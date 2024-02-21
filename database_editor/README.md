# Product Database Editor

In this example, we'll create a simple database editor. We should be able to view and modify the connected database.

For the purpose of this example, we'll use an SQLite3 `example-db` database.

## Build the project

```
$ mkdir build
$ cd build
$ cmake -DCMAKE_PREFIX_PATH=<path/to/Qt6> ..
$ cmake --build .
```

## Run

```
$ ./appsqlmodel
```