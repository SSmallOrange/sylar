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
CMAKE_BINARY_DIR = /home/orange/workspace

# Include any dependencies generated for this target.
include CMakeFiles/sylar.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/sylar.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/sylar.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/sylar.dir/flags.make

CMakeFiles/sylar.dir/sylar/log.cpp.o: CMakeFiles/sylar.dir/flags.make
CMakeFiles/sylar.dir/sylar/log.cpp.o: sylar/log.cpp
CMakeFiles/sylar.dir/sylar/log.cpp.o: CMakeFiles/sylar.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/orange/workspace/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/sylar.dir/sylar/log.cpp.o"
	/usr/bin/clang++-14 $(CXX_DEFINES) -D__FILE__=\"sylar/log.cpp\" $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/sylar.dir/sylar/log.cpp.o -MF CMakeFiles/sylar.dir/sylar/log.cpp.o.d -o CMakeFiles/sylar.dir/sylar/log.cpp.o -c /home/orange/workspace/sylar/log.cpp

CMakeFiles/sylar.dir/sylar/log.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sylar.dir/sylar/log.cpp.i"
	/usr/bin/clang++-14 $(CXX_DEFINES) -D__FILE__=\"sylar/log.cpp\" $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/orange/workspace/sylar/log.cpp > CMakeFiles/sylar.dir/sylar/log.cpp.i

CMakeFiles/sylar.dir/sylar/log.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sylar.dir/sylar/log.cpp.s"
	/usr/bin/clang++-14 $(CXX_DEFINES) -D__FILE__=\"sylar/log.cpp\" $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/orange/workspace/sylar/log.cpp -o CMakeFiles/sylar.dir/sylar/log.cpp.s

CMakeFiles/sylar.dir/sylar/util.cpp.o: CMakeFiles/sylar.dir/flags.make
CMakeFiles/sylar.dir/sylar/util.cpp.o: sylar/util.cpp
CMakeFiles/sylar.dir/sylar/util.cpp.o: CMakeFiles/sylar.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/orange/workspace/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/sylar.dir/sylar/util.cpp.o"
	/usr/bin/clang++-14 $(CXX_DEFINES) -D__FILE__=\"sylar/util.cpp\" $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/sylar.dir/sylar/util.cpp.o -MF CMakeFiles/sylar.dir/sylar/util.cpp.o.d -o CMakeFiles/sylar.dir/sylar/util.cpp.o -c /home/orange/workspace/sylar/util.cpp

CMakeFiles/sylar.dir/sylar/util.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sylar.dir/sylar/util.cpp.i"
	/usr/bin/clang++-14 $(CXX_DEFINES) -D__FILE__=\"sylar/util.cpp\" $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/orange/workspace/sylar/util.cpp > CMakeFiles/sylar.dir/sylar/util.cpp.i

CMakeFiles/sylar.dir/sylar/util.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sylar.dir/sylar/util.cpp.s"
	/usr/bin/clang++-14 $(CXX_DEFINES) -D__FILE__=\"sylar/util.cpp\" $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/orange/workspace/sylar/util.cpp -o CMakeFiles/sylar.dir/sylar/util.cpp.s

CMakeFiles/sylar.dir/sylar/config.cpp.o: CMakeFiles/sylar.dir/flags.make
CMakeFiles/sylar.dir/sylar/config.cpp.o: sylar/config.cpp
CMakeFiles/sylar.dir/sylar/config.cpp.o: CMakeFiles/sylar.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/orange/workspace/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/sylar.dir/sylar/config.cpp.o"
	/usr/bin/clang++-14 $(CXX_DEFINES) -D__FILE__=\"sylar/config.cpp\" $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/sylar.dir/sylar/config.cpp.o -MF CMakeFiles/sylar.dir/sylar/config.cpp.o.d -o CMakeFiles/sylar.dir/sylar/config.cpp.o -c /home/orange/workspace/sylar/config.cpp

CMakeFiles/sylar.dir/sylar/config.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sylar.dir/sylar/config.cpp.i"
	/usr/bin/clang++-14 $(CXX_DEFINES) -D__FILE__=\"sylar/config.cpp\" $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/orange/workspace/sylar/config.cpp > CMakeFiles/sylar.dir/sylar/config.cpp.i

CMakeFiles/sylar.dir/sylar/config.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sylar.dir/sylar/config.cpp.s"
	/usr/bin/clang++-14 $(CXX_DEFINES) -D__FILE__=\"sylar/config.cpp\" $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/orange/workspace/sylar/config.cpp -o CMakeFiles/sylar.dir/sylar/config.cpp.s

CMakeFiles/sylar.dir/sylar/thread.cpp.o: CMakeFiles/sylar.dir/flags.make
CMakeFiles/sylar.dir/sylar/thread.cpp.o: sylar/thread.cpp
CMakeFiles/sylar.dir/sylar/thread.cpp.o: CMakeFiles/sylar.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/orange/workspace/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/sylar.dir/sylar/thread.cpp.o"
	/usr/bin/clang++-14 $(CXX_DEFINES) -D__FILE__=\"sylar/thread.cpp\" $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/sylar.dir/sylar/thread.cpp.o -MF CMakeFiles/sylar.dir/sylar/thread.cpp.o.d -o CMakeFiles/sylar.dir/sylar/thread.cpp.o -c /home/orange/workspace/sylar/thread.cpp

CMakeFiles/sylar.dir/sylar/thread.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sylar.dir/sylar/thread.cpp.i"
	/usr/bin/clang++-14 $(CXX_DEFINES) -D__FILE__=\"sylar/thread.cpp\" $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/orange/workspace/sylar/thread.cpp > CMakeFiles/sylar.dir/sylar/thread.cpp.i

CMakeFiles/sylar.dir/sylar/thread.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sylar.dir/sylar/thread.cpp.s"
	/usr/bin/clang++-14 $(CXX_DEFINES) -D__FILE__=\"sylar/thread.cpp\" $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/orange/workspace/sylar/thread.cpp -o CMakeFiles/sylar.dir/sylar/thread.cpp.s

# Object files for target sylar
sylar_OBJECTS = \
"CMakeFiles/sylar.dir/sylar/log.cpp.o" \
"CMakeFiles/sylar.dir/sylar/util.cpp.o" \
"CMakeFiles/sylar.dir/sylar/config.cpp.o" \
"CMakeFiles/sylar.dir/sylar/thread.cpp.o"

# External object files for target sylar
sylar_EXTERNAL_OBJECTS =

lib/libsylar.so: CMakeFiles/sylar.dir/sylar/log.cpp.o
lib/libsylar.so: CMakeFiles/sylar.dir/sylar/util.cpp.o
lib/libsylar.so: CMakeFiles/sylar.dir/sylar/config.cpp.o
lib/libsylar.so: CMakeFiles/sylar.dir/sylar/thread.cpp.o
lib/libsylar.so: CMakeFiles/sylar.dir/build.make
lib/libsylar.so: CMakeFiles/sylar.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/orange/workspace/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX shared library lib/libsylar.so"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/sylar.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/sylar.dir/build: lib/libsylar.so
.PHONY : CMakeFiles/sylar.dir/build

CMakeFiles/sylar.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/sylar.dir/cmake_clean.cmake
.PHONY : CMakeFiles/sylar.dir/clean

CMakeFiles/sylar.dir/depend:
	cd /home/orange/workspace && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/orange/workspace /home/orange/workspace /home/orange/workspace /home/orange/workspace /home/orange/workspace/CMakeFiles/sylar.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/sylar.dir/depend

