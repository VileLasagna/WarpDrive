cmake_minimum_required(VERSION 3.7)
project(RigidCollisionDemo)

set(RIGIDCOLDEMO_HEADERS    ${RIGIDCOLDEMO_HEADERS}
                            ball.hpp
                            launcherstate.hpp   )

set(RIGIDCOLDEMO_SOURCES    ${RIGIDCOLDEMO_SOURCES}
                            ball.cpp
                            launcherstate.cpp
                            main.cpp    )
add_executable(${PROJECT_NAME} ${RIGIDCOLDEMO_SOURCES} ${RIGIDCOLDEMO_HEADERS})
add_dependencies(${PROJECT_NAME} WarpDrive)
target_link_libraries(RigidCollisionDemo WarpDrive)