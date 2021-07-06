cmake_minimum_required(VERSION 3.5)

project(GmshToVtkAndTecplotCpp11)


add_executable(gmshToX
  main.cpp

  Cell2D.cpp
  Face.cpp
  FvmMesh2D.cpp
  GmshReader.cpp
  NodeIdent.cpp
  NodeIdentMsh.cpp
  Point.cpp

  streamIO.h
  )



