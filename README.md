# OGDF for QML

This plug-in provides a binding of [Open Graph Drawing Framework](http://www.ogdf.net) to [QtQML](http://qt-project.org/doc/qt-5.0/qtqml/qtqml-index.html).

*Note: it's is quite useable, but far from mature (read: APIs may change)!*

## Features

- A wide range of graph drawing and layout algorithms
    - FMMM
    - More available, but not bound (TODO)
- A module mechanism to reuse and replace particular algorithm phases (TODO)
- Easy to use - it's QML after all

## Building

You need to have a C++ compiler, [Qt 5.0+](https://qt-project.org/downloads) and [CMake 2.8.10+](http://www.cmake.org/) installed. 

Start [Qt Creator](http://qt-project.org/downloads#qt-creator), open `CMakeLists.txt` as new project, follow the instructions, hit compile and you're done. Alternatively you can use CMake from the command line as follows:

1. Open up a terminal and navigate to the root directory
2. Create a build directory using `mkdir build; cd build`
3. Configure using `cmake -G "Unix Makefiles" ..`
4. Build using `make`

It's worth mentioning that `Unix Makefiles` can be replaced with your favorite CMake generator. See `cmake --help` or [online documentation](http://cmake.org/cmake/help/v2.8.10/cmake.html#section_Generators) for a list of available generators.

## Quick Start

Once build, you can start `ogdf-demo` to find out what algorithms are available and how to use them.

To use the plug-in in your own project, you need to compile an `OGDF` directory and copy it to your application's working directory as follows:

    OGDF/              -- plug-in directory
      ogdfplugin.so    -- compiled plug-in (Linux only)
      ogdfplugin.dylib -- compiled plug-in (OS X only)
      ogdfplugin.dll   -- compiled plug-in (Windows only)
      qmldir           -- module definition file

## License

Licensed under the [GNU Lesser General Public License](http://en.wikipedia.org/wiki/GNU_Lesser_General_Public_License) [Version 2.1](http://www.gnu.org/licenses/old-licenses/lgpl-2.1) or [Version 3.0](http://www.gnu.org/licenses/lgpl-3.0). Copyright (c) 2013 Christoph Schulz.

Note: OGDF is licensed under the [GNU General Public License](http://en.wikipedia.org/wiki/GNU_General_Public_License) [Version 2.0](http://www.gnu.org/licenses/old-licenses/gpl-2.0) or [Version 3.0](http://www.gnu.org/licenses/gpl-3.0). They kindly grand an exception to compile OGDF into this software and distribute it under weaker terms to prevent you from having legal issues when using this plug-in.
