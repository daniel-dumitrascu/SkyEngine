# SkyEngine

SkyEngine is a simple 2D game engine written in C++

Features:

* Reading png and tga images
* Reading mesh files describing the object geometry
* Able to parse and render animation files composed of 2D sprites
* Writing shaders in GLSL
* Collision detection
* Visual debugging features that can be activated and deactivated at runtime
* Simple logging mechanism
* Linux and Windows support
	
## How to compile

These are instructions on how to compile the code on various supported operating systems

### Windows

Supported version is Windows 10

* Install CMAKE and make sure you add it to the global environment variables
* We are going to use Visual Studio 2017 (platform toolset v141) to compile the code
* Add the conan package manager extension to Visual Studio. Once this is done, modify the conan install directory by going to Tool/Conan Package Manager/Options and add the path:
```
$(ProjectDir)binaries\$(Platform)\$(Configuration)\.conan
```
* Right click on the solution and install the dependencies using conan
* To run the application you will also need to copy the whole "resources" folder into either "Debug" or "Release"
	
### Linux

* Install gcc
* Install visual code
* Add the Microsoft C/C++ extension for Visual Code (if preferred  you can also add Material Icon Theme but this is not mandatory)
* We need to add some extra tools to the env by running this command: 
```
sudo apt-get install libglfw3-dev libgl1-mesa-dev libglu1-mesa-dev
```
* To build execute make
* Before running the game we need to make the shared library visible to the system
```
LD_LIBRARY_PATH=<path to engine so>
export LD_LIBRARY_PATH
```	