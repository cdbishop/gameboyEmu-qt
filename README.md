## Building

This project uses [Conan](https://conan.io)  

Only tested on Windows 10 with MSVC.

```
mkdir build
cd build
conan install --build=missing -s build_type=Debug -s compiler.version=15 -s arch=x86_64 -pr ..\profile.py ..
cmake -G "Visual Studio 15 2017 Win64" ..
```