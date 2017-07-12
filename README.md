# ProvaEngine

## Building

* In the third party folder, create an include folder and a lib folder
* Create folders GL, GLEW, SDL2, and SOIL in the include directory
* Place the header files belonging to each library in those folders
* Place lib/a files for GLEW and SOIL in the lib folder.
    * Make sure the libraries are named as lib[Library Name].*
* Place SDL2.dll in the lib folder (if using windows, otherwise just install SDL2)
* Now you can run `gradle cowboy` to build the test program, look in build/exe/cowboy when the build finishes