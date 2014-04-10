HEADERS += \
    $$_PRO_FILE_PWD_/Bloxtris/Brick.h           \
    $$_PRO_FILE_PWD_/Bloxtris/DemoState.h       \
    $$_PRO_FILE_PWD_/Bloxtris/GOScreen.h        \
    $$_PRO_FILE_PWD_/Bloxtris/Grid.h            \
    $$_PRO_FILE_PWD_/Bloxtris/MainGS.h          \
    $$_PRO_FILE_PWD_/Bloxtris/Splash.h          \
    $$_PRO_FILE_PWD_/Bloxtris/Tetrad.h          \
    $$_PRO_FILE_PWD_/Bloxtris/TKGridCommand.h

SOURCES += \
    $$_PRO_FILE_PWD_/Bloxtris/Brick.cpp         \
    $$_PRO_FILE_PWD_/Bloxtris/DemoState.cpp     \
    $$_PRO_FILE_PWD_/Bloxtris/GOScreen.cpp      \
    $$_PRO_FILE_PWD_/Bloxtris/Grid.cpp          \
    $$_PRO_FILE_PWD_/Bloxtris/MainGS.cpp        \
    $$_PRO_FILE_PWD_/Bloxtris/Splash.cpp        \
    $$_PRO_FILE_PWD_/Bloxtris/Tetrad.cpp        \
    $$_PRO_FILE_PWD_/Bloxtris/TKGridCommand.cpp \
    $$_PRO_FILE_PWD_/Bloxtris/main.cpp


data.path = $$DESTDIR/data

data.files +=   $$_PRO_FILE_PWD_/Bloxtris/data/Splash.png       \
                $$_PRO_FILE_PWD_/Bloxtris/data/arial.ttf        \
                $$_PRO_FILE_PWD_/Bloxtris/data/Background.png   \
                $$_PRO_FILE_PWD_/Bloxtris/data/Brick.mtl        \
                $$_PRO_FILE_PWD_/Bloxtris/data/Brick.obj        \
                $$_PRO_FILE_PWD_/Bloxtris/data/Demo.dat         \
                $$_PRO_FILE_PWD_/Bloxtris/data/DEMO.png         \
                $$_PRO_FILE_PWD_/Bloxtris/data/drop.wav         \
                $$_PRO_FILE_PWD_/Bloxtris/data/Elevation.mp3    \
                $$_PRO_FILE_PWD_/Bloxtris/data/failed.wav       \
                $$_PRO_FILE_PWD_/Bloxtris/data/GOScreen.png     \
                $$_PRO_FILE_PWD_/Bloxtris/data/line.wav         \
                $$_PRO_FILE_PWD_/Bloxtris/data/spin.wav         \
                $$_PRO_FILE_PWD_/Bloxtris/data/Splash.png       \
                $$_PRO_FILE_PWD_/Bloxtris/data/Tex1.png

INSTALLS += data
