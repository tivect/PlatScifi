cmake_minimum_required(VERSION 3.16)
project(PlatScifi LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

# Add all source files
# TODO: glob?
add_executable(PlatScifi
    src/main.cpp
    src/constants.h
    src/renderdata.h
    src/worldobject.cpp
    src/worldobject.h
    src/assethandler.cpp
    src/assethandler.h
    src/renderer.cpp
    src/renderer.h
    src/worldstate.cpp
    src/worldstate.h
    src/worldspawner.cpp
    src/worldspawner.h
    src/worldobjectincludes.h
    src/worldobjects/redcube.h
    src/worldobjects/bluecube.h
    src/worldobjects/stationaryimage.h
    src/worldobjects/player.h
    src/worldobjects/staticcollider.h
    src/worldobjects/movingcollider.h
    src/worldobjects/staticdeadly.h
    src/worldobjects/leveltp.h
    src/worldobjects/spike.h
    src/worldobjects/animal.cpp
    src/worldobjects/player.cpp
    src/gamestate.cpp
    src/gamestate.h
)
target_link_libraries(PlatScifi PRIVATE sfml-graphics)
target_compile_features(PlatScifi PRIVATE cxx_std_17)

if(WIN32)
    add_custom_command(
        TARGET PlatScifi
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:PlatScifi>
        VERBATIM)
endif()

install(TARGETS PlatScifi)

# Copy over the assets folder
# TODO: use a GLOB
set(ASSETS
	essential.txt
	tiv_logo.png
	grass1.png
    sand.png
	yellowpad.png
	spike.png
	level_0.csv
	level_1.csv
	level_2.csv
	level_design.csv
	LiberationSans-Regular.ttf
	enemy_bird_0.png
	enemy_bird_1.png
    enemy_fipa_0.png
    enemy_replicator_0.png
    enemy_replicator_1.png
    enemy_replicator_2.png
    enemy_addax_0.png
    enemy_addax_1.png
)

foreach(ASSET ${ASSETS})
    # This makes files, but corrupts image files
    # file(GENERATE OUTPUT "bin/Debug/assets/${ASSET}" INPUT "src/assets/${ASSET}")
    # file(GENERATE OUTPUT "bin/Release/assets/${ASSET}" INPUT "src/assets/${ASSET}")
    # This correctly copies the asset into the build assets folder:
	file(COPY "src/assets/${ASSET}" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/bin/Debug/assets/")
	file(COPY "src/assets/${ASSET}" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/bin/Release/assets/")
endforeach()
