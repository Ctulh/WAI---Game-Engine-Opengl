
# Change Log
All notable changes to this project will be documented in this file.
##  09-05-2021
### Added
- [Shape.h](https://github.com/Ctulh/WAI---Opengl-CubeViewer/blob/master/OpenglTo4noNormalno2/Shape.h)
  Declaration class Shape and inherited class - Sphere which help generate and draw  "sphere of the first order" .
- [Shape.cpp](https://github.com/Ctulh/WAI---Opengl-CubeViewer/blob/master/OpenglTo4noNormalno2/Shape.cpp)
   Implementation some classes and functions .
- [Structures.h](https://github.com/Ctulh/WAI---Opengl-CubeViewer/blob/master/OpenglTo4noNormalno2/Structures.h)
 Added enum of the shapes for the future procedural shape generation.
### How is drawing "Sphere of the first order" works
![](OctahedronToSphere)
![Uzoma Medium Gif](https://media.giphy.com/media/xEVDqEJZ1U64IwhNzW/giphy.gif)
First of all Octahedron verticies are loaded from [ball.wai](https://github.com/Ctulh/WAI---Opengl-CubeViewer/blob/master/OpenglTo4noNormalno2/res/objects/coords_shape/ball.wai), then every side(triangle) procedurial divided into 4 smaller traingles after these actions to all sides called function.
```c++
GLfloat* Normalize(GLfloat* _inArray, int count, double radius);
```
Where:
- `_inArray` - Array of Octahedron verticies.
- `count` - Count of Octahedron elements.
 - `radius` - Sphere radius.
 
`Normalize` funcion returnes **normalized** array of Octahedron verticies, that means that all vertices are at the same distance from the center of the sphere.
### Fixed
- Bug with "clear" texture using for the drawing first element at start the program.
