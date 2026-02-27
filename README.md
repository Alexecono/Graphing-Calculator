# Graphing Calculator

A C++ Graphing Calculator using **OpenGL**, **GLFW**, and **ImGui**.  

All required dependencies (GLFW) are automatically downloaded and built via CMake. ImGui is included locally in the `src/` and `include/` folders.

---

## Features

- Interactive 2D plotting  
- Smooth zoom and pan  
- Function input and dynamic rendering  
- Supports decimals, brackets, ln, sin, cos, and elementary mathematical functions  
- Built using **C++17**, **OpenGL**, **GLFW**, and **ImGui**

---

## Prerequisites

Before building, make sure your system has:

1. **C++17 compiler**  
   - Windows: MinGW-w64 (64-bit) or MSVC  
   - Linux: g++ or clang  
   - macOS: clang  

2. **CMake ≥ 3.20**  
   [Download CMake](https://cmake.org/download/)  

3. **OpenGL**  
   - Windows: Included by default (`opengl32`)  
   - Linux: Install via package manager:  
     ```bash
     sudo apt update
     sudo apt install libgl1-mesa-dev
     ```  
   - macOS: Included by default  

> GLFW is automatically downloaded and compiled via CMake — no manual installation is needed. ImGui is included locally.

---

## Getting Started

Follow these steps to build and run the Graphing Calculator:

### 1. Clone the repository

```bash
git clone https://github.com/Alexecono/Graphing-Calculator.git
cd Graphing-Calculator
```
### 2. Create a build directory
```bash
mkdir build
cd build
```

### 3. Configure the project with CMake
```bash
cmake ..
```

### 4. Build the project
```bash
cmake --build .
```

### 5. Run the executable
```bash
# Linux/macOS
./GraphingCalculator

# Windows
./GraphingCalculator.exe
```
