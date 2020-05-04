
## Description
This project is a QML app for BFS text web-search.

The project includes a simple unit-tests. 
Used single header library  catch2 (header included to project)
https://github.com/catchorg/Catch2

### Parameters
1. The start URL
2. The maximum number of threads
3. The desired text
4. Maximum number of crawls URLs

## Build from sources

### Prerequisites
* Compiler:
  - `with c++17 support`
* Build tools:
  - `cmake` (version >= 3.15)
  - `clang-format` (if formatting is needed)
  - `Qt` (version >= 5.13.1`)
  
  Make sure that Qt5_DIR environment variable is set

### Build & Install

```bash
git clone https://github.com/fryziuk/qt-web-search
cd qt-web-search
mkdir build
cd build
cmake ..
make -j 12
```

### Run TEST
From build directory
```bash
./test/url_searcher_test
```

### Run App
From build directory
```bash
./qt-web-search
```
### Tested platforms
macOS Catalina
