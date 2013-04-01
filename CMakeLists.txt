#
# CMake listfile to specify the build process, see:
# http://www.cmake.org/cmake/help/documentation.html
#
project(QML-OGDF)

# Require CMake 2.8.10+ for Qt5 support.
cmake_minimum_required(VERSION 2.8.10)

# Check for polluted source tree.
if(EXISTS ${CMAKE_SOURCE_DIR}/CMakeCache.txt OR
    EXISTS ${CMAKE_SOURCE_DIR}/CMakeFiles)
    message(FATAL_ERROR
        "Source directory is polluted:"
        "\n  * remove CMakeCache.txt"
        "\n  * remove CMakeFiles directory")
endif()

# Suppress in-source builds.
if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
    message(FATAL_ERROR
        "CMake generation is not allowed within the source directory:"
        "\n  * mkdir build"
        "\n  * cd build"
        "\n  * Unix-like: cmake -G \"Unix Makefiles\" .."
        "\n  * Windows: cmake -G \"Visual Studio 10\" ..")
endif()

# Add QML OGDF plug-in target.
file(GLOB_RECURSE OGDF_SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
    "ogdf/*.cpp" "ogdf/*.h")
file(GLOB SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
    "*.cpp" "*.h" "qmldir")
file(GLOB HEADERS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
     "*.h")
find_package(Qt5Qml REQUIRED)
include_directories("ogdf")
qt5_wrap_cpp(MOC_SOURCES ${HEADERS})
add_library(ogdfplugin SHARED ${SOURCES} ${MOC_SOURCES} ${OGDF_SOURCES})
set_target_properties(ogdfplugin PROPERTIES
    COMPILE_DEFINITIONS "OGDF_MEMORY_MALLOC_TS")
if(WIN32)
    target_link_libraries(ogdfplugin "Psapi.lib")
endif()
qt5_use_modules(ogdfplugin Qml)

# Add optional sub-projects.
if(EXISTS "demo/")
    add_subdirectory(demo)
endif()
