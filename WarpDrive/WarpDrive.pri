include ($$_PRO_FILE_PWD_/WarpDrive/include/external.pri)

HEADERS += \
    $$_PRO_FILE_PWD_/WarpDrive/3dmaths/billboard.hpp              \
    $$_PRO_FILE_PWD_/WarpDrive/3dmaths/glm.h                      \
    $$_PRO_FILE_PWD_/WarpDrive/3dmaths/glmesh.hpp                   \
    $$_PRO_FILE_PWD_/WarpDrive/3dmaths/glmint.hpp                   \
    $$_PRO_FILE_PWD_/WarpDrive/3dmaths/material.hpp                 \
    $$_PRO_FILE_PWD_/WarpDrive/3dmaths/model.hpp                    \
    $$_PRO_FILE_PWD_/WarpDrive/3dmaths/modelloader.hpp              \
    $$_PRO_FILE_PWD_/WarpDrive/3dmaths/teapot.hpp                   \
    $$_PRO_FILE_PWD_/WarpDrive/3dmaths/vertex.hpp                   \
    $$_PRO_FILE_PWD_/WarpDrive/3dmaths/viewport.hpp                 \
    $$_PRO_FILE_PWD_/WarpDrive/basemaths/capsule.hpp                \
    $$_PRO_FILE_PWD_/WarpDrive/basemaths/cliplinesegbox.hpp         \
    $$_PRO_FILE_PWD_/WarpDrive/basemaths/frustrum.hpp               \
    $$_PRO_FILE_PWD_/WarpDrive/basemaths/lineseg.hpp                \
    $$_PRO_FILE_PWD_/WarpDrive/basemaths/matrix44.hpp               \
    $$_PRO_FILE_PWD_/WarpDrive/basemaths/plane.hpp                  \
    $$_PRO_FILE_PWD_/WarpDrive/basemaths/quaternion.hpp             \
    $$_PRO_FILE_PWD_/WarpDrive/basemaths/rect.hpp                   \
    $$_PRO_FILE_PWD_/WarpDrive/basemaths/sphere.hpp                 \
    $$_PRO_FILE_PWD_/WarpDrive/basemaths/tri.hpp                    \
    $$_PRO_FILE_PWD_/WarpDrive/basemaths/vec2.hpp                   \
    $$_PRO_FILE_PWD_/WarpDrive/basemaths/vec3.hpp                   \
    $$_PRO_FILE_PWD_/WarpDrive/basemaths/vec4.hpp                   \
    $$_PRO_FILE_PWD_/WarpDrive/basesystem/configloader.hpp          \
    $$_PRO_FILE_PWD_/WarpDrive/basesystem/displaymanager.hpp        \
    $$_PRO_FILE_PWD_/WarpDrive/basesystem/err.hpp                   \
    $$_PRO_FILE_PWD_/WarpDrive/basesystem/factory.hpp               \
    $$_PRO_FILE_PWD_/WarpDrive/basesystem/filemanager.hpp           \
    $$_PRO_FILE_PWD_/WarpDrive/basesystem/game.hpp                  \
    $$_PRO_FILE_PWD_/WarpDrive/basesystem/gameobject.hpp            \
    $$_PRO_FILE_PWD_/WarpDrive/basesystem/gamestate.hpp             \
    $$_PRO_FILE_PWD_/WarpDrive/basesystem/managedfile.hpp           \
    $$_PRO_FILE_PWD_/WarpDrive/basesystem/memory.hpp                \
    $$_PRO_FILE_PWD_/WarpDrive/basesystem/objloader.hpp             \
    $$_PRO_FILE_PWD_/WarpDrive/basesystem/score.hpp                 \
    $$_PRO_FILE_PWD_/WarpDrive/basesystem/stringproc.hpp            \
    $$_PRO_FILE_PWD_/WarpDrive/basesystem/teapotloaderstate.hpp     \
    $$_PRO_FILE_PWD_/WarpDrive/basesystem/ttfmanager.hpp            \
    $$_PRO_FILE_PWD_/WarpDrive/basesystem/sdleventhandler.hpp       \
    $$_PRO_FILE_PWD_/WarpDrive/display/camera.hpp                   \
    $$_PRO_FILE_PWD_/WarpDrive/display/colour.hpp                   \
    $$_PRO_FILE_PWD_/WarpDrive/display/sdlimage.hpp                 \
    $$_PRO_FILE_PWD_/WarpDrive/display/rgbacolour.hpp               \
    $$_PRO_FILE_PWD_/WarpDrive/display/rgbcolour.hpp                \
    $$_PRO_FILE_PWD_/WarpDrive/display/sdlttf.hpp                   \
    $$_PRO_FILE_PWD_/WarpDrive/display/texture.hpp                  \
    $$_PRO_FILE_PWD_/WarpDrive/events/glcolorevent.hpp              \
    $$_PRO_FILE_PWD_/WarpDrive/events/objectevent.hpp               \
    $$_PRO_FILE_PWD_/WarpDrive/events/panandtiltevent.hpp           \
    $$_PRO_FILE_PWD_/WarpDrive/events/timedmoveevent.hpp            \
    $$_PRO_FILE_PWD_/WarpDrive/events/timedremoveevent.hpp          \
    $$_PRO_FILE_PWD_/WarpDrive/events/timeline.hpp                  \
    $$_PRO_FILE_PWD_/WarpDrive/events/timelinekey.hpp               \
    $$_PRO_FILE_PWD_/WarpDrive/events/tkaddevent.hpp                \
    $$_PRO_FILE_PWD_/WarpDrive/events/tkdrawteapot.hpp              \
    $$_PRO_FILE_PWD_/WarpDrive/events/tkmoveobject.hpp              \
    $$_PRO_FILE_PWD_/WarpDrive/events/tkplaymusic.hpp               \
    $$_PRO_FILE_PWD_/WarpDrive/events/tkuseobject.hpp               \
    $$_PRO_FILE_PWD_/WarpDrive/physics/alignedboundingbox.hpp       \
    $$_PRO_FILE_PWD_/WarpDrive/physics/collisionsystem.hpp          \
    $$_PRO_FILE_PWD_/WarpDrive/physics/octree.hpp                   \
    $$_PRO_FILE_PWD_/WarpDrive/physics/voxelgrid.hpp                \
    $$_PRO_FILE_PWD_/WarpDrive/sound/soundfx.hpp                    \
    $$_PRO_FILE_PWD_/WarpDrive/sound/soundmanager.hpp               \
    $$_PRO_FILE_PWD_/WarpDrive/display/animsheet.hpp                \
    $$_PRO_FILE_PWD_/WarpDrive/basesystem/sdlfontmanager.hpp        \
    $$_PRO_FILE_PWD_/WarpDrive/display/sprite.hpp                   \
    $$_PRO_FILE_PWD_/WarpDrive/display/texturesheet.hpp             \
    $$_PRO_FILE_PWD_/WarpDrive/basemaths/ray.hpp                    \
    $$_PRO_FILE_PWD_/WarpDrive/physics/bruteforcecollision.hpp      \
    $$_PRO_FILE_PWD_/WarpDrive/physics/rdccollision.hpp


