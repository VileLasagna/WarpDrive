cmake_minimum_required(VERSION 3.7)
project(ModernGLStudy)

set(GLSTUDY_SOURCES    ${GLSTUDY_SOURCES}
                        gldemostate.hpp   )

set(GLSTUDY_HEADERS    ${GLSTUDY_HEADERS}
                        gldemostate.cpp
                        main.cpp    )

set(GLSTUDY_SHADERS ${GLSTUDY_SHADERS}
                    fragtest1.frag
                    verttest1.vert)

add_executable(${PROJECT_NAME} ${GLSTUDY_SOURCES} ${GLSTUDY_HEADERS})
add_dependencies(${PROJECT_NAME} WarpDrive)
install(FILES ${GLSTUDY_SHADERS} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
target_link_libraries(${PROJECT_NAME} WarpDrive)
