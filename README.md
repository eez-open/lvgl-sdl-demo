`git clone https://github.com/eez-open/lvgl-sdl-demo.git --recursive`

## Build (Linux)
```
apt install libsdl2-dev
mkdir build
cd build
cmake ..
make
./lvgl-sdl-demo
```

## Build (Windows)
Install MYSYS2, then from a mingw64 environment:
```
pacman -S mingw-w64-x86_64-make \
          mingw-w64-x86_64-cmake \
          mingw-w64-x86_64-gcc \
          mingw-w64-x86_64-SDL2
cd example/
mkdir build && cd build
cmake .. -G "MinGW Makefiles"
cmake --build .
./lvgl_example.exe
```
