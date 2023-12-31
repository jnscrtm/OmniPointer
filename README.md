# OmniPointer

A (kind of) omnipotent pointer. Well, not really. As the brief description said, this is a bizarre thing coming out of a bizarre idea that suddenly passed by the author's head when he was bored and had nothing to do. ***Safety from any aspects is never guaranteed***; everything is at one's own risk.

The required minimum C++ standard is C++11, because there are a few things that do not effectively have their equivalent in earlier standards (namely, move semantics and type traits).

The CMake build script (`CMakeLists.txt`) may be used to build a static library which will then be linked to another project to compile. Otherwise, one also may use `OmniPointer.cpp` as another source code to compile together with the others. Of course, either way, the header file is still needed to access the functionality.

Consult `refman.pdf` for the general documentation of `OmniPointer`. You can also just read through the code files.

## Brief Mechanism
An `OmniPointer` internally holds:
1. a `void*` to hold the address of the object it currently owns and
2. a `void(*)(void*)` that points to the appropriate destroyer function (unique for each assigned type).
### Creation, Assignment, and Destruction
- `OmniPointer` only allows move semantics. The copy constructor and the copy assignment are marked deleted and are thus unusable.
- As far as uniqueness is concerned, `OmniPointer` is generally unique unless two or more are constructed from the same local raw pointer (not recommended).
- When the lifetime of an `OmniPointer` ends, the destructor is called, releasing the allocated memory through the specified destroyer function.

### Other
Other finer details shall be described in the documentation.
