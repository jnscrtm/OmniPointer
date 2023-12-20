# OmniPointer

A (kind of) omnipotent pointer. Well, not really. As the brief description said, this is a bizarre thing coming out of a bizarre idea that suddenly passed by the author's head when he was bored and had nothing to do. ***Safety from any aspects is never guaranteed***; everything is at one's own risk.

The required minimum C++ standard is C++11, because there are a few things that do not effectively have their equivalent in earlier standards (namely, move semantics and type traits).

The CMake build script (`CMakeLists.txt`) may be used to build a static library which will then be linked to another project to compile. Otherwise, one also may use `OmniPointer.cpp` as another source code to compile together with the others. Of course, either way, the header file is still needed to access the functionality.

Consult `refman.pdf` for the general documentation of `OmniPointer`. You can also just read through the code files.
