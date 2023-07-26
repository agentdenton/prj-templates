## Meson C project

### Setup

#### Debug build:
```
meson setup build --buildtype debug --cross-file cross-file.txt
ninja -C build
```

#### Release build:
```
meson setup build --buildtype release --cross-file cross-file.txt
ninja -C build
```
