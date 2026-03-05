cmake_minimum_required(VERSION 3.15)
project(Captcha)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# SFML 3.0.2 via FetchContent with static linking
set(SFML_BUILD_DOC FALSE CACHE BOOL "" FORCE)
set(SFML_BUILD_EXAMPLES FALSE CACHE BOOL "" FORCE)
set(SFML_BUILD_TESTS FALSE CACHE BOOL "" FORCE)
set(SFML_BUILD_GUI FALSE CACHE BOOL "" FORCE)
set(SFML_STATIC_LIBRARIES TRUE CACHE BOOL "" FORCE)

include(FetchContent)
FetchContent_Declare(
    sfml
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.2
)

# Build SFML explicitly before main project
FetchContent_GetProperties(sfml)
if(NOT sfml_POPULATED)
    FetchContent_Populate(sfml)
    add_subdirectory(${sfml_SOURCE_DIR} ${sfml_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()

add_executable(captcha source/main.cpp)
target_link_libraries(captcha PRIVATE sfml-graphics sfml-system sfml-window)

# Copy assets to build directory
add_custom_command(TARGET captcha POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets
        $<TARGET_FILE_DIR:captcha>/assets
)
