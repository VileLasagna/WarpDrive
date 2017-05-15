cmake_minimum_required(VERSION 3.8)
project(dEffectiveMotor)

option(DEVELOPMENT_DEPLOY "Deploy to ./redist instead of to the system" ON)

if(NOT EXTERNAL_ROOT)
    set(EXTERNAL_ROOT "${CMAKE_SOURCE_DIR}/redist")
endif(NOT EXTERNAL_ROOT)

if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    set(WDSYSTEM_ROOT "/opt/WarpDrive")
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    set(WDSYSTEM_ROOT "c:/Program Files/${PROJECT_NAME}")
endif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
list(APPEND CMAKE_PREFIX_PATH ${WDSYSTEM_ROOT} ${EXTERNAL_ROOT})


if ( (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
        OR ( (CMAKE_INSTALL_PREFIX STREQUAL EXTERNAL_ROOT) OR (CMAKE_INSTALL_PREFIX STREQUAL WDSYSTEM_ROOT) ) )

    if(DEVELOPMENT_DEPLOY)
        set(CMAKE_INSTALL_PREFIX "${EXTERNAL_ROOT}" CACHE PATH "Default install path" FORCE)
    else(DEVELOPMENT_DEPLOY)
        set(CMAKE_INSTALL_PREFIX "${WDSYSTEM_ROOT}" CACHE PATH "Default install path" FORCE)
    endif(DEVELOPMENT_DEPLOY)

endif()

# create package-config.cmake stuff
if (UNIX) # varies config location depending on platform
    set(CMAKE_CONFIG_INSTALL_DIR "lib/${PROJECT_NAME}/cmake" CACHE STRING "Where ${PROJECT_NAME}-config.cmake and companions will be installed")
elseif(WIN32)
    set(CMAKE_CONFIG_INSTALL_DIR "cmake"  CACHE STRING "Where ${PROJECT_NAME}-config.cmake and companions will be installed")
elseif(APPLE)
    set(CMAKE_CONFIG_INSTALL_DIR "cmake" CACHE STRING "Where ${PROJECT_NAME}-config.cmake and companions will be installed")
endif()


add_subdirectory("WarpDrive")
#add_subdirectory("RigidCollisionDemo")
add_subdirectory("ModernOpenGLStudy")

set(CPACK_PACKAGE_NAME "WarpDrive_Installer")
set(CPACK_PACKAGE_VENDOR "Vile Lasagna")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Warp Drive - Game engine built on SDL2 and demos")


set(CPACK_GENERATOR "IFW")
set(CPACK_COMPONENTS_ALL WarpDrive OpenGLStudy)
set(CPACK_COMPONENT_WARPDRIVE_DISPLAY_NAME "Warp Drive")
set(CPACK_COMPONENT_OPENGLSTUDY_DISPLAY_NAME "GL Shader demo")

set(CPACK_COMPONENT_WARPDRIVE_DESCRIPTION
    "Install the lib and header files for the Warp Drive engine")
set(CPACK_COMPONENT_OPENGLSTUDY_DESCRIPTION
    "An in-progress Open GL Shader demo")

#Always last
include(CPack)
include(CPackIFW)

