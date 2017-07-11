# ProvaEngine

## Building

* In the third party folder, create an include folder and a lib folder
* Create folders GL, GLU, GLEW, SDL, and SOIL in the include directory
* Place the header files belonging to each library in those folders
* Place dll/so files in the lib folder.
    * Make sure the libraries are named as lib[Library Name].*
* Put libSOIL.a in the lib folder as well
* Now you can run `gradle cowboy` to build the test program, look in build/exe/cowboy when the build finishes