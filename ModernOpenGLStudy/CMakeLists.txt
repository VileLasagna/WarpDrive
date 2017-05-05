cmake_minimum_required(VERSION 3.7)
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
                    yaranaika.jpeg  )

add_custom_target(Assets SOURCES ${GLSTUDY_ASSETS})


add_executable(${PROJECT_NAME} ${GLSTUDY_SOURCES} ${GLSTUDY_HEADERS})
add_dependencies(${PROJECT_NAME} WarpDrive)
#install(FILES ${GLSTUDY_SHADERS} ${GLSTUDY_ASSETS} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
#install(FILES ${GLSTUDY_SHADERS}
#       DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/shaders)

#install(FILES ${GLSTUDY_ASSETS}
#           DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/assets)


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
