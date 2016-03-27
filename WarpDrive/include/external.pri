INCLUDEPATH += \
    $$_PRO_FILE_PWD_/WarpDrive/include        \
    $$_PRO_FILE_PWD_/WarpDrive/


DEPENDPATH += \
    $$_PRO_FILE_PWD_/WarpDrive/lib

win32 \
{
    HEADERS += \
#        $$_PRO_FILE_PWD_/WarpDrive/include/GL/glut.h                      \
#        $$_PRO_FILE_PWD_/WarpDrive/include/GL/freeglut.h                  \
#        $$_PRO_FILE_PWD_/WarpDrive/include/GL/freeglut_ext.h              \
#        $$_PRO_FILE_PWD_/WarpDrive/include/GL/freeglut_std.h              \
        $$_PRO_FILE_PWD_/WarpDrive/include/SDL/begin_code.h               \
        $$_PRO_FILE_PWD_/WarpDrive/include/SDL/close_code.h               \
        $$_PRO_FILE_PWD_/WarpDrive/include/SDL/SDL.h                      \
        $$_PRO_FILE_PWD_/WarpDrive/include/SDL/SDL_assert.h               \
        $$_PRO_FILE_PWD_/WarpDrive/include/SDL/SDL_atomic.h               \
        $$_PRO_FILE_PWD_/WarpDrive/include/SDL/SDL_audio.h                \
        $$_PRO_FILE_PWD_/WarpDrive/include/SDL/SDL_bits.h                 \
        $$_PRO_FILE_PWD_/WarpDrive/include/SDL/SDL_blendmode.h            \
        $$_PRO_FILE_PWD_/WarpDrive/include/SDL/SDL_clipboard.h            \
        $$_PRO_FILE_PWD_/WarpDrive/include/SDL/SDL_config.h               \
        $$_PRO_FILE_PWD_/WarpDrive/include/SDL/SDL_cpuinfo.h              \
        $$_PRO_FILE_PWD_/WarpDrive/include/SDL/SDL_endian.h               \
        $$_PRO_FILE_PWD_/WarpDrive/include/SDL/SDL_error.h                \
        $$_PRO_FILE_PWD_/WarpDrive/include/SDL/SDL_events.h               \
        $$_PRO_FILE_PWD_/WarpDrive/include/SDL/SDL_gamecontroller.h       \
        $$_PRO_FILE_PWD_/WarpDrive/include/SDL/SDL_gesture.h              \
        $$_PRO_FILE_PWD_/WarpDrive/include/SDL/SDL_haptic.h               \
        $$_PRO_FILE_PWD_/WarpDrive/include/SDL/SDL_hints.h                \
        $$_PRO_FILE_PWD_/WarpDrive/include/SDL/SDL_image.h                \
        $$_PRO_FILE_PWD_/WarpDrive/include/SDL/SDL_joystick.h             \
        $$_PRO_FILE_PWD_/WarpDrive/include/SDL/SDL_keyboard.h             \
        $$_PRO_FILE_PWD_/WarpDrive/include/SDL/SDL_keycode.h              \
        $$_PRO_FILE_PWD_/WarpDrive/include/SDL/SDL_loadso.h               \
        $$_PRO_FILE_PWD_/WarpDrive/include/SDL/SDL_log.h                  \
        $$_PRO_FILE_PWD_/WarpDrive/include/SDL/SDL_main.h                 \
        $$_PRO_FILE_PWD_/WarpDrive/include/SDL/SDL_messagebox.h           \
        $$_PRO_FILE_PWD_/WarpDrive/include/SDL/SDL_mixer.h                \
        $$_PRO_FILE_PWD_/WarpDrive/include/SDL/SDL_mouse.h                \
        $$_PRO_FILE_PWD_/WarpDrive/include/SDL/SDL_mutex.h                \
        $$_PRO_FILE_PWD_/WarpDrive/include/SDL/SDL_name.h                 \
        $$_PRO_FILE_PWD_/WarpDrive/include/SDL/SDL_opengl.h               \
        $$_PRO_FILE_PWD_/WarpDrive/include/SDL/SDL_opengles.h             \
        $$_PRO_FILE_PWD_/WarpDrive/include/SDL/SDL_opengles2.h            \
        $$_PRO_FILE_PWD_/WarpDrive/include/SDL/SDL_pixels.h               \
        $$_PRO_FILE_PWD_/WarpDrive/include/SDL/SDL_platform.h             \
        $$_PRO_FILE_PWD_/WarpDrive/include/SDL/SDL_power.h                \
        $$_PRO_FILE_PWD_/WarpDrive/include/SDL/SDL_quit.h                 \
        $$_PRO_FILE_PWD_/WarpDrive/include/SDL/SDL_rect.h                 \
        $$_PRO_FILE_PWD_/WarpDrive/include/SDL/SDL_render.h               \
        $$_PRO_FILE_PWD_/WarpDrive/include/SDL/SDL_revision.h             \
        $$_PRO_FILE_PWD_/WarpDrive/include/SDL/SDL_rwops.h                \
        $$_PRO_FILE_PWD_/WarpDrive/include/SDL/SDL_scancode.h             \
        $$_PRO_FILE_PWD_/WarpDrive/include/SDL/SDL_shape.h                \
        $$_PRO_FILE_PWD_/WarpDrive/include/SDL/SDL_stdinc.h               \
        $$_PRO_FILE_PWD_/WarpDrive/include/SDL/SDL_surface.h              \
        $$_PRO_FILE_PWD_/WarpDrive/include/SDL/SDL_system.h               \
        $$_PRO_FILE_PWD_/WarpDrive/include/SDL/SDL_syswm.h                \
        $$_PRO_FILE_PWD_/WarpDrive/include/SDL/SDL_test.h                 \
        $$_PRO_FILE_PWD_/WarpDrive/include/SDL/SDL_test_assert.h          \
        $$_PRO_FILE_PWD_/WarpDrive/include/SDL/SDL_test_common.h          \
        $$_PRO_FILE_PWD_/WarpDrive/include/SDL/SDL_test_compare.h         \
        $$_PRO_FILE_PWD_/WarpDrive/include/SDL/SDL_test_crc32.h           \
        $$_PRO_FILE_PWD_/WarpDrive/include/SDL/SDL_test_font.h            \
        $$_PRO_FILE_PWD_/WarpDrive/include/SDL/SDL_test_fuzzer.h          \
        $$_PRO_FILE_PWD_/WarpDrive/include/SDL/SDL_test_harness.h         \
        $$_PRO_FILE_PWD_/WarpDrive/include/SDL/SDL_test_images.h          \
        $$_PRO_FILE_PWD_/WarpDrive/include/SDL/SDL_test_log.h             \
        $$_PRO_FILE_PWD_/WarpDrive/include/SDL/SDL_test_md5.h             \
        $$_PRO_FILE_PWD_/WarpDrive/include/SDL/SDL_test_random.h          \
        $$_PRO_FILE_PWD_/WarpDrive/include/SDL/SDL_thread.h               \
        $$_PRO_FILE_PWD_/WarpDrive/include/SDL/SDL_timer.h                \
        $$_PRO_FILE_PWD_/WarpDrive/include/SDL/SDL_touch.h                \
        $$_PRO_FILE_PWD_/WarpDrive/include/SDL/SDL_ttf.h                  \
        $$_PRO_FILE_PWD_/WarpDrive/include/SDL/SDL_types.h                \
        $$_PRO_FILE_PWD_/WarpDrive/include/SDL/SDL_version.h              \
        $$_PRO_FILE_PWD_/WarpDrive/include/SDL/SDL_video.h


    LIBS += \
        $$_PRO_FILE_PWD_/WarpDrive/lib/freeglut.lib              \
        $$_PRO_FILE_PWD_/WarpDrive/lib/SDL2.lib                  \
        $$_PRO_FILE_PWD_/WarpDrive/lib/SDL2main.lib              \
        $$_PRO_FILE_PWD_/WarpDrive/lib/SDL2test.lib              \
        $$_PRO_FILE_PWD_/WarpDrive/lib/SDL2_image.lib            \
        $$_PRO_FILE_PWD_/WarpDrive/lib/SDL2_mixer.lib            \
        $$_PRO_FILE_PWD_/WarpDrive/lib/SDL2_ttf.lib              \
    #    $$_PRO_FILE_PWD_/WarpDrive/lib/freeglut.dll              \
    #    $$_PRO_FILE_PWD_/WarpDrive/lib/libFLAC-8.dll             \
    #    $$_PRO_FILE_PWD_/WarpDrive/lib/libfreetype-6.dll         \
    #    $$_PRO_FILE_PWD_/WarpDrive/lib/libjpeg-9.dll             \
    #    $$_PRO_FILE_PWD_/WarpDrive/lib/libmikmod-2.dll           \
    #    $$_PRO_FILE_PWD_/WarpDrive/lib/libmodplug-1.dll          \
    #    $$_PRO_FILE_PWD_/WarpDrive/lib/libogg-0.dll              \
    #    $$_PRO_FILE_PWD_/WarpDrive/lib/libpng16-16.dll           \
    #    $$_PRO_FILE_PWD_/WarpDrive/lib/libtiff-5.dll             \
    #    $$_PRO_FILE_PWD_/WarpDrive/lib/libvorbis-0.dll           \
    #    $$_PRO_FILE_PWD_/WarpDrive/lib/libvorbisfile-3.dll       \
    #    $$_PRO_FILE_PWD_/WarpDrive/lib/libwebp-4.dll             \
    #    $$_PRO_FILE_PWD_/WarpDrive/lib/SDL2.dll                  \
    #    $$_PRO_FILE_PWD_/WarpDrive/lib/SDL2_image.dll            \
    #    $$_PRO_FILE_PWD_/WarpDrive/lib/SDL2_mixer.dll            \
    #    $$_PRO_FILE_PWD_/WarpDrive/lib/SDL2_ttf.dll              \
    #    $$_PRO_FILE_PWD_/WarpDrive/lib/smpeg2.dll                \
    #    $$_PRO_FILE_PWD_/WarpDrive/lib/zlib1.dll



    dlls.path = $$DESTDIR
    dlls.files += \
        $$_PRO_FILE_PWD_/WarpDrive/lib/freeglut.dll              \
        $$_PRO_FILE_PWD_/WarpDrive/lib/libFLAC-8.dll             \
        $$_PRO_FILE_PWD_/WarpDrive/lib/libfreetype-6.dll         \
        $$_PRO_FILE_PWD_/WarpDrive/lib/libjpeg-9.dll             \
        $$_PRO_FILE_PWD_/WarpDrive/lib/libmikmod-2.dll           \
        $$_PRO_FILE_PWD_/WarpDrive/lib/libmodplug-1.dll          \
        $$_PRO_FILE_PWD_/WarpDrive/lib/libogg-0.dll              \
        $$_PRO_FILE_PWD_/WarpDrive/lib/libpng16-16.dll           \
        $$_PRO_FILE_PWD_/WarpDrive/lib/libtiff-5.dll             \
        $$_PRO_FILE_PWD_/WarpDrive/lib/libvorbis-0.dll           \
        $$_PRO_FILE_PWD_/WarpDrive/lib/libvorbisfile-3.dll       \
        $$_PRO_FILE_PWD_/WarpDrive/lib/libwebp-4.dll             \
        $$_PRO_FILE_PWD_/WarpDrive/lib/SDL2.dll                  \
        $$_PRO_FILE_PWD_/WarpDrive/lib/SDL2_image.dll            \
        $$_PRO_FILE_PWD_/WarpDrive/lib/SDL2_mixer.dll            \
        $$_PRO_FILE_PWD_/WarpDrive/lib/SDL2_ttf.dll              \
        $$_PRO_FILE_PWD_/WarpDrive/lib/smpeg2.dll                \
        $$_PRO_FILE_PWD_/WarpDrive/lib/zlib1.dll



    VCREDISTPATH = "Redefine me"

    CONFIG(release, debug|release)
    {
        VCREDISTPATH = "C:\\Program Files (x86)\\Microsoft Visual Studio 11.0\\VC\\redist\\x64\\Microsoft.VC110.CRT"
    }

    CONFIG(debug, debug|release)
    {
        VCREDISTPATH = "C:\\Program Files (x86)\\Microsoft Visual Studio 11.0\\VC\\redist\\Debug_NonRedist\\x64\\Microsoft.VC110.DebugCRT"
    }


    message($$VCREDISTPATH)



    CONFIG(debug, debug|release)
    {
    dlls.files += \
                $$VCREDISTPATH\\msvcp110d.dll       \
                $$VCREDISTPATH\\msvcr110d.dll       \
                $$VCREDISTPATH\\vccorlib110d.dll
    }

    CONFIG(release, debug|release)
    {
    dlls.files += \
                $$VCREDISTPATH\\msvcp110.dll       \
                $$VCREDISTPATH\\msvcr110.dll       \
                $$VCREDISTPATH\\vccorlib110.dll
    }

    INSTALLS += dlls
}
#ABOUT THIS SECTION OF THE PROJECT!
#
# Qt is supposed to differentiate by both target.arch or mkspecs.
# Checking MY Qt install folder, I DID find the linux-g++-64/32 folders
# However, Qt most helpfully  has done away with it and just reports itself
# as "linux-g++". To boot, QMAKE_TARGET.arch returns null. Joy all around ¬¬
# So, for now this is set to compile only to your host environment, so no
# 32/64-bits cross compiling

