# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /mnt/c/Users/huawei/Desktop/3_сем/labs/lalalabs/Lab5/6

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/c/Users/huawei/Desktop/3_сем/labs/lalalabs/Lab5/6/build

# Include any dependencies generated for this target.
include CMakeFiles/VectorTest.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/VectorTest.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/VectorTest.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/VectorTest.dir/flags.make

CMakeFiles/VectorTest.dir/unit.cpp.o: CMakeFiles/VectorTest.dir/flags.make
CMakeFiles/VectorTest.dir/unit.cpp.o: ../unit.cpp
CMakeFiles/VectorTest.dir/unit.cpp.o: CMakeFiles/VectorTest.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/huawei/Desktop/3_сем/labs/lalalabs/Lab5/6/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/VectorTest.dir/unit.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/VectorTest.dir/unit.cpp.o -MF CMakeFiles/VectorTest.dir/unit.cpp.o.d -o CMakeFiles/VectorTest.dir/unit.cpp.o -c /mnt/c/Users/huawei/Desktop/3_сем/labs/lalalabs/Lab5/6/unit.cpp

CMakeFiles/VectorTest.dir/unit.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/VectorTest.dir/unit.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/Users/huawei/Desktop/3_сем/labs/lalalabs/Lab5/6/unit.cpp > CMakeFiles/VectorTest.dir/unit.cpp.i

CMakeFiles/VectorTest.dir/unit.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/VectorTest.dir/unit.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/Users/huawei/Desktop/3_сем/labs/lalalabs/Lab5/6/unit.cpp -o CMakeFiles/VectorTest.dir/unit.cpp.s

# Object files for target VectorTest
VectorTest_OBJECTS = \
"CMakeFiles/VectorTest.dir/unit.cpp.o"

# External object files for target VectorTest
VectorTest_EXTERNAL_OBJECTS =

VectorTest: CMakeFiles/VectorTest.dir/unit.cpp.o
VectorTest: CMakeFiles/VectorTest.dir/build.make
VectorTest: /usr/lib/x86_64-linux-gnu/libgtest.a
VectorTest: CMakeFiles/VectorTest.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/mnt/c/Users/huawei/Desktop/3_сем/labs/lalalabs/Lab5/6/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable VectorTest"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/VectorTest.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/VectorTest.dir/build: VectorTest
.PHONY : CMakeFiles/VectorTest.dir/build

CMakeFiles/VectorTest.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/VectorTest.dir/cmake_clean.cmake
.PHONY : CMakeFiles/VectorTest.dir/clean

CMakeFiles/VectorTest.dir/depend:
	cd /mnt/c/Users/huawei/Desktop/3_сем/labs/lalalabs/Lab5/6/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/c/Users/huawei/Desktop/3_сем/labs/lalalabs/Lab5/6 /mnt/c/Users/huawei/Desktop/3_сем/labs/lalalabs/Lab5/6 /mnt/c/Users/huawei/Desktop/3_сем/labs/lalalabs/Lab5/6/build /mnt/c/Users/huawei/Desktop/3_сем/labs/lalalabs/Lab5/6/build /mnt/c/Users/huawei/Desktop/3_сем/labs/lalalabs/Lab5/6/build/CMakeFiles/VectorTest.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/VectorTest.dir/depend

