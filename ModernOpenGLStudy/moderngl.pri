SOURCES += \
    $$_PRO_FILE_PWD_/ModernOpenGLStudy/main.cpp         \
    $$_PRO_FILE_PWD_/ModernOpenGLStudy/gldemostate.cpp

HEADERS += \
    $$_PRO_FILE_PWD_/ModernOpenGLStudy/gldemostate.hpp

DISTFILES += \
    $$_PRO_FILE_PWD_/ModernOpenGLStudy/fragtest1.frag \
    $$_PRO_FILE_PWD_/ModernOpenGLStudy/verttest1.vert

shaders.path = $$target.path
shaders.files += \
    $$_PRO_FILE_PWD_/ModernOpenGLStudy/fragtest1.frag \
    $$_PRO_FILE_PWD_/ModernOpenGLStudy/verttest1.vert

INSTALLS += shaders

TARGET = WD_ModernGL

