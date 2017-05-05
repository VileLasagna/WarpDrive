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

#[[
Separating into groups like this is pretty awkward/overkill, yeah however
I don't want to use install(DIRECTORY ... FILE_MATCHING_PATTERN *.hpp)
The reasoning behind this is that it would prevent me from having private
headers using that name scheme and ultimately make the deployment more finicky
]]

set(WARPDRIVE_HEADERS_3DMATHS   ${WARPDRIVE_HEADERS_3DMATHS}
                                3dmaths/billboard.hpp
                                3dmaths/glmesh.hpp
                                3dmaths/material.hpp
                                3dmaths/model.hpp
                                3dmaths/modelloader.hpp
                                3dmaths/vertex.hpp
                                3dmaths/viewport.hpp
)

set(WARPDRIVE_HEADERS_BASEMATHS ${WARPDRIVE_HEADERS_BASEMATHS}

                                basemaths/capsule.hpp
                                basemaths/cliplinesegbox.hpp
                                basemaths/frustrum.hpp
                                basemaths/lineseg.hpp
                                basemaths/matrix44.hpp
                                basemaths/plane.hpp
                                basemaths/quaternion.hpp
                                basemaths/rect.hpp
                                basemaths/sphere.hpp
                                basemaths/tri.hpp
                                basemaths/vec2.hpp
                                basemaths/vec3.hpp
                                basemaths/vec4.hpp
                                basemaths/ray.hpp
)

set(WARPDRIVE_HEADERS_SYSTEM   ${WARPDRIVE_HEADERS_SYSTEM}

                                basesystem/configloader.hpp
                                basesystem/displaymanager.hpp
                                basesystem/err.hpp
                                basesystem/factory.hpp
                                basesystem/filemanager.hpp
                                basesystem/game.hpp
                                basesystem/gameobject.hpp
                                basesystem/gamestate.hpp
                                basesystem/managedfile.hpp
                                basesystem/memory.hpp
                                basesystem/score.hpp
                                basesystem/stringproc.hpp
                                basesystem/ttfmanager.hpp
                                basesystem/sdleventhandler.hpp
                                basesystem/sdlfontmanager.hpp
                                basesystem/util.hpp
)

set(WARPDRIVE_HEADERS_DISPLAY   ${WARPDRIVE_HEADERS_DISPLAY}

                                display/camera.hpp
                                display/colour.hpp
                                display/sdlimage.hpp
                                display/rgbacolour.hpp
                                display/rgbcolour.hpp
                                display/sdlttf.hpp
                                display/texture.hpp
                                display/sprite.hpp
                                display/texturesheet.hpp
                                display/glshader.hpp
                                display/animsheet.hpp
)

set(WARPDRIVE_HEADERS_EVENTS   ${WARPDRIVE_HEADERS_EVENTS}

                                events/glcolorevent.hpp
                                events/objectevent.hpp
                                events/panandtiltevent.hpp
                                events/timedmoveevent.hpp
                                events/timedremoveevent.hpp
                                events/timeline.hpp
                                events/timelinekey.hpp
                                events/tkaddevent.hpp
                                events/tkmoveobject.hpp
                                events/tkplaymusic.hpp
                                events/tkuseobject.hpp
)

set(WARPDRIVE_HEADERS_PHYSICS   ${WARPDRIVE_HEADERS_PHYSICS}

                                physics/alignedboundingbox.hpp
                                physics/collisionsystem.hpp
                                physics/octree.hpp
                                physics/voxelgrid.hpp
                                physics/bruteforcecollisioncheck.hpp
                                physics/rdccollisioncheck.hpp
                                physics/rbpcollision.hpp
)

set(WARPDRIVE_HEADERS_SOUND   ${WARPDRIVE_HEADERS_SOUND}

                                sound/soundfx.hpp
                                sound/soundmanager.hpp
)

set(WARPDRIVE_HEADERS_PUBLIC    ${WARPDRIVE_HEADERS_3DMATHS}
                                ${WARPDRIVE_HEADERS_BASEMATHS}
                                ${WARPDRIVE_HEADERS_SYSTEM}
                                ${WARPDRIVE_HEADERS_DISPLAY}
                                ${WARPDRIVE_HEADERS_EVENTS}
                                ${WARPDRIVE_HEADERS_PHYSICS}
                                ${WARPDRIVE_HEADERS_SOUND}
)

set(WARPDRIVE_HEADERS_PRIVATE   ${WARPDRIVE_HEADERS_PRIVATE}

                                3dmaths/glm.h
                                3dmaths/glmint.h
)

set(WARPDRIVE_SOURCES   ${WARPDRIVE_SOURCES}
                        3dmaths/billboard.cpp
                        3dmaths/glmesh.cpp
                        3dmaths/material.cpp
                        3dmaths/model.cpp
                        3dmaths/vertex.cpp
                        3dmaths/glm.c
                        3dmaths/glm_util.c
                        3dmaths/glmimg.c
                        3dmaths/glmimg_sdl.c

                        basemaths/capsule.cpp
                        basemaths/cliplinesegbox.cpp
                        basemaths/frustrum.cpp
                        basemaths/lineseg.cpp
                        basemaths/matrix44.cpp
                        basemaths/plane.cpp
                        basemaths/quaternion.cpp
                        basemaths/sphere.cpp
                        basemaths/ray.cpp

                        basesystem/configloader.cpp
                        basesystem/displaymanager.cpp
                        basesystem/err.cpp
                        basesystem/filemanager.cpp
                        basesystem/game.cpp
                        basesystem/gameobject.cpp
                        basesystem/managedfile.cpp
                        basesystem/memory.cpp
                        basesystem/score.cpp
                        basesystem/stringproc.cpp
                        basesystem/ttfmanager.cpp
                        basesystem/sdleventhandler.cpp
                        basesystem/sdlfontmanager.cpp
                        basesystem/util.cpp
                        basesystem/gamestate.cpp

                        display/camera.cpp
                        display/sdlimage.cpp
                        display/sdlttf.cpp
                        display/texture.cpp
                        display/animsheet.cpp
                        display/sprite.cpp
                        display/texturesheet.cpp
                        display/glshader.cpp

                        events/glcolorevent.cpp
                        events/panandtiltevent.cpp
                        events/timedmoveevent.cpp
                        events/timedremoveevent.cpp
                        events/timeline.cpp
                        events/tkmoveobject.cpp
                        events/tkuseobject.cpp
                        events/timelinekey.cpp
                        events/objectevent.cpp

                        physics/alignedboundingbox.cpp
                        physics/bruteforcecollisioncheck.cpp
                        physics/rdccollisioncheck.cpp
                        physics/collisionsystem.cpp
                        physics/rbpcollision.cpp

                        sound/soundfx.cpp
                        sound/soundmanager.cpp
        )

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

