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
CMAKE_SOURCE_DIR = "/home/marco/Desktop/Working directory/DM/my_examples"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/home/marco/Desktop/Working directory/DM/my_examples/build"

# Include any dependencies generated for this target.
include CMakeFiles/2_basics.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/2_basics.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/2_basics.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/2_basics.dir/flags.make

CMakeFiles/2_basics.dir/src/2_basics.c.o: CMakeFiles/2_basics.dir/flags.make
CMakeFiles/2_basics.dir/src/2_basics.c.o: ../src/2_basics.c
CMakeFiles/2_basics.dir/src/2_basics.c.o: CMakeFiles/2_basics.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/marco/Desktop/Working directory/DM/my_examples/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/2_basics.dir/src/2_basics.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/2_basics.dir/src/2_basics.c.o -MF CMakeFiles/2_basics.dir/src/2_basics.c.o.d -o CMakeFiles/2_basics.dir/src/2_basics.c.o -c "/home/marco/Desktop/Working directory/DM/my_examples/src/2_basics.c"

CMakeFiles/2_basics.dir/src/2_basics.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/2_basics.dir/src/2_basics.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/home/marco/Desktop/Working directory/DM/my_examples/src/2_basics.c" > CMakeFiles/2_basics.dir/src/2_basics.c.i

CMakeFiles/2_basics.dir/src/2_basics.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/2_basics.dir/src/2_basics.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/home/marco/Desktop/Working directory/DM/my_examples/src/2_basics.c" -o CMakeFiles/2_basics.dir/src/2_basics.c.s

# Object files for target 2_basics
2_basics_OBJECTS = \
"CMakeFiles/2_basics.dir/src/2_basics.c.o"

# External object files for target 2_basics
2_basics_EXTERNAL_OBJECTS =

2_basics: CMakeFiles/2_basics.dir/src/2_basics.c.o
2_basics: CMakeFiles/2_basics.dir/build.make
2_basics: CMakeFiles/2_basics.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/home/marco/Desktop/Working directory/DM/my_examples/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable 2_basics"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/2_basics.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/2_basics.dir/build: 2_basics
.PHONY : CMakeFiles/2_basics.dir/build

CMakeFiles/2_basics.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/2_basics.dir/cmake_clean.cmake
.PHONY : CMakeFiles/2_basics.dir/clean

CMakeFiles/2_basics.dir/depend:
	cd "/home/marco/Desktop/Working directory/DM/my_examples/build" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/home/marco/Desktop/Working directory/DM/my_examples" "/home/marco/Desktop/Working directory/DM/my_examples" "/home/marco/Desktop/Working directory/DM/my_examples/build" "/home/marco/Desktop/Working directory/DM/my_examples/build" "/home/marco/Desktop/Working directory/DM/my_examples/build/CMakeFiles/2_basics.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/2_basics.dir/depend

