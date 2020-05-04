
## Description
This project is QML app for BFS text web-search.

Project include simple unit-tests. 
Used single header catch2 library (header included to project)
https://github.com/catchorg/Catch2

### Parameters
1. The start URL
2. The maximum number of threads
3. The desired text
4. Maximum number of crawls URLS

## Build from sources

### Prerequisites


* Compiler:
  - `with c++17 support`
* Build tools:
  - `cmake` (version >= 3.15)
  - `clang-format` (if formatting is needed)
  - `Qt` (version >= 5.13.1`)

### Build & Install

```bash
git clone https://github.com/fryziuk/qt-web-search
cd https://github.com/fryziuk/qt-web-search
cmake -Bbuild -H.
cmake --build build
```

### Run TEST
```bash
./url_searcher_test
```


