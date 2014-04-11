

HEADERS += \
    $$_PRO_FILE_PWD_/WarpDrive/3DMaths/Billboard.h                \
    $$_PRO_FILE_PWD_/WarpDrive/3DMaths/glm.h                      \
    $$_PRO_FILE_PWD_/WarpDrive/3DMaths/GLMesh.h                   \
    $$_PRO_FILE_PWD_/WarpDrive/3DMaths/glmint.h                   \
    $$_PRO_FILE_PWD_/WarpDrive/3DMaths/Material.h                 \
    $$_PRO_FILE_PWD_/WarpDrive/3DMaths/Model.h                    \
    $$_PRO_FILE_PWD_/WarpDrive/3DMaths/ModelLoader.h              \
    $$_PRO_FILE_PWD_/WarpDrive/3DMaths/Teapot.h                   \
    $$_PRO_FILE_PWD_/WarpDrive/3DMaths/Vertex.h                   \
    $$_PRO_FILE_PWD_/WarpDrive/3DMaths/Viewport.h                 \
    $$_PRO_FILE_PWD_/WarpDrive/BaseMaths/Capsule.h                \
    $$_PRO_FILE_PWD_/WarpDrive/BaseMaths/ClipLineSegBox.h         \
    $$_PRO_FILE_PWD_/WarpDrive/BaseMaths/Frustrum.h               \
    $$_PRO_FILE_PWD_/WarpDrive/BaseMaths/LineSeg.h                \
    $$_PRO_FILE_PWD_/WarpDrive/BaseMaths/Matrix44.h               \
    $$_PRO_FILE_PWD_/WarpDrive/BaseMaths/Plane.h                  \
    $$_PRO_FILE_PWD_/WarpDrive/BaseMaths/Quaternion.h             \
    $$_PRO_FILE_PWD_/WarpDrive/BaseMaths/Rect.h                   \
    $$_PRO_FILE_PWD_/WarpDrive/BaseMaths/Sphere.h                 \
    $$_PRO_FILE_PWD_/WarpDrive/BaseMaths/Tri.h                    \
    $$_PRO_FILE_PWD_/WarpDrive/BaseMaths/Vec2.h                   \
    $$_PRO_FILE_PWD_/WarpDrive/BaseMaths/Vec3.h                   \
    $$_PRO_FILE_PWD_/WarpDrive/BaseMaths/Vec4.h                   \
    $$_PRO_FILE_PWD_/WarpDrive/BaseSystem/ConfigLoader.h          \
    $$_PRO_FILE_PWD_/WarpDrive/BaseSystem/DisplayManager.h        \
    $$_PRO_FILE_PWD_/WarpDrive/BaseSystem/Err.h                   \
    $$_PRO_FILE_PWD_/WarpDrive/BaseSystem/Factory.h               \
    $$_PRO_FILE_PWD_/WarpDrive/BaseSystem/FileManager.h           \
    $$_PRO_FILE_PWD_/WarpDrive/BaseSystem/Game.h                  \
    $$_PRO_FILE_PWD_/WarpDrive/BaseSystem/GameObject.h            \
    $$_PRO_FILE_PWD_/WarpDrive/BaseSystem/GameState.h             \
    $$_PRO_FILE_PWD_/WarpDrive/BaseSystem/ManagedFile.h           \
    $$_PRO_FILE_PWD_/WarpDrive/BaseSystem/Memory.h                \
    $$_PRO_FILE_PWD_/WarpDrive/BaseSystem/OBJLoader.h             \
    $$_PRO_FILE_PWD_/WarpDrive/BaseSystem/Score.h                 \
    $$_PRO_FILE_PWD_/WarpDrive/BaseSystem/StringProc.h            \
    $$_PRO_FILE_PWD_/WarpDrive/BaseSystem/TeapotLoaderState.h     \
    $$_PRO_FILE_PWD_/WarpDrive/BaseSystem/TTFManager.h            \
    $$_PRO_FILE_PWD_/WarpDrive/BaseSystem/SDLEventHandler.h       \
    $$_PRO_FILE_PWD_/WarpDrive/Display/Camera.h                   \
    $$_PRO_FILE_PWD_/WarpDrive/Display/Colour.h                   \
    $$_PRO_FILE_PWD_/WarpDrive/Display/SDLImage.h                 \
    $$_PRO_FILE_PWD_/WarpDrive/Display/SDLRGBAColour.h            \
    $$_PRO_FILE_PWD_/WarpDrive/Display/SDLRGBColour.h             \
    $$_PRO_FILE_PWD_/WarpDrive/Display/SDLTTF.h                   \
    $$_PRO_FILE_PWD_/WarpDrive/Display/Texture.h                  \
    $$_PRO_FILE_PWD_/WarpDrive/Events/glColorEvent.h              \
    $$_PRO_FILE_PWD_/WarpDrive/Events/ObjectEvent.h               \
    $$_PRO_FILE_PWD_/WarpDrive/Events/PanAndTiltEvent.h           \
    $$_PRO_FILE_PWD_/WarpDrive/Events/TimedMoveEvent.h            \
    $$_PRO_FILE_PWD_/WarpDrive/Events/TimedRemoveEvent.h          \
    $$_PRO_FILE_PWD_/WarpDrive/Events/Timeline.h                  \
    $$_PRO_FILE_PWD_/WarpDrive/Events/TimelineKey.h               \
    $$_PRO_FILE_PWD_/WarpDrive/Events/TKAddEvent.h                \
    $$_PRO_FILE_PWD_/WarpDrive/Events/TKDrawTeapot.h              \
    $$_PRO_FILE_PWD_/WarpDrive/Events/TKMoveObject.h              \
    $$_PRO_FILE_PWD_/WarpDrive/Events/TKPlayMusic.h               \
    $$_PRO_FILE_PWD_/WarpDrive/Events/TKUseObject.h               \
    $$_PRO_FILE_PWD_/WarpDrive/Physics/BoundingBox.h              \
    $$_PRO_FILE_PWD_/WarpDrive/Physics/CollisionSystem.h          \
    $$_PRO_FILE_PWD_/WarpDrive/Physics/Octree.h                   \
    $$_PRO_FILE_PWD_/WarpDrive/Physics/VoxelGrid.h                \
    $$_PRO_FILE_PWD_/WarpDrive/Sound/SoundFX.h                    \
    $$_PRO_FILE_PWD_/WarpDrive/Sound/SoundManager.h               \
    $$_PRO_FILE_PWD_/WarpDrive/Display/AnimSheet.h                \
    $$_PRO_FILE_PWD_/WarpDrive/BaseSystem/SDLFontManager.h        \
    $$_PRO_FILE_PWD_/WarpDrive/Display/Sprite.h                   \
    $$_PRO_FILE_PWD_/WarpDrive/Display/TextureSheet.h


