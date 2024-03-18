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
add_executable(PlatScifi
    src/main.cpp
    src/renderdata.h
    src/worldobject.cpp
    src/worldobject.h
    src/renderer.cpp
    src/renderer.h
    src/worldstate.cpp
    src/worldstate.h
    src/worldobjects/redcube.h
    src/worldobjects/bluecube.h
    src/worldobjects/stationaryimage.h
)
target_link_libraries(PlatScifi PRIVATE sfml-graphics)
target_compile_features(PlatScifi PRIVATE cxx_std_17)

# Copy over the assets folder
set(ASSETS
    testtex.txt
    tiv_logo.png
    tiv_logo.txt
    screenshot.jpg
)

foreach(ASSET ${ASSETS})
    # This makes files, but corrupts image files
    file(GENERATE OUTPUT "bin/Debug/assets/${ASSET}" INPUT "src/assets/${ASSET}")
    file(GENERATE OUTPUT "bin/Release/assets/${ASSET}" INPUT "src/assets/${ASSET}")
    # This does not work:
    # file(COPY "src/assets/${ASSET}" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/bin/Debug/assets/${ASSET}")
    # file(COPY "src/assets/${ASSET}" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/bin/Release/assets/${ASSET}")
endforeach()

# foreach(ASSET ${ASSETS})

# add_custom_command(TARGET PlatScifi POST_BUILD
#     COMMAND ${CMAKE_COMMAND} -E copy_directory
#     ${PROJECT_SOURCE_DIR}/assets
#     ${PROEJCT_BINARY_DIR}/assets
# )

# add_custom_target(copy_resources ALL
#     COMMAND ${CMAKE_COMMAND} -E copy_directory
#     ${PROJECT_SOURCE_DIR}/assets
#     ${CMAKE_CURRENT_BINARY_DIR}/assets
#     COMMENT "Copying resources into binary directory"
# )
# add_dependencies(PlatScifi copy_resources)


if(WIN32)
    add_custom_command(
        TARGET PlatScifi
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:PlatScifi>
        VERBATIM)
endif()

install(TARGETS PlatScifi)
