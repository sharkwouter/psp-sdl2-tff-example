# Jewels SDL texture loading test

This code shows an issue with SDL2 when trying to render a texture. It is not triggered in PPSSPP, but this code will crash when SDL_RenderCopy is called on PSP. Comment it out and the crash won't happen.

## Building

### PSP

```
mkdir psp && cd psp
psp-cmake ..
make
```

### PC

```
mkdir build && cd build
cmake ..
make
```
