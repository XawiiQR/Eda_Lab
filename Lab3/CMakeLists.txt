cmake_minimum_required(VERSION 3.10)

project(TuProyecto)

# Encuentra e incluye VTK
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})

# Agrega tu ejecutable y enlázalo con las bibliotecas de VTK
add_executable(eda Grafica.cpp)
target_link_libraries(eda ${VTK_LIBRARIES})
