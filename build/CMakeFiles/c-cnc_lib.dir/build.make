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
include CMakeFiles/c-cnc_lib.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/c-cnc_lib.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/c-cnc_lib.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/c-cnc_lib.dir/flags.make

CMakeFiles/c-cnc_lib.dir/src/block.c.o: CMakeFiles/c-cnc_lib.dir/flags.make
CMakeFiles/c-cnc_lib.dir/src/block.c.o: ../src/block.c
CMakeFiles/c-cnc_lib.dir/src/block.c.o: CMakeFiles/c-cnc_lib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/marco/Desktop/Working directory/DM/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/c-cnc_lib.dir/src/block.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/c-cnc_lib.dir/src/block.c.o -MF CMakeFiles/c-cnc_lib.dir/src/block.c.o.d -o CMakeFiles/c-cnc_lib.dir/src/block.c.o -c "/home/marco/Desktop/Working directory/DM/src/block.c"

CMakeFiles/c-cnc_lib.dir/src/block.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/c-cnc_lib.dir/src/block.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/home/marco/Desktop/Working directory/DM/src/block.c" > CMakeFiles/c-cnc_lib.dir/src/block.c.i

CMakeFiles/c-cnc_lib.dir/src/block.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/c-cnc_lib.dir/src/block.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/home/marco/Desktop/Working directory/DM/src/block.c" -o CMakeFiles/c-cnc_lib.dir/src/block.c.s

CMakeFiles/c-cnc_lib.dir/src/fsm.c.o: CMakeFiles/c-cnc_lib.dir/flags.make
CMakeFiles/c-cnc_lib.dir/src/fsm.c.o: ../src/fsm.c
CMakeFiles/c-cnc_lib.dir/src/fsm.c.o: CMakeFiles/c-cnc_lib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/marco/Desktop/Working directory/DM/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/c-cnc_lib.dir/src/fsm.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/c-cnc_lib.dir/src/fsm.c.o -MF CMakeFiles/c-cnc_lib.dir/src/fsm.c.o.d -o CMakeFiles/c-cnc_lib.dir/src/fsm.c.o -c "/home/marco/Desktop/Working directory/DM/src/fsm.c"

CMakeFiles/c-cnc_lib.dir/src/fsm.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/c-cnc_lib.dir/src/fsm.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/home/marco/Desktop/Working directory/DM/src/fsm.c" > CMakeFiles/c-cnc_lib.dir/src/fsm.c.i

CMakeFiles/c-cnc_lib.dir/src/fsm.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/c-cnc_lib.dir/src/fsm.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/home/marco/Desktop/Working directory/DM/src/fsm.c" -o CMakeFiles/c-cnc_lib.dir/src/fsm.c.s

CMakeFiles/c-cnc_lib.dir/src/machine.c.o: CMakeFiles/c-cnc_lib.dir/flags.make
CMakeFiles/c-cnc_lib.dir/src/machine.c.o: ../src/machine.c
CMakeFiles/c-cnc_lib.dir/src/machine.c.o: CMakeFiles/c-cnc_lib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/marco/Desktop/Working directory/DM/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/c-cnc_lib.dir/src/machine.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/c-cnc_lib.dir/src/machine.c.o -MF CMakeFiles/c-cnc_lib.dir/src/machine.c.o.d -o CMakeFiles/c-cnc_lib.dir/src/machine.c.o -c "/home/marco/Desktop/Working directory/DM/src/machine.c"

CMakeFiles/c-cnc_lib.dir/src/machine.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/c-cnc_lib.dir/src/machine.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/home/marco/Desktop/Working directory/DM/src/machine.c" > CMakeFiles/c-cnc_lib.dir/src/machine.c.i

CMakeFiles/c-cnc_lib.dir/src/machine.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/c-cnc_lib.dir/src/machine.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/home/marco/Desktop/Working directory/DM/src/machine.c" -o CMakeFiles/c-cnc_lib.dir/src/machine.c.s

CMakeFiles/c-cnc_lib.dir/src/point.c.o: CMakeFiles/c-cnc_lib.dir/flags.make
CMakeFiles/c-cnc_lib.dir/src/point.c.o: ../src/point.c
CMakeFiles/c-cnc_lib.dir/src/point.c.o: CMakeFiles/c-cnc_lib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/marco/Desktop/Working directory/DM/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/c-cnc_lib.dir/src/point.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/c-cnc_lib.dir/src/point.c.o -MF CMakeFiles/c-cnc_lib.dir/src/point.c.o.d -o CMakeFiles/c-cnc_lib.dir/src/point.c.o -c "/home/marco/Desktop/Working directory/DM/src/point.c"

CMakeFiles/c-cnc_lib.dir/src/point.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/c-cnc_lib.dir/src/point.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/home/marco/Desktop/Working directory/DM/src/point.c" > CMakeFiles/c-cnc_lib.dir/src/point.c.i

