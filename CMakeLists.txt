#
# CMake listfile to specify the build process, see:
# http://www.cmake.org/cmake/help/documentation.html
#
project(QML-OGDF)

# Require CMake 2.8.0+.
cmake_minimum_required(VERSION 2.8.0)

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

# Setup Qt5.
find_package(Qt5Gui REQUIRED)
find_package(Qt5Quick REQUIRED)
add_definitions(-DQT_PLUGIN)
add_definitions(-DQT_SHARED)

# Add OGDF plug-in.
file(GLOB_RECURSE OGDF_SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
    "ogdf/*.cpp" "ogdf/*.h")
file(GLOB SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
    "*.cpp" "*.h" "qmldir")
include_directories("ogdf")
qt5_wrap_cpp(MOC_SOURCES ${SOURCES})
add_library(ogdfplugin SHARED ${SOURCES} ${MOC_SOURCES} ${OGDF_SOURCES})
if(WIN32)
    target_link_libraries(ogdfplugin "Psapi.lib")
endif()
qt5_use_modules(ogdfplugin Gui Quick)

# Add example.
file(GLOB EXAMPLE_SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
    "example/main.cpp")
file(GLOB EXAMPLE_QRC_SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
    "example/main.qrc")
file(GLOB EXAMPLE_QML RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
    "example/*.qml")
qt5_add_resources(EXAMPLE_QRC_SOURCES "example/main.qrc")
add_executable(qml-ogdf WIN32 "example/main.cpp" ${EXAMPLE_QRC_SOURCES} ${EXAMPLE_QML})
target_link_libraries(qml-ogdf ${Qt5Core_QTMAIN_LIBRARIES})
qt5_use_modules(qml-ogdf Gui Quick)

# Get path to executable.
get_target_property(EXAMPLE_DIR qml-ogdf LOCATION)
get_filename_component(EXAMPLE_DIR ${EXAMPLE_DIR} PATH)

# Copy plug-in to executable.
add_custom_target(ogdfplugindir ALL
    COMMAND ${CMAKE_COMMAND} -E make_directory "${EXAMPLE_DIR}/OGDF"
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:ogdfplugin> "${EXAMPLE_DIR}/OGDF"
    COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_SOURCE_DIR}/qmldir" "${EXAMPLE_DIR}/OGDF")
add_dependencies(qml-ogdf ogdfplugindir)
