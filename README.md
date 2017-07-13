# ProvaEngine

## Building

* In the third party folder, create an include folder and a lib folder
* Create folders GL, GLEW, SDL2, and SOIL in the include directory
* Place the header files belonging to each library in those folders
* Place the lib/a file for GLEW in the lib folder.
* Place SDL2.dll in the lib folder (if using Windows, otherwise just install SDL2)
* Now you can run `gradle cowboy` to build the test program, look in build/exe/cowboy when the build finishes