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
file(GLOB HEADERS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
     "*.h")
include_directories("ogdf")
qt5_wrap_cpp(MOC_SOURCES ${HEADERS})
add_library(ogdfplugin SHARED ${SOURCES} ${MOC_SOURCES} ${OGDF_SOURCES})
if(WIN32)
    target_link_libraries(ogdfplugin "Psapi.lib")
endif()
qt5_use_modules(ogdfplugin Gui Quick)

# Add demo.
file(GLOB DEMO_SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
    "demo/main.cpp")
file(GLOB DEMO_QRC_SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
    "demo/main.qrc")
file(GLOB DEMO_QML RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
    "demo/qml/*.qml")
qt5_add_resources(DEMO_QRC_SOURCES "demo/main.qrc")
add_executable(ogdf-demo WIN32 "demo/main.cpp" ${DEMO_QRC_SOURCES} ${DEMO_QML})
target_link_libraries(ogdf-demo ${Qt5Core_QTMAIN_LIBRARIES})
qt5_use_modules(ogdf-demo Gui Quick)

# Get path to demo and copy plug-in there.
get_target_property(DEMO_DIR ogdf-demo LOCATION)
get_filename_component(DEMO_DIR ${DEMO_DIR} PATH)
add_custom_target(ogdfplugindir ALL
    COMMAND ${CMAKE_COMMAND} -E make_directory "${DEMO_DIR}/OGDF"
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:ogdfplugin> "${DEMO_DIR}/OGDF"
    COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_SOURCE_DIR}/qmldir" "${DEMO_DIR}/OGDF")
add_dependencies(ogdf-demo ogdfplugindir)
