cmake_minimum_required(VERSION 3.10)
project(Snake_Game)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(Snake_Game src/main.cpp
    src/basics.cpp
    src/field/field.cpp
    src/field/fruit/fruit.cpp
    src/field/snake/snake.cpp
)

INCLUDE(FindPkgConfig)

PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
PKG_SEARCH_MODULE(SDL2TTF REQUIRED SDL2_ttf)

target_link_libraries(Snake_Game PRIVATE ${SDL2_LIBRARIES} ${SDL2TTF_LIBRARIES})
target_include_directories(Snake_Game PUBLIC
    ${SDL2_INCLUDE_DIRS}
    ${SDL2TTF_INCLUDE_DIRS}
    "${PROJECT_SOURCE_DIR}/src"
    "${PROJECT_SOURCE_DIR}/src/field"
    "${PROJECT_SOURCE_DIR}/src/field/fruit"
    "${PROJECT_SOURCE_DIR}/src/field/snake"
)

add_custom_target(assets)
FILE(TO_NATIVE_PATH "${PROJECT_SOURCE_DIR}/assets" source)
FILE(TO_NATIVE_PATH "${PROJECT_BINARY_DIR}/assets" destination)

IF(WIN32)
    add_custom_command(
        TARGET assets POST_BUILD
        COMMAND mklink /D ${destination} ${source}
        DEPENDS ${destination}
        COMMENT "symbolic link assets folder from ${source} => ${destination}"
    )
ELSE()
    add_custom_command(
        TARGET assets POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E create_symlink ${source} ${destination}
        DEPENDS ${destination}
        COMMENT "symbolic link assets folder from ${source} => ${destination}"
    )
ENDIF()
