cmake_minimum_required(VERSION 3.5)
project(octachore)

# set(CMAKE_CXX_STANDARD 14)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules/")
find_package(Boost REQUIRED COMPONENTS filesystem REQUIRED)
find_package(Tesseract REQUIRED)
find_package(Leptonica REQUIRED)
include_directories(
        ${Boost_INCLUDE_DIRS}
        ${TESSERACT_INCLUDE_DIRS}
        ${LEPTONICA_INCLUDE_DIRS}
        ${CMAKE_SOURCE_DIR}/src
        ${CMAKE_JS_INC}
)

message(dir: "${PROJECT_SOURCE_DIR}")
file(GLOB SOURCE_FILES "src/*.cpp" "src/*.hpp")
add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} ${CMAKE_JS_LIB})
target_link_libraries(${PROJECT_NAME} ${TESSERACT_LIBRARY})
target_link_libraries(${PROJECT_NAME} ${LEPTONICA_LIBRARY})

# Gives our library file a .node extension without any "lib" prefix
set_target_properties(${PROJECT_NAME} PROPERTIES PREFIX "" SUFFIX ".node")

# Essential include files to build a node addon,
# You should add this line in every CMake.js based project
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_JS_INC})

# Essential library files to link to a node addon
# You should add this line in every CMake.js based project


