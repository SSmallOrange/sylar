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
CMAKE_SOURCE_DIR = /home/orange/workspace

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/orange/workspace/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/workspace.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/workspace.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/workspace.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/workspace.dir/flags.make

CMakeFiles/workspace.dir/main.cpp.o: CMakeFiles/workspace.dir/flags.make
CMakeFiles/workspace.dir/main.cpp.o: ../main.cpp
CMakeFiles/workspace.dir/main.cpp.o: CMakeFiles/workspace.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/orange/workspace/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/workspace.dir/main.cpp.o"
	/usr/bin/clang++-14 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/workspace.dir/main.cpp.o -MF CMakeFiles/workspace.dir/main.cpp.o.d -o CMakeFiles/workspace.dir/main.cpp.o -c /home/orange/workspace/main.cpp

CMakeFiles/workspace.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/workspace.dir/main.cpp.i"
	/usr/bin/clang++-14 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/orange/workspace/main.cpp > CMakeFiles/workspace.dir/main.cpp.i

CMakeFiles/workspace.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/workspace.dir/main.cpp.s"
	/usr/bin/clang++-14 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/orange/workspace/main.cpp -o CMakeFiles/workspace.dir/main.cpp.s

CMakeFiles/workspace.dir/sylar/log.cpp.o: CMakeFiles/workspace.dir/flags.make
CMakeFiles/workspace.dir/sylar/log.cpp.o: ../sylar/log.cpp
CMakeFiles/workspace.dir/sylar/log.cpp.o: CMakeFiles/workspace.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/orange/workspace/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/workspace.dir/sylar/log.cpp.o"
	/usr/bin/clang++-14 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/workspace.dir/sylar/log.cpp.o -MF CMakeFiles/workspace.dir/sylar/log.cpp.o.d -o CMakeFiles/workspace.dir/sylar/log.cpp.o -c /home/orange/workspace/sylar/log.cpp

CMakeFiles/workspace.dir/sylar/log.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/workspace.dir/sylar/log.cpp.i"
	/usr/bin/clang++-14 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/orange/workspace/sylar/log.cpp > CMakeFiles/workspace.dir/sylar/log.cpp.i

CMakeFiles/workspace.dir/sylar/log.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/workspace.dir/sylar/log.cpp.s"
	/usr/bin/clang++-14 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/orange/workspace/sylar/log.cpp -o CMakeFiles/workspace.dir/sylar/log.cpp.s

# Object files for target workspace
workspace_OBJECTS = \
"CMakeFiles/workspace.dir/main.cpp.o" \
"CMakeFiles/workspace.dir/sylar/log.cpp.o"

# External object files for target workspace
workspace_EXTERNAL_OBJECTS =

../bin/workspace: CMakeFiles/workspace.dir/main.cpp.o
../bin/workspace: CMakeFiles/workspace.dir/sylar/log.cpp.o
../bin/workspace: CMakeFiles/workspace.dir/build.make
../bin/workspace: CMakeFiles/workspace.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/orange/workspace/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable ../bin/workspace"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/workspace.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/workspace.dir/build: ../bin/workspace
.PHONY : CMakeFiles/workspace.dir/build

CMakeFiles/workspace.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/workspace.dir/cmake_clean.cmake
.PHONY : CMakeFiles/workspace.dir/clean

CMakeFiles/workspace.dir/depend:
	cd /home/orange/workspace/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/orange/workspace /home/orange/workspace /home/orange/workspace/cmake-build-debug /home/orange/workspace/cmake-build-debug /home/orange/workspace/cmake-build-debug/CMakeFiles/workspace.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/workspace.dir/depend