CMakeFiles/c-cnc_lib.dir/src/point.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/c-cnc_lib.dir/src/point.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/home/marco/Desktop/Working directory/DM/src/point.c" -o CMakeFiles/c-cnc_lib.dir/src/point.c.s

CMakeFiles/c-cnc_lib.dir/src/program.c.o: CMakeFiles/c-cnc_lib.dir/flags.make
CMakeFiles/c-cnc_lib.dir/src/program.c.o: ../src/program.c
CMakeFiles/c-cnc_lib.dir/src/program.c.o: CMakeFiles/c-cnc_lib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/marco/Desktop/Working directory/DM/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_5) "Building C object CMakeFiles/c-cnc_lib.dir/src/program.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/c-cnc_lib.dir/src/program.c.o -MF CMakeFiles/c-cnc_lib.dir/src/program.c.o.d -o CMakeFiles/c-cnc_lib.dir/src/program.c.o -c "/home/marco/Desktop/Working directory/DM/src/program.c"

CMakeFiles/c-cnc_lib.dir/src/program.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/c-cnc_lib.dir/src/program.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/home/marco/Desktop/Working directory/DM/src/program.c" > CMakeFiles/c-cnc_lib.dir/src/program.c.i

CMakeFiles/c-cnc_lib.dir/src/program.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/c-cnc_lib.dir/src/program.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/home/marco/Desktop/Working directory/DM/src/program.c" -o CMakeFiles/c-cnc_lib.dir/src/program.c.s

CMakeFiles/c-cnc_lib.dir/src/toml.c.o: CMakeFiles/c-cnc_lib.dir/flags.make
CMakeFiles/c-cnc_lib.dir/src/toml.c.o: ../src/toml.c
CMakeFiles/c-cnc_lib.dir/src/toml.c.o: CMakeFiles/c-cnc_lib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/marco/Desktop/Working directory/DM/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_6) "Building C object CMakeFiles/c-cnc_lib.dir/src/toml.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/c-cnc_lib.dir/src/toml.c.o -MF CMakeFiles/c-cnc_lib.dir/src/toml.c.o.d -o CMakeFiles/c-cnc_lib.dir/src/toml.c.o -c "/home/marco/Desktop/Working directory/DM/src/toml.c"

CMakeFiles/c-cnc_lib.dir/src/toml.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/c-cnc_lib.dir/src/toml.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/home/marco/Desktop/Working directory/DM/src/toml.c" > CMakeFiles/c-cnc_lib.dir/src/toml.c.i

CMakeFiles/c-cnc_lib.dir/src/toml.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/c-cnc_lib.dir/src/toml.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/home/marco/Desktop/Working directory/DM/src/toml.c" -o CMakeFiles/c-cnc_lib.dir/src/toml.c.s

# Object files for target c-cnc_lib
c__cnc_lib_OBJECTS = \
"CMakeFiles/c-cnc_lib.dir/src/block.c.o" \
"CMakeFiles/c-cnc_lib.dir/src/fsm.c.o" \
"CMakeFiles/c-cnc_lib.dir/src/machine.c.o" \
"CMakeFiles/c-cnc_lib.dir/src/point.c.o" \
"CMakeFiles/c-cnc_lib.dir/src/program.c.o" \
"CMakeFiles/c-cnc_lib.dir/src/toml.c.o"

# External object files for target c-cnc_lib
c__cnc_lib_EXTERNAL_OBJECTS =

libc-cnc_lib.so: CMakeFiles/c-cnc_lib.dir/src/block.c.o
libc-cnc_lib.so: CMakeFiles/c-cnc_lib.dir/src/fsm.c.o
libc-cnc_lib.so: CMakeFiles/c-cnc_lib.dir/src/machine.c.o
libc-cnc_lib.so: CMakeFiles/c-cnc_lib.dir/src/point.c.o
libc-cnc_lib.so: CMakeFiles/c-cnc_lib.dir/src/program.c.o
libc-cnc_lib.so: CMakeFiles/c-cnc_lib.dir/src/toml.c.o
libc-cnc_lib.so: CMakeFiles/c-cnc_lib.dir/build.make
libc-cnc_lib.so: CMakeFiles/c-cnc_lib.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/home/marco/Desktop/Working directory/DM/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_7) "Linking C shared library libc-cnc_lib.so"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/c-cnc_lib.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/c-cnc_lib.dir/build: libc-cnc_lib.so
.PHONY : CMakeFiles/c-cnc_lib.dir/build

CMakeFiles/c-cnc_lib.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/c-cnc_lib.dir/cmake_clean.cmake
.PHONY : CMakeFiles/c-cnc_lib.dir/clean

CMakeFiles/c-cnc_lib.dir/depend:
	cd "/home/marco/Desktop/Working directory/DM/build" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/home/marco/Desktop/Working directory/DM" "/home/marco/Desktop/Working directory/DM" "/home/marco/Desktop/Working directory/DM/build" "/home/marco/Desktop/Working directory/DM/build" "/home/marco/Desktop/Working directory/DM/build/CMakeFiles/c-cnc_lib.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/c-cnc_lib.dir/depend

