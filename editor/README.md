# libs #

[Yaml](https://github.com/jbeder/yaml-cpp/) and Qt5 (sudo apt-get install qt5-default).

# How to Build #

editor uses [CMake](http://www.cmake.org) to support cross-platform building. The basic steps to build are:

1. Download and install [CMake](http://www.cmake.org) (Resources -> Download).

**Note:** If you don't use the provided installer for your platform, make sure that you add CMake's bin folder to your path.

2. Navigate into the source directory, and type:

```
mkdir build
cd build
```

3. Run CMake. The basic syntax is:

```
cmake ..
```
  * For more options on customizing the build, see the [CMakeLists.txt](https://github.com/jbeder/yaml-cpp/blob/master/CMakeLists.txt) file.

4. Build it!

5. To clean up, just remove the `build` directory.

# How to excute #

./editor
