# gmsh-to-vtk-CPP11
C++ 11 version of my Fortran code gmsh-to-vtk-and-tecplot

Some features:

- Convert .msh mesh file (Quadrilateral) of gmsh to .vtk file.
- Written in modern C++ (C++11 standard, intensive use of C++ STL).

**Remarks:**

- You will need a mature C++11 compiler to compile and run my code, as described in **History**

**History:**

06/2021

- After a major refactoring, the code has been tested with MinGW g++ 9.20 (under NetBeans 8.2 IDE) and MinGW g++ 8.1 (under Code::Blocks 20.3 IDE).

2018

- I have compiled and run my code successfully with g++ 5.1.0, Visual Studio 2015 Community Edition, Intel C++ 2018 for Linux.

- The default C++ compiler of Ubuntu 14.04 LTS (g++ 4.8.4) failed to compile my code. This bug is fixed [here](https://github.com/truongd8593/Euler2dCpp11/commit/6350ba1ad3b54f72bd5d7fc752e6977979ff914f)

[Description](https://github.com/truongd8593/gmsh-to-vtk-CPP11/wiki)
