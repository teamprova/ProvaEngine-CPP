# ProvaEngine

## Building

* Install Gradle, gcc, and g++
* Create a "third party" folder, with an include subfolder and lib subfolder
* Create folders GL, GLEW, SDL2 in the include directory
* Place the header files for the matching library in each folder
* Place the lib/a file for GLEW in the lib folder.
* Place SDL2.dll in the lib folder (if using Windows, otherwise just install SDL2)
* Run `gradle ProvaEngineStaticLibrary`, if it compiles properly you should see BUILD SUCCESSFUL around the end of Gradle's output