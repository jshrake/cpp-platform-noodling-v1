# grimoire
[![Build Status](https://travis-ci.org/jshrake/grimoire.svg?branch=master)](https://travis-ci.org/jshrake/grimoire)
Magical libraries for C++ graphics development.

- [**grim_math.h**](grim_math.h): GLSL-like vector math library
- [**grim_gl.h**](grim_gl.h): Minimal multi-platform OpenGL function loading

## Usage

### OSX/Linux

Install the dependencies:

```bash
# Linux
$ apt-get install cmake libsdl2-dev
# MacOS
$ brew install cmake sdl2
```

Create and run a new project:

```bash
# Install the command-line tool
$ git clone https://github.com/jshrake/grimoire
$ pushd grimoire
$ grimoire install
$ popd
# Create a new project
$ grim new foo
$ cd foo
# Build
$ grim build
# Run
$ grim run
```

### Windows

Coming soon!

## WARNING

Don't cast these spells in public! This is experimental software.
