# ProvaEngine

Old repository here for history's sake.


The updated ProvaEngine is written in D:  
[https://github.com/teamprova/ProvaEngine](https://github.com/teamprova/ProvaEngine)

## Building

* Install Gradle, gcc, and g++
* Create a folder in the "third party" folder named "SDL2"
* Make a folder named "include" in the SDL2 folder with associated header files inside
* Create a "lib" folder in the SDL2 folder and place SDL2.dll inside (if using Windows, otherwise just install SDL2)
* Run `gradle ProvaEngineStaticLibrary`, if it compiles properly you should see BUILD SUCCESSFUL around the end of Gradle's output
