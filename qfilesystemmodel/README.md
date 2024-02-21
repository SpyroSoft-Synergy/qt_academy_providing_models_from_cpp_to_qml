<center><img src="/doc/spyrosoft_color_rgb-1.png" alt="Spyrosoft" width="300" height="auto"></center>

# QFileSystemModel

In this example we want to apply optimizations to the [FileSystem Viewer](../filesystem_viewer/README.md).
Our goal is to re-use QFileSystemModel class as is, instead of implementing our own FileSystem model

## Build the project

```
$ mkdir build
$ cd build
$ cmake -DCMAKE_PREFIX_PATH=<path/to/Qt6> ..
$ cmake --build .
```

## Run

```
$ ./appqfilesystemmodel
```