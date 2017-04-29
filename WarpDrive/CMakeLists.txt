cmake_minimum_required(VERSION 3.7)
project(WarpDrive)

set(WARPDRIVE_HEADERS   ${WARPDRIVE_HEADERS}
                        3dmaths/billboard.hpp
                        3dmaths/glm.h
                        3dmaths/glmesh.hpp
                        3dmaths/glmint.h
                        3dmaths/material.hpp
                        3dmaths/model.hpp
                        3dmaths/modelloader.hpp
                        3dmaths/vertex.hpp
                        3dmaths/viewport.hpp
                        
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
                        
                        physics/alignedboundingbox.hpp
                        physics/collisionsystem.hpp
                        physics/octree.hpp
                        physics/voxelgrid.hpp
                        physics/bruteforcecollisioncheck.hpp
                        physics/rdccollisioncheck.hpp
                        physics/rbpcollision.hpp
                        
                        sound/soundfx.hpp
                        sound/soundmanager.hpp
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

add_library(${PROJECT_NAME} ${WARPDRIVE_HEADERS} ${WARPDRIVE_SOURCES})
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
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_LIST_DIR} ${CMAKE_CURRENT_LIST_DIR}/..)

set(CMAKE_THREAD_PREFER_PTHREAD ON)
find_package(Threads)
target_link_libraries(${PROJECT_NAME} INTERFACE Threads::Threads)

find_package(OpenGL)
target_link_libraries(${PROJECT_NAME} INTERFACE ${OPENGL_LIBRARIES})

find_package(GLEW)
target_link_libraries(${PROJECT_NAME} INTERFACE GLEW::GLEW)
