# FileSystem Viewer

The goal is to implement a simple viewer of the local filesystem. We only want to display the folders/files structure, modifications are not planned.

## Build the project

```
$ mkdir build
$ cd build
$ cmake -DCMAKE_PREFIX_PATH=<path/to/Qt6> ..
$ cmake --build .
```

## Run

```
$ ./apptreefs
```