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
include CMakeFiles/program.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/program.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/program.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/program.dir/flags.make

CMakeFiles/program.dir/src/axis.c.o: CMakeFiles/program.dir/flags.make
CMakeFiles/program.dir/src/axis.c.o: ../src/axis.c
CMakeFiles/program.dir/src/axis.c.o: CMakeFiles/program.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/marco/Desktop/Working directory/DM/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/program.dir/src/axis.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/program.dir/src/axis.c.o -MF CMakeFiles/program.dir/src/axis.c.o.d -o CMakeFiles/program.dir/src/axis.c.o -c "/home/marco/Desktop/Working directory/DM/src/axis.c"

CMakeFiles/program.dir/src/axis.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/program.dir/src/axis.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/home/marco/Desktop/Working directory/DM/src/axis.c" > CMakeFiles/program.dir/src/axis.c.i

CMakeFiles/program.dir/src/axis.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/program.dir/src/axis.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/home/marco/Desktop/Working directory/DM/src/axis.c" -o CMakeFiles/program.dir/src/axis.c.s

CMakeFiles/program.dir/src/block.c.o: CMakeFiles/program.dir/flags.make
CMakeFiles/program.dir/src/block.c.o: ../src/block.c
CMakeFiles/program.dir/src/block.c.o: CMakeFiles/program.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/marco/Desktop/Working directory/DM/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/program.dir/src/block.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/program.dir/src/block.c.o -MF CMakeFiles/program.dir/src/block.c.o.d -o CMakeFiles/program.dir/src/block.c.o -c "/home/marco/Desktop/Working directory/DM/src/block.c"

CMakeFiles/program.dir/src/block.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/program.dir/src/block.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/home/marco/Desktop/Working directory/DM/src/block.c" > CMakeFiles/program.dir/src/block.c.i

CMakeFiles/program.dir/src/block.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/program.dir/src/block.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/home/marco/Desktop/Working directory/DM/src/block.c" -o CMakeFiles/program.dir/src/block.c.s

CMakeFiles/program.dir/src/fsm.c.o: CMakeFiles/program.dir/flags.make
CMakeFiles/program.dir/src/fsm.c.o: ../src/fsm.c
CMakeFiles/program.dir/src/fsm.c.o: CMakeFiles/program.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/marco/Desktop/Working directory/DM/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/program.dir/src/fsm.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/program.dir/src/fsm.c.o -MF CMakeFiles/program.dir/src/fsm.c.o.d -o CMakeFiles/program.dir/src/fsm.c.o -c "/home/marco/Desktop/Working directory/DM/src/fsm.c"

CMakeFiles/program.dir/src/fsm.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/program.dir/src/fsm.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/home/marco/Desktop/Working directory/DM/src/fsm.c" > CMakeFiles/program.dir/src/fsm.c.i

CMakeFiles/program.dir/src/fsm.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/program.dir/src/fsm.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/home/marco/Desktop/Working directory/DM/src/fsm.c" -o CMakeFiles/program.dir/src/fsm.c.s

CMakeFiles/program.dir/src/machine.c.o: CMakeFiles/program.dir/flags.make
CMakeFiles/program.dir/src/machine.c.o: ../src/machine.c
CMakeFiles/program.dir/src/machine.c.o: CMakeFiles/program.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/marco/Desktop/Working directory/DM/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/program.dir/src/machine.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/program.dir/src/machine.c.o -MF CMakeFiles/program.dir/src/machine.c.o.d -o CMakeFiles/program.dir/src/machine.c.o -c "/home/marco/Desktop/Working directory/DM/src/machine.c"

CMakeFiles/program.dir/src/machine.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/program.dir/src/machine.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/home/marco/Desktop/Working directory/DM/src/machine.c" > CMakeFiles/program.dir/src/machine.c.i

CMakeFiles/program.dir/src/machine.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/program.dir/src/machine.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/home/marco/Desktop/Working directory/DM/src/machine.c" -o CMakeFiles/program.dir/src/machine.c.s

CMakeFiles/program.dir/src/point.c.o: CMakeFiles/program.dir/flags.make
CMakeFiles/program.dir/src/point.c.o: ../src/point.c
CMakeFiles/program.dir/src/point.c.o: CMakeFiles/program.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/marco/Desktop/Working directory/DM/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_5) "Building C object CMakeFiles/program.dir/src/point.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/program.dir/src/point.c.o -MF CMakeFiles/program.dir/src/point.c.o.d -o CMakeFiles/program.dir/src/point.c.o -c "/home/marco/Desktop/Working directory/DM/src/point.c"

