# Trion Engine

Trion Engine is a small, experimental C++ / OpenGL engine built to understand and implement core rendering and engine architecture concepts from scratch.

![Trion Engine](https://raw.githubusercontent.com/cimenbaran/trion-engine/refs/heads/main/Trion-engine.png))

---

## Goals

- Build a clean and understandable rendering engine in modern C++
- Learn and apply modern OpenGL (VAO, VBO, shaders, explicit layouts)
- Establish solid engine architecture foundations (Scene, Camera, Renderer)
- Serve as a long-term base for graphics and engine experimentation

---

## Download and Build Instructions

1. Clone the repository
```
git clone https://github.com/cimenbaran/trion-engine.git  
cd trion-engine
```
2. Configure the build
```
cmake --preset vs2022
```
3a. Build (Debug)

```
cmake --build --preset vs2022-debug
```
3b. Build (Release)
```
cmake --build --preset vs2022-release
```

4. Run
```
./build/trion_engine.exe
```
---

Currently, I've only Visual Studio / MSVC build options available as I'm focused on adding more to the engine.

## Current Features

- C++20 codebase
- OpenGL context creation using GLFW
- OpenGL function loading via GLAD
- Scene and SceneManager system
- GameObject and Component system
- Shader abstraction (compile, link, bind)
- Mesh abstraction (VAO + VBO with interleaved vertex data)
- Built-in cube mesh
- Basic camera system (view and projection matrices)
- Renderer entry point
- Time and delta-time handling

---

## Notes

This project is under active development and is expected to change frequently.
The engine is intended as a learning and experimentation platform.

---

## License

MIT License

## Author
Baran Çimen
