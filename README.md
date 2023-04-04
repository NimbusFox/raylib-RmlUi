# Raylib + RmlUi Example(s)

This is a quick example of how to integrate RmlUi into raylib

Right now it only shows how to add:
* Fonts
* Html (rml files)
* Stylesheets
* Images

To see how it clicks together you can look at the raylib\*interface files in src:
* raylibFileInterface.cpp
* raylibRenderInterface.cpp
* raylibSystemInterface.cpp
* raylibRmlUI.cpp

At this time this is only a very simple implementation. It is recommended to give the [documentation](https://mikke89.github.io/RmlUiDoc/pages/cpp_manual.html) a read

There are things like clipboard interaction and a virtual keyboard

RmlUi is able to work inside of Emscripten since 5.0

# Compile
## Prequisites

After cloning run inside of the cloned folder:
```bash
git submodule update --init --recursive
```

## Build
```
cmake -S . -B ./build -DCMAKE_BUILD_TYPE=Debug
cmake --build ./build -- -j $(nproc)
```

# Run
Inside the project folder there should now be a bin folder if the compile was successful. Inside that should be a Debug folder. Then run RmlUI_Example(.exe) to see the simple demo
