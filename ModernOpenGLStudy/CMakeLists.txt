cmake_minimum_required(VERSION 3.8)
project(ModernGLStudy)

set(GLSTUDY_SOURCES    ${GLSTUDY_SOURCES}
                        gldemostate.hpp   )

set(GLSTUDY_HEADERS    ${GLSTUDY_HEADERS}
                        gldemostate.cpp
                        main.cpp    )

set(GLSTUDY_SHADERS ${GLSTUDY_SHADERS}
                    fragtest1.frag
                    verttest1.vert  )

add_custom_target(Shaders SOURCES ${GLSTUDY_SHADERS})

set(GLSTUDY_ASSETS ${GLSTUDY_ASSETS}
                    yaranaika.jpeg
                    konodio.jpeg
                    diemap.png      )

add_custom_target(Assets SOURCES ${GLSTUDY_ASSETS})


add_executable(${PROJECT_NAME} ${GLSTUDY_SOURCES} ${GLSTUDY_HEADERS})
add_dependencies(${PROJECT_NAME} WarpDrive)

target_link_libraries(${PROJECT_NAME} WarpDrive)

install(TARGETS ${PROJECT_NAME}
        DESTINATION bin
        COMPONENT OpenGLStudy )

install(FILES ${GLSTUDY_SHADERS}
        DESTINATION bin/shaders
        COMPONENT OpenGLStudy )

install(FILES ${GLSTUDY_ASSETS}
        DESTINATION bin/assets
        COMPONENT OpenGLStudy )
