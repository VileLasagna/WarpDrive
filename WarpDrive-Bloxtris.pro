





CONFIG += app
#QT -= gui core
CONFIG -= qt

CONFIG(release, debug|release) \
{
    DESTDIR = $$_PRO_FILE_PWD_/distro/release
}


CONFIG(debug, debug|release) \
{
    DESTDIR = $$_PRO_FILE_PWD_/distro/debug
}

#QMAKE_CXX = clang++
#QMAKE_CC = clang
#QMAKE_CXXFLAGS += -std=c++14 #-stdlib=libstdc++
QMAKE_CXXFLAGS += -std=c++14
#QMAKE_CFLAGS += -stdlib=libstdc++
#QMAKE_LINK = llvm-link
#QMAKE_LFLAGS = -cppgen=program -v
#QMAKE_POST_LINK = llc -cppgen=program $$DESTDIR_TARGET
#QMAKE_LINK = ld

include($$_PRO_FILE_PWD_/WarpDrive/WarpDrive.pri)
#include a pri with your game specific code here
#include($$_PRO_FILE_PWD_/Bloxtris/Bloxtris.pri)
include($$_PRO_FILE_PWD_/GLPickingDemo/PickingDemo.pri)
