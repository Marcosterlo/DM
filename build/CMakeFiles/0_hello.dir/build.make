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
CMAKE_SOURCE_DIR = /home/marco/Desktop/DM

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/marco/Desktop/DM/build

# Include any dependencies generated for this target.
include CMakeFiles/0_hello.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/0_hello.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/0_hello.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/0_hello.dir/flags.make

CMakeFiles/0_hello.dir/src/0_hello.c.o: CMakeFiles/0_hello.dir/flags.make
CMakeFiles/0_hello.dir/src/0_hello.c.o: ../src/0_hello.c
CMakeFiles/0_hello.dir/src/0_hello.c.o: CMakeFiles/0_hello.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/marco/Desktop/DM/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/0_hello.dir/src/0_hello.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/0_hello.dir/src/0_hello.c.o -MF CMakeFiles/0_hello.dir/src/0_hello.c.o.d -o CMakeFiles/0_hello.dir/src/0_hello.c.o -c /home/marco/Desktop/DM/src/0_hello.c

CMakeFiles/0_hello.dir/src/0_hello.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/0_hello.dir/src/0_hello.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/marco/Desktop/DM/src/0_hello.c > CMakeFiles/0_hello.dir/src/0_hello.c.i

CMakeFiles/0_hello.dir/src/0_hello.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/0_hello.dir/src/0_hello.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/marco/Desktop/DM/src/0_hello.c -o CMakeFiles/0_hello.dir/src/0_hello.c.s

# Object files for target 0_hello
0_hello_OBJECTS = \
"CMakeFiles/0_hello.dir/src/0_hello.c.o"

# External object files for target 0_hello
0_hello_EXTERNAL_OBJECTS =

0_hello: CMakeFiles/0_hello.dir/src/0_hello.c.o
0_hello: CMakeFiles/0_hello.dir/build.make
0_hello: CMakeFiles/0_hello.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/marco/Desktop/DM/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable 0_hello"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/0_hello.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/0_hello.dir/build: 0_hello
.PHONY : CMakeFiles/0_hello.dir/build

CMakeFiles/0_hello.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/0_hello.dir/cmake_clean.cmake
.PHONY : CMakeFiles/0_hello.dir/clean

CMakeFiles/0_hello.dir/depend:
	cd /home/marco/Desktop/DM/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/marco/Desktop/DM /home/marco/Desktop/DM /home/marco/Desktop/DM/build /home/marco/Desktop/DM/build /home/marco/Desktop/DM/build/CMakeFiles/0_hello.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/0_hello.dir/depend

