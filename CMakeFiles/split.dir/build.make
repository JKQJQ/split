# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.20

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
CMAKE_SOURCE_DIR = /home/team-10/split

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/team-10/split

# Include any dependencies generated for this target.
include CMakeFiles/split.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/split.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/split.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/split.dir/flags.make

CMakeFiles/split.dir/split.cpp.o: CMakeFiles/split.dir/flags.make
CMakeFiles/split.dir/split.cpp.o: split.cpp
CMakeFiles/split.dir/split.cpp.o: CMakeFiles/split.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/team-10/split/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/split.dir/split.cpp.o"
	/opt/anaconda3/bin/x86_64-conda-linux-gnu-c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/split.dir/split.cpp.o -MF CMakeFiles/split.dir/split.cpp.o.d -o CMakeFiles/split.dir/split.cpp.o -c /home/team-10/split/split.cpp

CMakeFiles/split.dir/split.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/split.dir/split.cpp.i"
	/opt/anaconda3/bin/x86_64-conda-linux-gnu-c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/team-10/split/split.cpp > CMakeFiles/split.dir/split.cpp.i

CMakeFiles/split.dir/split.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/split.dir/split.cpp.s"
	/opt/anaconda3/bin/x86_64-conda-linux-gnu-c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/team-10/split/split.cpp -o CMakeFiles/split.dir/split.cpp.s

# Object files for target split
split_OBJECTS = \
"CMakeFiles/split.dir/split.cpp.o"

# External object files for target split
split_EXTERNAL_OBJECTS =

split: CMakeFiles/split.dir/split.cpp.o
split: CMakeFiles/split.dir/build.make
split: /opt/anaconda3/lib/libhdf5.so
split: /opt/anaconda3/x86_64-conda-linux-gnu/sysroot/usr/lib/librt.so
split: /opt/anaconda3/x86_64-conda-linux-gnu/sysroot/usr/lib/libpthread.so
split: /opt/anaconda3/lib/libz.so
split: /opt/anaconda3/x86_64-conda-linux-gnu/sysroot/usr/lib/libdl.so
split: /opt/anaconda3/x86_64-conda-linux-gnu/sysroot/usr/lib/libm.so
split: /opt/anaconda3/lib/libhdf5_cpp.so
split: /opt/anaconda3/lib/libhdf5.so
split: /opt/anaconda3/x86_64-conda-linux-gnu/sysroot/usr/lib/librt.so
split: /opt/anaconda3/x86_64-conda-linux-gnu/sysroot/usr/lib/libpthread.so
split: /opt/anaconda3/lib/libz.so
split: /opt/anaconda3/x86_64-conda-linux-gnu/sysroot/usr/lib/libdl.so
split: /opt/anaconda3/x86_64-conda-linux-gnu/sysroot/usr/lib/libm.so
split: /opt/anaconda3/lib/libhdf5_cpp.so
split: CMakeFiles/split.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/team-10/split/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable split"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/split.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/split.dir/build: split
.PHONY : CMakeFiles/split.dir/build

CMakeFiles/split.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/split.dir/cmake_clean.cmake
.PHONY : CMakeFiles/split.dir/clean

CMakeFiles/split.dir/depend:
	cd /home/team-10/split && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/team-10/split /home/team-10/split /home/team-10/split /home/team-10/split /home/team-10/split/CMakeFiles/split.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/split.dir/depend

