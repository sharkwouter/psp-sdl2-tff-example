# Jewels SDL texture loading test

This code shows a simple SDL2 example which runs on PSP, VITA and Linux. It uses texture rendering to draw a BMP image. This makes it easier to test if there are any issues with SDL2 for PSP.

![screenshot](screenshot.png?raw=true)

## Building

### PSP

```
mkdir psp && cd psp
psp-cmake ..
make
```

### VITA

```
mkdir vita && cd vita
cmake -DCMAKE_TOOLCHAIN_FILE="${VITASDK}/share/vita.toolchain.cmake" ..
make
```

### PC

```
mkdir build && cd build
cmake ..
make
```
