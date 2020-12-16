# godot-dear-imgui
Native Dear [ImGui](https://github.com/ocornut/imgui) module for [Godot game engine](https://godotengine.org/)

Based on [pkdawson's](https://github.com/pkdawson/imgui-godot) C# plugin imgui-godot

The module ships with Dear ImGui, the module is implemented in such a fashion that you can drop in your preferred version of ImGui. The module does not touch any code inside either Godot or Dear ImGui. 

## Requirements 
Module is based on godot [3.2.3 stable](https://github.com/godotengine/godot/tree/3.2.3-stable).

## Instructions

How [compile](https://docs.godotengine.org/en/stable/development/compiling/index.html) Godot for your plattform. 

The addition you need to make is to place the ```src\imgui``` folder inside ```..\godot\modules\``` and then compile.

## Usage
The intent behind this module is to bring ImGui to GDScript, ImGui's uses C++ namespaces::, this is not supported in GDScript and therefore _ is used instead. GDScript is agnostic to address. Meaning that we turn from address-based manipulation to updating values by copy-by-value. 
This leads to wonky usage of ImGui such as this; ```temp = ImGui_InputFloat("Test value", temp, 0.1, 0.2, "%.3f")```, where temp is an argument, but also captures the return value. 

When Godot has been compiled with the custom module, you will get an additional node called native_imgui. Suggested usage is to add this node as a child to the object you want to debug, and get the values by using GDScript get_parent().

See the demo project for the ImGui demo window. 

You are in charge of keeping the ImGui stack in order, the only thing the modules does for you "automagically" is to hijack the render, by connecting to the VisualServers pre/post_render signals. 

You are currently forced to have at least one ```\_input notification``` function in one of the modules, this is because I haven't been able to catch the notification ```_input``` from the SceneTree yet. 


## Issues
Issues are presented in severity.
* ~~Two native_imgui nodes will result in two windows, one broken.~~
* ~~New children are created in every frame. This is to create correct clipping rects, each child requires their own, and the amount of children is tied to how many draw commands ImGui wants, which in turn is dynamic.~~
* We are creating new surfaces and deleting them every single frame. 
* The binds for the Godot default function _input is used as passthrough, as I could not figure out how to make Godot call my versions implemented in C++. 
* Most of the work is tedious and repetitious copy and paste, meaning that there is a high risk for small errors from me not paying attention.


