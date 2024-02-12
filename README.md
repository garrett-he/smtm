# smtm

Lua engine to let you run scripts for memory training in games.

## Build

Make sure you have [CMake][1] and [conan][2] installed. For sure toolchain is
required using Visual Studio for example:

```
conan install . --output-folder=build --build=missing
cd build
cmake .. -G "Visual Studio 17 2022" -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake
cmake --build . --config Release
```

The output file is:

```
./build/Release/smtm.exe
```


## License

Copyright (C) 2023 Garrett HE <garrett.he@outlook.com>

The GNU General Public License (GPL) version 3, see [COPYING](./COPYING).

[1]: https://cmake.org/

[2]: https://conan.io/
