cmake_minimum_required(VERSION 3.16)

project(PAC-MAN LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

add_executable(PAC-MAN src/main.cpp "src/Game Representation/Game.cpp" "src/Game Representation/Game.h" "src/Game Representation/Game.h" "src/Game Representation/EntityView.cpp" "src/Game Representation/EntityView.h" "src/Game Representation/Camera.cpp" "src/Game Representation/Camera.h" "src/Game Representation/ConcreteFactory.cpp" "src/Game Representation/ConcreteFactory.h" "src/Game Representation/State.cpp" "src/Game Representation/State.h" "src/Game Representation/StateManager.cpp" "src/Game Representation/StateManager.h" "src/Logic Library/Subject.cpp" "src/Logic Library/Subject.h" "src/Logic Library/Random.cpp" "src/Logic Library/Random.h" "src/Logic Library/Stopwatch.cpp" "src/Logic Library/Stopwatch.h" "src/Logic Library/World.cpp" "src/Logic Library/World.h" "src/Logic Library/EntityModel.cpp" "src/Logic Library/EntityModel.h" "src/Logic Library/AbstractFactory.cpp" "src/Logic Library/AbstractFactory.h" "src/Game Representation/States/MenuState.cpp" "src/Game Representation/States/MenuState.h" "src/Game Representation/States/LevelState.cpp" "src/Game Representation/States/LevelState.h" "src/Game Representation/States/PausedState.cpp" "src/Game Representation/States/PausedState.h" "src/Game Representation/States/VictoryState.cpp" "src/Game Representation/States/VictoryState.h" "src/Game Representation/States/GameOverState.cpp" "src/Game Representation/States/GameOverState.h" "src/Logic Library/Score.cpp" "src/Logic Library/Score.h" "src/Logic Library/Observer.cpp" "src/Logic Library/Observer.h" src/enum.h "src/Logic Library/Models/Ghost.cpp" "src/Logic Library/Models/Ghost.h" "src/Logic Library/Models/Wall.cpp" "src/Logic Library/Models/Wall.h" "src/Logic Library/Models/Collectable.cpp" "src/Logic Library/Models/Collectable.h" "src/Logic Library/Models/PacMan.cpp" "src/Logic Library/Models/PacMan.h")
target_link_libraries(PAC-MAN PRIVATE sfml-graphics)
target_compile_features(PAC-MAN PRIVATE cxx_std_17)

if(WIN32)
    add_custom_command(
        TARGET PAC-MAN
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:PAC-MAN>
        VERBATIM)
endif()

install(TARGETS PAC-MAN)
