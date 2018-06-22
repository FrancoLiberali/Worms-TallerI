# libs #
Install SDL libs on Linux:

```
sudo apt-get install libsdl2-2.0
sudo apt-get install libsdl2-ttf-2.0
sudo apt-get install libsdl2-mixer-2.0
```

Install Qt5 on Linux:

```
sudo apt-get install qt5-default
```

# How to install #

1. Download and install [CMake](http://www.cmake.org) (if you don't have root privileges, just install to a local directory, like ~/bin)

2. From the source directory, type:

```
mkdir build
cd build
cmake ..
```

Note: The dafault install path is "/usr/local" to change it type `cmake .. -DINSTALL_PATH=<dir>`


now run and install

```
make && sudo make install
```


3. To clean up, just remove the 'build' directory.
