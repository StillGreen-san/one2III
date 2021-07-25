# one2III

a commandline utility that generates possible ways of reading a number.

or more formally:
- given a string of digits and a list of conversion rules
- split the string into all possible combination of substrings
- convert every substring using every possible conversion rule

a bit like the ["Worst Wifi Password Ever"](https://www.youtube.com/watch?v=bLE7zsJk4AI), but for numbers only.

sample:

![sample](sample.gif)

### available rules:

| rule                   | from | to                       |
| ---------------------- | ---- | ------------------------ |
| as number              | 55   | 55                       |
| run length encoding    | 335  | 2:2 1:5                  |
| run length decoding    | 3211 | 2221                     |
| roman numeral          | 123  | CXXIII                   |
| to english             | 321  | three hundred twenty one |
| look and say           | 770  | two sevens one zero      |

### example: 123 with rules "run length encoding" & "roman numeral":

- "123"
  - 1:1 1:2 1:3 , CXXIII
- "12 3"
  - 1:1 1:2 1:3 , XII III
  - 1:1 1:2 III , XII 1:3
- "1 23"
  - 1:1 1:2 1:3 , I XXIII
  - 1:1 XXIII , I 1:2 1:3
- "1 2 3"
  - 1:1 1:2 1:3 , I II III
  - 1:1 1:2 III , 1:1 II 1:3 , I 1:2 1:3
  - 1:1 I I III , I II 1:3 , I 1:2 III

## Code

  - written in/with C++ 17
  - uses cmake (find_package or FetchContent)
  - only tested under Windows 10 (2004) x64

### Dependencies

  - CMake : [cpp_starter_project](https://github.com/lefticus/cpp_starter_project/) (submodule)
  - Testing : [Catch2](https://github.com/catchorg/Catch2)

### Build

```
git clone https://github.com/StillGreen-san/one2III
cd one2III
git submodule update --init --recursive

# depending on the default generator only one of the Release options is needed
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release

build/Release/one2III
# or (depending on default generator)
build/one2III
```

building for x86 may result in errors not present with x64!

avaiable cmake targets:
- one2III : user execuatable
- one2III-test : test executable
- one2II-lib : common code lib

avaiable cmake options:
- ENABLE_CLANG_TIDY
  - may complain about disabled exceptions due to [LLVM Bug 45356](https://bugs.llvm.org/show_bug.cgi?id=45356)
  - replace all instances of ```/EHsc``` with ```-EHsc``` in build/ as a workaround
- ENABLE_CPPCHECK
  - use cppcheck.ps1 if it doesn't work properly
- both should be skipped for test target
