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
CMAKE_SOURCE_DIR = "/home/lupralo31/Escritorio/ROBOCUP CLON/robocup"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/home/lupralo31/Escritorio/ROBOCUP CLON/robocup"

# Include any dependencies generated for this target.
include CMakeFiles/player.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/player.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/player.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/player.dir/flags.make

CMakeFiles/player.dir/main.cpp.o: CMakeFiles/player.dir/flags.make
CMakeFiles/player.dir/main.cpp.o: main.cpp
CMakeFiles/player.dir/main.cpp.o: CMakeFiles/player.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/lupralo31/Escritorio/ROBOCUP CLON/robocup/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/player.dir/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/player.dir/main.cpp.o -MF CMakeFiles/player.dir/main.cpp.o.d -o CMakeFiles/player.dir/main.cpp.o -c "/home/lupralo31/Escritorio/ROBOCUP CLON/robocup/main.cpp"

CMakeFiles/player.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/player.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/lupralo31/Escritorio/ROBOCUP CLON/robocup/main.cpp" > CMakeFiles/player.dir/main.cpp.i

CMakeFiles/player.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/player.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/lupralo31/Escritorio/ROBOCUP CLON/robocup/main.cpp" -o CMakeFiles/player.dir/main.cpp.s

# Object files for target player
player_OBJECTS = \
"CMakeFiles/player.dir/main.cpp.o"

# External object files for target player
player_EXTERNAL_OBJECTS =

player: CMakeFiles/player.dir/main.cpp.o
player: CMakeFiles/player.dir/build.make
player: _deps/min_sock-build/src/libMinimalSocket.a
player: CMakeFiles/player.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/home/lupralo31/Escritorio/ROBOCUP CLON/robocup/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable player"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/player.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/player.dir/build: player
.PHONY : CMakeFiles/player.dir/build

CMakeFiles/player.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/player.dir/cmake_clean.cmake
.PHONY : CMakeFiles/player.dir/clean

CMakeFiles/player.dir/depend:
	cd "/home/lupralo31/Escritorio/ROBOCUP CLON/robocup" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/home/lupralo31/Escritorio/ROBOCUP CLON/robocup" "/home/lupralo31/Escritorio/ROBOCUP CLON/robocup" "/home/lupralo31/Escritorio/ROBOCUP CLON/robocup" "/home/lupralo31/Escritorio/ROBOCUP CLON/robocup" "/home/lupralo31/Escritorio/ROBOCUP CLON/robocup/CMakeFiles/player.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/player.dir/depend