SOURCES += \
    $$_PRO_FILE_PWD_/WarpDrive/3dmaths/billboard.cpp                \
    $$_PRO_FILE_PWD_/WarpDrive/3dmaths/glmesh.cpp                   \
    $$_PRO_FILE_PWD_/WarpDrive/3dmaths/material.cpp                 \
    $$_PRO_FILE_PWD_/WarpDrive/3dmaths/model.cpp                    \
    $$_PRO_FILE_PWD_/WarpDrive/3dmaths/vertex.cpp                   \
    $$_PRO_FILE_PWD_/WarpDrive/3dmaths/glm.c                        \
    $$_PRO_FILE_PWD_/WarpDrive/3dmaths/glm_util.c                   \
    $$_PRO_FILE_PWD_/WarpDrive/3dmaths/glmimg.c                     \
    $$_PRO_FILE_PWD_/WarpDrive/3dmaths/glmimg_sdl.c                 \
    $$_PRO_FILE_PWD_/WarpDrive/basemaths/capsule.cpp                \
    $$_PRO_FILE_PWD_/WarpDrive/basemaths/cliplinesegbox.cpp         \
    $$_PRO_FILE_PWD_/WarpDrive/basemaths/frustrum.cpp               \
    $$_PRO_FILE_PWD_/WarpDrive/basemaths/lineseg.cpp                \
    $$_PRO_FILE_PWD_/WarpDrive/basemaths/matrix44.cpp               \
    $$_PRO_FILE_PWD_/WarpDrive/basemaths/plane.cpp                  \
    $$_PRO_FILE_PWD_/WarpDrive/basemaths/quaternion.cpp             \
    $$_PRO_FILE_PWD_/WarpDrive/basemaths/sphere.cpp                 \
    $$_PRO_FILE_PWD_/WarpDrive/basesystem/configloader.cpp          \
    $$_PRO_FILE_PWD_/WarpDrive/basesystem/displaymanager.cpp        \
    $$_PRO_FILE_PWD_/WarpDrive/basesystem/err.cpp                   \
    $$_PRO_FILE_PWD_/WarpDrive/basesystem/filemanager.cpp           \
    $$_PRO_FILE_PWD_/WarpDrive/basesystem/game.cpp                  \
    $$_PRO_FILE_PWD_/WarpDrive/basesystem/gameobject.cpp            \
    $$_PRO_FILE_PWD_/WarpDrive/basesystem/managedfile.cpp           \
    $$_PRO_FILE_PWD_/WarpDrive/basesystem/memory.cpp                \
    $$_PRO_FILE_PWD_/WarpDrive/basesystem/score.cpp                 \
    $$_PRO_FILE_PWD_/WarpDrive/basesystem/stringproc.cpp            \
    $$_PRO_FILE_PWD_/WarpDrive/basesystem/teapotloaderstate.cpp     \
    $$_PRO_FILE_PWD_/WarpDrive/basesystem/ttfmanager.cpp            \
    $$_PRO_FILE_PWD_/WarpDrive/basesystem/sdleventhandler.cpp       \
    $$_PRO_FILE_PWD_/WarpDrive/display/camera.cpp                   \
    $$_PRO_FILE_PWD_/WarpDrive/display/sdlimage.cpp                 \
    $$_PRO_FILE_PWD_/WarpDrive/display/sdlttf.cpp                   \
    $$_PRO_FILE_PWD_/WarpDrive/display/texture.cpp                  \
    $$_PRO_FILE_PWD_/WarpDrive/events/glcolorevent.cpp              \
    $$_PRO_FILE_PWD_/WarpDrive/events/panandtiltevent.cpp           \
    $$_PRO_FILE_PWD_/WarpDrive/events/timedmoveevent.cpp            \
    $$_PRO_FILE_PWD_/WarpDrive/events/timedremoveevent.cpp          \
    $$_PRO_FILE_PWD_/WarpDrive/events/timeline.cpp                  \
    $$_PRO_FILE_PWD_/WarpDrive/events/tkmoveobject.cpp              \
    $$_PRO_FILE_PWD_/WarpDrive/events/tkuseobject.cpp               \
    $$_PRO_FILE_PWD_/WarpDrive/physics/alignedboundingbox.cpp       \
    $$_PRO_FILE_PWD_/WarpDrive/sound/soundfx.cpp                    \
    $$_PRO_FILE_PWD_/WarpDrive/sound/soundmanager.cpp               \
    $$_PRO_FILE_PWD_/WarpDrive/display/animsheet.cpp                \
    $$_PRO_FILE_PWD_/WarpDrive/basesystem/sdlfontmanager.cpp        \
    $$_PRO_FILE_PWD_/WarpDrive/display/sprite.cpp                   \
    $$_PRO_FILE_PWD_/WarpDrive/display/texturesheet.cpp             \
    $$_PRO_FILE_PWD_/WarpDrive/basemaths/ray.cpp                    \
    $$_PRO_FILE_PWD_/WarpDrive/physics/bruteforcecollision.cpp      \
    $$_PRO_FILE_PWD_/WarpDrive/physics/rdccollision.cpp


