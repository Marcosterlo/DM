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
CMAKE_SOURCE_DIR = "/home/marco/Desktop/Working directory/DM"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/home/marco/Desktop/Working directory/DM/build"

# Include any dependencies generated for this target.
include CMakeFiles/3_file.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/3_file.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/3_file.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/3_file.dir/flags.make

CMakeFiles/3_file.dir/src/3_file.c.o: CMakeFiles/3_file.dir/flags.make
CMakeFiles/3_file.dir/src/3_file.c.o: ../src/3_file.c
CMakeFiles/3_file.dir/src/3_file.c.o: CMakeFiles/3_file.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/marco/Desktop/Working directory/DM/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/3_file.dir/src/3_file.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/3_file.dir/src/3_file.c.o -MF CMakeFiles/3_file.dir/src/3_file.c.o.d -o CMakeFiles/3_file.dir/src/3_file.c.o -c "/home/marco/Desktop/Working directory/DM/src/3_file.c"

CMakeFiles/3_file.dir/src/3_file.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/3_file.dir/src/3_file.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/home/marco/Desktop/Working directory/DM/src/3_file.c" > CMakeFiles/3_file.dir/src/3_file.c.i

CMakeFiles/3_file.dir/src/3_file.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/3_file.dir/src/3_file.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/home/marco/Desktop/Working directory/DM/src/3_file.c" -o CMakeFiles/3_file.dir/src/3_file.c.s

# Object files for target 3_file
3_file_OBJECTS = \
"CMakeFiles/3_file.dir/src/3_file.c.o"

# External object files for target 3_file
3_file_EXTERNAL_OBJECTS =

3_file: CMakeFiles/3_file.dir/src/3_file.c.o
3_file: CMakeFiles/3_file.dir/build.make
3_file: CMakeFiles/3_file.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/home/marco/Desktop/Working directory/DM/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable 3_file"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/3_file.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/3_file.dir/build: 3_file
.PHONY : CMakeFiles/3_file.dir/build

CMakeFiles/3_file.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/3_file.dir/cmake_clean.cmake
.PHONY : CMakeFiles/3_file.dir/clean

CMakeFiles/3_file.dir/depend:
	cd "/home/marco/Desktop/Working directory/DM/build" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/home/marco/Desktop/Working directory/DM" "/home/marco/Desktop/Working directory/DM" "/home/marco/Desktop/Working directory/DM/build" "/home/marco/Desktop/Working directory/DM/build" "/home/marco/Desktop/Working directory/DM/build/CMakeFiles/3_file.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/3_file.dir/depend

