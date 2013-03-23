# OGDF for QML

This plug-in provides a binding of [Open Graph Drawing Framework](http://www.ogdf.net) to [QtQML](http://qt-project.org/doc/qt-5.0/qtqml/qtqml-index.html).

*Note: this plug-in is quite useable, but it's far from mature (read: it's API may change)!*

## Features

- A wide range of graph drawing and layout algorithms
    - FMMM
    - More available, but not bound (TODO)
- A module mechanism to reuse and replace particular algorithm phases (TODO)
- Easy to use - it's QML after all

## Building

You need to have a C++ compiler, [Qt 5.0+](https://qt-project.org/downloads) and [CMake 2.8+](http://www.cmake.org/) installed. 

Start [Qt Creator](http://qt-project.org/downloads#qt-creator), open `CMakeLists.txt` as new project and follow the instructions.

Alternatively you can use CMake from the command line:

1. Open up a terminal and navigate to the root directory of the project
2. Create a build directory: `mkdir build; cd build`
3. Generate project files: `cmake -G "Unix Makefiles" ..`
4. Compile project: `make`

It's worth mentioning that `"Unix Makefiles"` can be replaced with your favorite CMake generator (e.g. `"Visual Studio 10"`). See `cmake --help` for a list of available generators.

## Quick Start

Once build, you should start by running the `qml-ogdf` example in your build directory. Find out what algorithms you want to use and look at the `*.qml`.

To use the compiled plug-in you need to create an `OGDF` directory in your project's working directory and copy some files to it. This process is automated for the example.

    OGDF/              -- plug-in directory
      ogdfplugin.so    -- compiled plug-in (Linux only)
      ogdfplugin.dylib -- compiled plug-in (OS X only)
      ogdfplugin.dll   -- compiled plug-in (Windows only)
      qmldir           -- module definition file

## License

Licensed under the [GNU Lesser General Public License](http://en.wikipedia.org/wiki/GNU_Lesser_General_Public_License) [Version 2.1](http://www.gnu.org/licenses/old-licenses/lgpl-2.1) or [Version 3.0](http://www.gnu.org/licenses/lgpl-3.0).

Note: OGDF is usually licensed under the [GNU General Public License](http://en.wikipedia.org/wiki/GNU_General_Public_License) [Version 2.0](http://www.gnu.org/licenses/old-licenses/gpl-2.0) or [Version 3.0](http://www.gnu.org/licenses/gpl-3.0). They kindly grand an exception compile OGDF into this software and distribute it under weaker terms to prevent you from having legal issues when using this plug-in.
