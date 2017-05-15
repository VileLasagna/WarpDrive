cmake_minimum_required(VERSION 3.7)
project(WarpDrive)

option(DEVELOPMENT_DEPLOY "Deploy to ./redist instead of to the system" ON)

set(WarpDrive_VERSION 0.7)

if(NOT EXTERNAL_ROOT)
    set(EXTERNAL_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/redist")
endif(NOT EXTERNAL_ROOT)

if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    set(WDSYSTEM_ROOT "/usr/local")
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    set(WDSYSTEM_ROOT "c:/Program Files/${PROJECT_NAME}")
endif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
list(APPEND CMAKE_PREFIX_PATH ${WDSYSTEM_ROOT})


if ( (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
        OR ( (CMAKE_INSTALL_PREFIX STREQUAL EXTERNAL_ROOT) OR (CMAKE_INSTALL_PREFIX STREQUAL WDSYSTEM_ROOT) ) )

    if(DEVELOPMENT_DEPLOY)
        set(CMAKE_INSTALL_PREFIX "${EXTERNAL_ROOT}" CACHE PATH "Default install path" FORCE)
    else(DEVELOPMENT_DEPLOY)
        set(CMAKE_INSTALL_PREFIX "${WDSYSTEM_ROOT}" CACHE PATH "Default install path" FORCE)
    endif(DEVELOPMENT_DEPLOY)

endif()

# create -config.cmake stuff
if (UNIX) # varies config location depending on platform
    set(WarpDrive_INSTALL_DIR "lib/WarpDrive/cmake" CACHE STRING "Where WarpDrive-config.cmake and companions will be installed")
elseif(WIN32)
    set(WarpDrive_INSTALL_DIR "cmake"  CACHE STRING "Where WarpDrive-config.cmake and companions will be installed")
elseif(APPLE)
    set(WarpDrive_INSTALL_DIR "cmake" CACHE STRING "Where WarpDrive-config.cmake and companions will be installed")
endif()

set(LIB_INSTALL_DIR lib)
set(INCLUDE_INSTALL_DIR include)

include("WarpDriveSources.cmake")

add_custom_target(WrpDrvHeaders SOURCES ${WARPDRIVE_HEADERS_PUBLIC} )
add_custom_target(WrpDrvInternal SOURCES ${WARPDRIVE_HEADERS_PRIVATE} )



add_library(${PROJECT_NAME} ${WARPDRIVE_HEADERS_PUBLIC} ${WARPDRIVE_HEADERS_PRIVATE} ${WARPDRIVE_SOURCES})
target_compile_features(${PROJECT_NAME} PUBLIC
                                            cxx_constexpr
                                            cxx_relaxed_constexpr
                                            cxx_auto_type
                                            cxx_decltype
                                            cxx_deleted_functions
                                            cxx_defaulted_move_initializers
                                            cxx_explicit_conversions
                                            cxx_lambdas
                                            cxx_lambda_init_captures
                                            cxx_generic_lambdas
                                            cxx_noexcept
                                            cxx_rvalue_references
                                            cxx_return_type_deduction
                                            cxx_strong_enums
                                            cxx_nullptr
                                            cxx_uniform_initialization
                                            cxx_override
                            )
add_library(${PROJECT_NAME} ${WARPDRIVE_SOURCES})

find_package(SDL2)

target_link_libraries(${PROJECT_NAME} INTERFACE ${SDL2_LIBRARIES} SDL2_ttf SDL2_image)
target_include_directories(${PROJECT_NAME} PUBLIC   $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/..>
                                                    $<INSTALL_INTERFACE:include>)

set(CMAKE_THREAD_PREFER_PTHREAD ON)
find_package(Threads)
target_link_libraries(${PROJECT_NAME} INTERFACE Threads::Threads)

find_package(OpenGL)
target_link_libraries(${PROJECT_NAME} INTERFACE ${OPENGL_LIBRARIES})

find_package(GLEW)
target_link_libraries(${PROJECT_NAME} INTERFACE GLEW::GLEW)

# Install all public headers to the correct folders

install(FILES   ${WARPDRIVE_HEADERS_3DMATHS}
                DESTINATION include/WarpDrive/3dmaths       )
install(FILES   ${WARPDRIVE_HEADERS_BASEMATHS}
                DESTINATION include/WarpDrive/basemaths     )
install(FILES   ${WARPDRIVE_HEADERS_SYSTEM}
                DESTINATION include/WarpDrive/basesystem    )
install(FILES   ${WARPDRIVE_HEADERS_DISPLAY}
                DESTINATION include/WarpDrive/display       )
install(FILES   ${WARPDRIVE_HEADERS_EVENTS}
                DESTINATION include/WarpDrive/events        )
install(FILES   ${WARPDRIVE_HEADERS_PHYSICS}
                DESTINATION include/WarpDrive/physics       )
install(FILES   ${WARPDRIVE_HEADERS_SOUND}
                DESTINATION include/WarpDrive/sound         )

install(    TARGETS WarpDrive
            EXPORT  WarpDrive-targets
            RUNTIME DESTINATION bin
            LIBRARY DESTINATION lib
            ARCHIVE DESTINATION lib
            COMPONENT WarpDrive
        )


################################################################
###     Package Creation
################################################################


include(CMakePackageConfigHelpers)
configure_package_config_file(
    cmake-src/WarpDrive-config.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/WarpDrive-config-tmp
    INSTALL_DESTINATION ${WarpDrive_INSTALL_DIR}
    PATH_VARS INCLUDE_INSTALL_DIR LIB_INSTALL_DIR
    )

write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/WarpDrive-config-version.cmake
    VERSION ${WarpDrive_VERSION}
    COMPATIBILITY ExactVersion
    )

install( FILES
    ${CMAKE_CURRENT_BINARY_DIR}/WarpDrive-config-version.cmake
    RENAME WarpDrive-config-version.cmake
    DESTINATION ${WarpDrive_INSTALL_DIR}
    )

install( FILES
    ${CMAKE_CURRENT_BINARY_DIR}/WarpDrive-config-tmp
    RENAME WarpDrive-config.cmake
    DESTINATION ${WarpDrive_INSTALL_DIR}
    )

install(EXPORT WarpDrive-targets DESTINATION ${WarpDrive_INSTALL_DIR})

