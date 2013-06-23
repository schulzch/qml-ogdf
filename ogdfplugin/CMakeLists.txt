#
# CMake listfile to specify the build process, see:
# http://www.cmake.org/cmake/help/documentation.html
#
project(OGDFPLUGIN)

# Add QML OGDF plug-in target.
file(GLOB_RECURSE OGDF_SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
    "ogdf/*.cpp" "ogdf/*.h")
file(GLOB SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
    "*.cpp" "*.h" "*.qml" "qmldir")
file(GLOB HEADERS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
     "*.h")
list(REMOVE_ITEM OGDF_SOURCES "ogdf/src/coin/Osi/OsiGrbSolverInterface.cpp")
list(REMOVE_ITEM OGDF_SOURCES "ogdf/src/coin/Osi/OsiCpxSolverInterface.cpp")
find_package(Qt5Qml REQUIRED)
include_directories("ogdf/include")
include_directories("ogdf/include/coin")
qt5_wrap_cpp(MOC_SOURCES ${HEADERS})
add_library(ogdfplugin SHARED ${SOURCES} ${MOC_SOURCES} ${OGDF_SOURCES})
set(OGDF_DEFINES
    "CLP_BUILD"
    "COINUTILS_BUILD"
    "OSI_BUILD"
    "SYMPHONY_BUILD"
    "__OSI_CLP__"
    "COMPILE_IN_CG"
    "COMPILE_IN_CP"
    "COMPILE_IN_LP"
    "COMPILE_IN_TM"
    "USE_CGL_CUTS")
if(WIN32)
    list(APPEND OGDF_DEFINES
        "_CRT_SECURE_NO_WARNINGS"
        "_SCL_SECURE_NO_WARNINGS")
    target_link_libraries(ogdfplugin "Psapi.lib")
else()
    list(APPEND OGDF_DEFINES
        "HAVE_CONFIG_H")
endif()
set_target_properties(ogdfplugin PROPERTIES
    COMPILE_DEFINITIONS "${OGDF_DEFINES}")
qt5_use_modules(ogdfplugin Qml)
