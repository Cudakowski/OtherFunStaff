if ("${CMAKE_SOURCE_DIR}" STREQUAL "${CMAKE_BINARY_DIR}")
  message(FATAL_ERROR "In-source builds are not allowed.")
endif ()

cmake_minimum_required(VERSION 3.21 FATAL_ERROR)

set(CMAKE_CXX_FLAGS_DEBUG_INIT "-Wall -fdiagnostics-color=always -g -ggdb -pedantic-errors -Weffc++ -Wextra -Wconversion -Wsign-conversion -Werror -Wshadow")
set(CMAKE_CXX_FLAGS_RELEASE_INIT "-Wall -fdiagnostics-color=always -g -O2 -DNDEBUG -pedantic-errors -Weffc++ -Wextra -Wconversion -Wsign-conversion -Werror -Wshadow")
#CHANGE: change above flags
    # "-Werror", treat warnings as errors
    # "-std=c++23", force c++23 standard ; set lower if needed
    # "-Wshadow", warn about shadowing
    
get_filename_component(PARENT_DIR_NAME "${CMAKE_CURRENT_SOURCE_DIR}" NAME)
    
project(${PARENT_DIR_NAME} LANGUAGES CXX) 
set(${PROJECT_NAME}_VERSION_MAJOR  0)
set(${PROJECT_NAME}_VERSION_MINOR  0)
set(${PROJECT_NAME}_VERSION_PATCH  0)
set(${PROJECT_NAME}_VERSION_TWEAK  0)
set(${PROJECT_NAME}_VERSION "${${PROJECT_NAME}_VERSION_MAJOR}.${${PROJECT_NAME}_VERSION_MINOR}.${${PROJECT_NAME}_VERSION_PATCH}.${PROJECT_NAME}_VERSION_TWEAK")


#EXPLAIN: prevent for in-source building
set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)
set(CMAKE_DISABLE_SOURCE_CHANGES  ON)                   #EXPLAIN: “Don’t allow this project to modify files in the source directory during configuration or build.

#CHANGE: Change to "Release" if needed
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)                           #EXPLAIN: disables -std=gnu++23 and leaves -std=c++23

file(GLOB SOURCES "${PROJECT_SOURCE_DIR}/src/*.cpp")    #EXPLAIN: getting all source files
add_executable(${PROJECT_NAME} ${SOURCES})              #EXPLAIN: setting sources to found ones
#add_subdirectory()                                     #EXPLAIN: thats a surprise tool thats gonna help us later ;)

#EXPLAIN: Add includes
target_include_directories(${PROJECT_NAME} PUBLIC 
    "${PROJECT_SOURCE_DIR}/include"
)

#EXPLAIN: Add preprocessor definitions
target_compile_definitions(${PROJECT_NAME} PRIVATE 
    $<$<CONFIG:Debug>:DEBUG_BUILD>
)
