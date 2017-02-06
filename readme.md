# Gincu -- a simple match three game, game engine, and game framework written in C++

## Version

1.0.1

## Introduction and goals

This is a simple tiny 2D game, game engine, and game framework written in C++. This is not and will not be feature complete because the goals are:
 * Proof of concept. Though I developed several commercial games and engines in the past decade, I didn't have the chance to try some cool concepts such as Entity Component System. The project is where to show the concepts.
 * Learning. I hope this project is a good start point for someone who wants to develop a game from scratch.

The original work was a test work when I was applying a job with a game company. The company requires a simple match-three game written in C++ with SDL. I didn't join the company because I got another offer at the mean time.

Now I open source the project, and I've rewritten the render engine with SFML.

The match-three is the first step. In the future we may add more games as prototypes to the project. Though the match three game is not as cool as Candy Crush Saga, it includes most basic stuff and may be a good kick off.

## Supported platform

 * Windows. Tested.
 * Android. Tested.
 * iOS/iPhone/iPad. Not tested.
 * Mac. Not tested.
 * Linux. Not tested.
 
## Environments and requirements

 * C++11 compiler (Visual C++ 2015 or later, or GCC (MingW) 4.8 or later)
 * [SFML 2.4.1](http://www.sfml-dev.org/) or later
 * My [cpgf library](https://github.com/cpgf/cpgf)
 * CMake 3.6 or later

## License

Apache License, Version 2.0

## Core system and features

 * Entity Component System (ECS).
 * Finite state machine.
 * Scene management.
 * ECS based scene graph (ComponentLocalTransform).
 * Tween animation using the tween module in my cpgf library.
 * Memory pool and cached entities and components. So CPU cache optimization is considered.
 * Underlying rendering engine agnostic. We can replace SFML with any other engine or even 3D engine simply and easily.
 * Sprite sheet.
 * Low level automatically batching draw calls.

## How to contribute

There are several ways to contribute to the project

 * Add new game beside the match-three. Such as adding a Super Mario Bros like game will demonstrate the basic 2D physics engine works perfectly, or adding a Box2D based game.
 * Add or enhance the features. There are several features missed:
   * Frame based animation system. Solution: very easy to add to ECS system as a kind of component.
   * Physics system. Not used in matchtThree type games but is very useful. Solution: easy to add to ECS system as a kind of component.
 * Improve the features such as GameTransform (I'm not good at algebra).
 * Make some better art work. Current art resource is (mostly) made by me and is very ugly.

## Build and run on desktop

 * Download [latest SFML binary](http://www.sfml-dev.org/) that matches your compiler.
 * Download [cpgf library source code](https://github.com/cpgf/cpgf). You don't need to compile the library.
 * Go to the "build/desktop" folder in this project.
 * Edit config.txt to set the proper directories to point to SFML and cpgf.
 * Run "make vc15" to generate VC2015 project file, or "make mingw" to compile using MingW directly, or just "make" to see the help. You can replace "make" with "mingw32-make" or "nmake".
 * If you run "make vc15", open gincu.sln in folder build/project_vc15 in VC IDE and compile the project.
 * The binary file is generated in folder bin.
 * Go to folder "bin", copy SFML graphics, system, and window DLL (or dynamic libraries on Linux) to bin folder, then run the compiled program.

## Build and run on Android

 * Setup Android SDK and NDK, and Apache ANT.
 * Download [latest SFML source code](http://www.sfml-dev.org/) then build SFML for Android (search for tutorial).
 * Download [cpgf library source code](https://github.com/cpgf/cpgf). You don't need to compile the library.
 * Go to folder "build/android".
 * Create sub folder "assets", copy the "resources" folder in "bin" there.
 * Run "android update project --target "android-23" --path . --subprojects --name gincu".
 * Run "ndk-build".
 * Then run "ant debug" for debug version or "ant release" for release version.
 * Now .apk is in "build/android/bin" folder.

## Folder structure

 * bin. The resources, libraries, and the game program. CMake was already configured to output compiled program there.
 * build. CMake build home.
 * include. The include folder of the library.
 * src. The source code of the library..
 * tests/application. All application code. Each sub folder is a single game or application.
 * tests/application/matchthree. The match-three game. If you need to add another game XYZ, create folder src/application/xyz.
 
 