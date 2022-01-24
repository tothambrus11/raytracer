cmake_minimum_required(VERSION 3.20)
project(renderer1)

set(CMAKE_CXX_STANDARD 20)

MATH(EXPR stack_size "100 * 1024 * 1024")

include_directories(includes src)
link_libraries(SDL2 SDL2main)

add_executable(renderer1
        src/main.cpp
        src/Vector3.cpp
        src/HittableObject.cpp
        src/Ray.cpp
        src/objects/Sphere.cpp
        src/objects/Sphere.h
        includes/color.h
        src/objects/Octahedron.cpp
        src/objects/Octahedron.h
        src/Material.cpp
        includes/Material.h
        src/PointLight.cpp
        includes/PointLight.h
        src/objects/Cylinder.cpp
        src/objects/Cylinder.h
        src/objects/CylinderInsideOut.cpp
        src/objects/CylinderInsideOut.h)

target_link_libraries(renderer1 "-Wl,--stack,400000000")