#message("Host architecture is: "$$QMAKE_HOST.arch)

linux-g++:contains(QMAKE_HOST.arch, x86_64):\
{
    # include SDL
    LIBS += -L/usr/lib64 -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_gfx -lSDL2_mixer -lGL -lglut -lGLU -lGLEW -lpthread #-lSDL2_test
    message("Configured for 64bits GCC Linux")
}
linux-g++:contains(QMAKE_HOST.arch, x86):\
{
    # include SDL
    LIBS += -L/usr/lib -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_gfx -lSDL2_mixer -lSDL2_test -lGL -lglut -lGLU -lGLEW -lpthread
    message("Configured for 32bits GCC Linux")
}


linux-clang:contains(QMAKE_HOST.arch, x86_64):\
{
    # include SDL
    LIBS += -L/usr/lib64 -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_gfx -lSDL2_mixer -lGL -lglut -lGLU -lGLEW  -lpthread  #-lSDL2_test
    message("Configured for 64bits CLANG Linux")
}
linux-clang:contains(QMAKE_HOST.arch, x86):\
{
    # include SDL
    LIBS += -L/usr/lib -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_gfx -lSDL2_mixer -lSDL2_test -lGL -lglut -lGLU -lGLEW -lpthread
    message("Configured for 32bits CLANG Linux")
}



