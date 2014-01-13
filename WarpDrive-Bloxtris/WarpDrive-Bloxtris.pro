





CONFIG += app
#QT -= gui core
CONFIG -= qt

CONFIG(release, debug|release)
{
    DESTDIR = $$_PRO_FILE_PWD_/../distro/release
}


CONFIG(debug, debug|release)
{
    DESTDIR = $$_PRO_FILE_PWD_/../distro/debug
}


include(../WarpDrive/WarpDrive.pri)
#include a pri with your game specific code here
include(../Bloxtris/Bloxtris.pri)
