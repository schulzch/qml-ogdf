#
# CMake listfile to specify the build process, see:
# http://www.cmake.org/cmake/help/documentation.html
#
project(OGDF-DEMO)

# Add QML OGDF demo target.
file(GLOB DEMO_SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
    "*.h" "*.cpp")
file(GLOB DEMO_QRC_SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
    "main.qrc")
file(GLOB DEMO_QML RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
    "qml/*.qml" "qml/*.js")
find_package(Qt5Quick REQUIRED)
qt5_add_resources(DEMO_QRC_SOURCES "main.qrc")
add_executable(ogdf-demo WIN32 "main.cpp" ${DEMO_QRC_SOURCES} ${DEMO_QML})
target_link_libraries(ogdf-demo)
set_target_properties(ogdf-demo PROPERTIES PROJECT_LABEL "demo")
qt5_use_modules(ogdf-demo Quick)

# Get path to demo and copy plug-in there.
get_target_property(DEMO_DIR ogdf-demo LOCATION)
get_filename_component(DEMO_DIR ${DEMO_DIR} PATH)
add_custom_target(ogdfplugindir ALL
    COMMAND ${CMAKE_COMMAND} -E make_directory "${DEMO_DIR}/OGDF"
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:ogdfplugin> "${DEMO_DIR}/OGDF"
    COMMAND ${CMAKE_COMMAND} -E copy "${OGDFPLUGIN_SOURCE_DIR}/EdgeSpline.qml" "${DEMO_DIR}/OGDF"
    COMMAND ${CMAKE_COMMAND} -E copy "${OGDFPLUGIN_SOURCE_DIR}/GraphView.qml" "${DEMO_DIR}/OGDF"
    COMMAND ${CMAKE_COMMAND} -E copy "${OGDFPLUGIN_SOURCE_DIR}/qmldir" "${DEMO_DIR}/OGDF")
add_dependencies(ogdf-demo ogdfplugindir)