SOURCES += \
    $$_PRO_FILE_PWD_/WarpDrive/3DMaths/Billboard.cpp              \
    $$_PRO_FILE_PWD_/WarpDrive/3DMaths/GLMesh.cpp                 \
    $$_PRO_FILE_PWD_/WarpDrive/3DMaths/Material.cpp               \
    $$_PRO_FILE_PWD_/WarpDrive/3DMaths/Model.cpp                  \
    $$_PRO_FILE_PWD_/WarpDrive/3DMaths/Vertex.cpp                 \
    $$_PRO_FILE_PWD_/WarpDrive/3DMaths/glm.c                      \
    $$_PRO_FILE_PWD_/WarpDrive/3DMaths/glm_util.c                 \
    $$_PRO_FILE_PWD_/WarpDrive/3DMaths/glmimg.c                   \
    $$_PRO_FILE_PWD_/WarpDrive/3DMaths/glmimg_sdl.c               \
    $$_PRO_FILE_PWD_/WarpDrive/BaseMaths/Capsule.cpp              \
    $$_PRO_FILE_PWD_/WarpDrive/BaseMaths/ClipLineSegBox.cpp       \
    $$_PRO_FILE_PWD_/WarpDrive/BaseMaths/Frustrum.cpp             \
    $$_PRO_FILE_PWD_/WarpDrive/BaseMaths/LineSeg.cpp              \
    $$_PRO_FILE_PWD_/WarpDrive/BaseMaths/Matrix44.cpp             \
    $$_PRO_FILE_PWD_/WarpDrive/BaseMaths/Plane.cpp                \
    $$_PRO_FILE_PWD_/WarpDrive/BaseMaths/Quaternion.cpp           \
    $$_PRO_FILE_PWD_/WarpDrive/BaseMaths/Sphere.cpp               \
    $$_PRO_FILE_PWD_/WarpDrive/BaseSystem/ConfigLoader.cpp        \
    $$_PRO_FILE_PWD_/WarpDrive/BaseSystem/DisplayManager.cpp      \
    $$_PRO_FILE_PWD_/WarpDrive/BaseSystem/Err.cpp                 \
    $$_PRO_FILE_PWD_/WarpDrive/BaseSystem/FileManager.cpp         \
    $$_PRO_FILE_PWD_/WarpDrive/BaseSystem/Game.cpp                \
    $$_PRO_FILE_PWD_/WarpDrive/BaseSystem/GameObject.cpp          \
    $$_PRO_FILE_PWD_/WarpDrive/BaseSystem/ManagedFile.cpp         \
    $$_PRO_FILE_PWD_/WarpDrive/BaseSystem/Memory.cpp              \
    $$_PRO_FILE_PWD_/WarpDrive/BaseSystem/Score.cpp               \
    $$_PRO_FILE_PWD_/WarpDrive/BaseSystem/StringProc.cpp          \
    $$_PRO_FILE_PWD_/WarpDrive/BaseSystem/TeapotLoaderState.cpp   \
    $$_PRO_FILE_PWD_/WarpDrive/BaseSystem/TTFManager.cpp          \
    $$_PRO_FILE_PWD_/WarpDrive/BaseSystem/SDLEventHandler.cpp     \
    $$_PRO_FILE_PWD_/WarpDrive/Display/Camera.cpp                 \
    $$_PRO_FILE_PWD_/WarpDrive/Display/SDLImage.cpp               \
    $$_PRO_FILE_PWD_/WarpDrive/Display/SDLRGBColour.cpp           \
    $$_PRO_FILE_PWD_/WarpDrive/Display/SDLTTF.cpp                 \
    $$_PRO_FILE_PWD_/WarpDrive/Display/Texture.cpp                \
    $$_PRO_FILE_PWD_/WarpDrive/Events/glColorEvent.cpp            \
    $$_PRO_FILE_PWD_/WarpDrive/Events/PanAndTiltEvent.cpp         \
    $$_PRO_FILE_PWD_/WarpDrive/Events/TimedMoveEvent.cpp          \
    $$_PRO_FILE_PWD_/WarpDrive/Events/TimedRemoveEvent.cpp        \
    $$_PRO_FILE_PWD_/WarpDrive/Events/Timeline.cpp                \
    $$_PRO_FILE_PWD_/WarpDrive/Events/TKMoveObject.cpp            \
    $$_PRO_FILE_PWD_/WarpDrive/Events/TKUseObject.cpp             \
    $$_PRO_FILE_PWD_/WarpDrive/Physics/BoundingBox.cpp            \
    $$_PRO_FILE_PWD_/WarpDrive/Sound/SoundFX.cpp                  \
    $$_PRO_FILE_PWD_/WarpDrive/Sound/SoundManager.cpp             \
    $$_PRO_FILE_PWD_/WarpDrive/Display/AnimSheet.cpp              \
    $$_PRO_FILE_PWD_/WarpDrive/BaseSystem/SDLFontManager.cpp      \
    $$_PRO_FILE_PWD_/WarpDrive/Display/Sprite.cpp                 \
    $$_PRO_FILE_PWD_/WarpDrive/Display/TextureSheet.cpp

include ($$_PRO_FILE_PWD_/WarpDrive/include/external.pri)

