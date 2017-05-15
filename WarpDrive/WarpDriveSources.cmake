########################################################
# This file lists the sources for Warp Drive
# It is merely a convenience to unclutter the main list
#
# ~Vile Lasagna
#
########################################################



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
                                3dmaths/vertexbuffer.hpp
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

                                display/animsheet.hpp
                                display/camera.hpp
                                display/colour.hpp
                                display/glshader.hpp
                                display/sdlimage.hpp
                                display/rgbacolour.hpp
                                display/rgbcolour.hpp
                                display/sdlttf.hpp
                                display/sprite.hpp
                                display/texture.hpp
                                display/texturesheet.hpp
                                display/vertexarray.hpp
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
                                physics/bruteforcecollisioncheck.hpp
                                physics/collisionsystem.hpp
                                physics/octree.hpp
                                physics/rdccollisioncheck.hpp
                                physics/rbpcollision.hpp
                                physics/voxelgrid.hpp
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
                        3dmaths/vertexbuffer.cpp
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
                        basemaths/ray.cpp
                        basemaths/sphere.cpp

                        basesystem/configloader.cpp
                        basesystem/displaymanager.cpp
                        basesystem/err.cpp
                        basesystem/filemanager.cpp
                        basesystem/game.cpp
                        basesystem/gameobject.cpp
                        basesystem/gamestate.cpp
                        basesystem/managedfile.cpp
                        basesystem/memory.cpp
                        basesystem/score.cpp
                        basesystem/stringproc.cpp
                        basesystem/ttfmanager.cpp
                        basesystem/sdleventhandler.cpp
                        basesystem/sdlfontmanager.cpp
                        basesystem/util.cpp

                        display/animsheet.cpp
                        display/camera.cpp
                        display/glshader.cpp
                        display/sdlimage.cpp
                        display/sdlttf.cpp
                        display/texture.cpp
                        display/sprite.cpp
                        display/texturesheet.cpp
                        display/vertexarray.cpp

                        events/glcolorevent.cpp
                        events/objectevent.cpp
                        events/panandtiltevent.cpp
                        events/timedmoveevent.cpp
                        events/timedremoveevent.cpp
                        events/timeline.cpp
                        events/tkmoveobject.cpp
                        events/tkuseobject.cpp
                        events/timelinekey.cpp

                        physics/alignedboundingbox.cpp
                        physics/bruteforcecollisioncheck.cpp
                        physics/collisionsystem.cpp
                        physics/rdccollisioncheck.cpp
                        physics/rbpcollision.cpp

                        sound/soundfx.cpp
                        sound/soundmanager.cpp
        )