CMakeFiles/program.dir/src/point.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/program.dir/src/point.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/home/marco/Desktop/Working directory/DM/src/point.c" > CMakeFiles/program.dir/src/point.c.i

CMakeFiles/program.dir/src/point.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/program.dir/src/point.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/home/marco/Desktop/Working directory/DM/src/point.c" -o CMakeFiles/program.dir/src/point.c.s

CMakeFiles/program.dir/src/program.c.o: CMakeFiles/program.dir/flags.make
CMakeFiles/program.dir/src/program.c.o: ../src/program.c
CMakeFiles/program.dir/src/program.c.o: CMakeFiles/program.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/marco/Desktop/Working directory/DM/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_6) "Building C object CMakeFiles/program.dir/src/program.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/program.dir/src/program.c.o -MF CMakeFiles/program.dir/src/program.c.o.d -o CMakeFiles/program.dir/src/program.c.o -c "/home/marco/Desktop/Working directory/DM/src/program.c"

CMakeFiles/program.dir/src/program.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/program.dir/src/program.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/home/marco/Desktop/Working directory/DM/src/program.c" > CMakeFiles/program.dir/src/program.c.i

CMakeFiles/program.dir/src/program.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/program.dir/src/program.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/home/marco/Desktop/Working directory/DM/src/program.c" -o CMakeFiles/program.dir/src/program.c.s

CMakeFiles/program.dir/src/toml.c.o: CMakeFiles/program.dir/flags.make
CMakeFiles/program.dir/src/toml.c.o: ../src/toml.c
CMakeFiles/program.dir/src/toml.c.o: CMakeFiles/program.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/marco/Desktop/Working directory/DM/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_7) "Building C object CMakeFiles/program.dir/src/toml.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/program.dir/src/toml.c.o -MF CMakeFiles/program.dir/src/toml.c.o.d -o CMakeFiles/program.dir/src/toml.c.o -c "/home/marco/Desktop/Working directory/DM/src/toml.c"

CMakeFiles/program.dir/src/toml.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/program.dir/src/toml.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/home/marco/Desktop/Working directory/DM/src/toml.c" > CMakeFiles/program.dir/src/toml.c.i

CMakeFiles/program.dir/src/toml.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/program.dir/src/toml.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/home/marco/Desktop/Working directory/DM/src/toml.c" -o CMakeFiles/program.dir/src/toml.c.s

# Object files for target program
program_OBJECTS = \
"CMakeFiles/program.dir/src/axis.c.o" \
"CMakeFiles/program.dir/src/block.c.o" \
"CMakeFiles/program.dir/src/fsm.c.o" \
"CMakeFiles/program.dir/src/machine.c.o" \
"CMakeFiles/program.dir/src/point.c.o" \
"CMakeFiles/program.dir/src/program.c.o" \
"CMakeFiles/program.dir/src/toml.c.o"

# External object files for target program
program_EXTERNAL_OBJECTS =

program: CMakeFiles/program.dir/src/axis.c.o
program: CMakeFiles/program.dir/src/block.c.o
program: CMakeFiles/program.dir/src/fsm.c.o
program: CMakeFiles/program.dir/src/machine.c.o
program: CMakeFiles/program.dir/src/point.c.o
program: CMakeFiles/program.dir/src/program.c.o
program: CMakeFiles/program.dir/src/toml.c.o
program: CMakeFiles/program.dir/build.make
program: CMakeFiles/program.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/home/marco/Desktop/Working directory/DM/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_8) "Linking C executable program"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/program.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/program.dir/build: program
.PHONY : CMakeFiles/program.dir/build

CMakeFiles/program.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/program.dir/cmake_clean.cmake
.PHONY : CMakeFiles/program.dir/clean

CMakeFiles/program.dir/depend:
	cd "/home/marco/Desktop/Working directory/DM/build" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/home/marco/Desktop/Working directory/DM" "/home/marco/Desktop/Working directory/DM" "/home/marco/Desktop/Working directory/DM/build" "/home/marco/Desktop/Working directory/DM/build" "/home/marco/Desktop/Working directory/DM/build/CMakeFiles/program.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/program.dir/depend

