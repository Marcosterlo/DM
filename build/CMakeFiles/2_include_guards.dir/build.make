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
include CMakeFiles/2_include_guards.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/2_include_guards.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/2_include_guards.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/2_include_guards.dir/flags.make

CMakeFiles/2_include_guards.dir/src/2_include_guards.c.o: CMakeFiles/2_include_guards.dir/flags.make
CMakeFiles/2_include_guards.dir/src/2_include_guards.c.o: ../src/2_include_guards.c
CMakeFiles/2_include_guards.dir/src/2_include_guards.c.o: CMakeFiles/2_include_guards.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/marco/Desktop/DM/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/2_include_guards.dir/src/2_include_guards.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/2_include_guards.dir/src/2_include_guards.c.o -MF CMakeFiles/2_include_guards.dir/src/2_include_guards.c.o.d -o CMakeFiles/2_include_guards.dir/src/2_include_guards.c.o -c /home/marco/Desktop/DM/src/2_include_guards.c

CMakeFiles/2_include_guards.dir/src/2_include_guards.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/2_include_guards.dir/src/2_include_guards.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/marco/Desktop/DM/src/2_include_guards.c > CMakeFiles/2_include_guards.dir/src/2_include_guards.c.i

CMakeFiles/2_include_guards.dir/src/2_include_guards.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/2_include_guards.dir/src/2_include_guards.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/marco/Desktop/DM/src/2_include_guards.c -o CMakeFiles/2_include_guards.dir/src/2_include_guards.c.s

# Object files for target 2_include_guards
2_include_guards_OBJECTS = \
"CMakeFiles/2_include_guards.dir/src/2_include_guards.c.o"

# External object files for target 2_include_guards
2_include_guards_EXTERNAL_OBJECTS =

2_include_guards: CMakeFiles/2_include_guards.dir/src/2_include_guards.c.o
2_include_guards: CMakeFiles/2_include_guards.dir/build.make
2_include_guards: CMakeFiles/2_include_guards.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/marco/Desktop/DM/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable 2_include_guards"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/2_include_guards.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/2_include_guards.dir/build: 2_include_guards
.PHONY : CMakeFiles/2_include_guards.dir/build

CMakeFiles/2_include_guards.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/2_include_guards.dir/cmake_clean.cmake
.PHONY : CMakeFiles/2_include_guards.dir/clean

CMakeFiles/2_include_guards.dir/depend:
	cd /home/marco/Desktop/DM/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/marco/Desktop/DM /home/marco/Desktop/DM /home/marco/Desktop/DM/build /home/marco/Desktop/DM/build /home/marco/Desktop/DM/build/CMakeFiles/2_include_guards.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/2_include_guards.dir/depend

