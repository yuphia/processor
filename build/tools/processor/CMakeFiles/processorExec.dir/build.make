# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
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
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/lev/Documents/processorChertov

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/lev/Documents/processorChertov/build

# Include any dependencies generated for this target.
include tools/processor/CMakeFiles/processorExec.dir/depend.make

# Include the progress variables for this target.
include tools/processor/CMakeFiles/processorExec.dir/progress.make

# Include the compile flags for this target's objects.
include tools/processor/CMakeFiles/processorExec.dir/flags.make

tools/processor/CMakeFiles/processorExec.dir/processor.cpp.o: tools/processor/CMakeFiles/processorExec.dir/flags.make
tools/processor/CMakeFiles/processorExec.dir/processor.cpp.o: ../tools/processor/processor.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lev/Documents/processorChertov/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object tools/processor/CMakeFiles/processorExec.dir/processor.cpp.o"
	cd /home/lev/Documents/processorChertov/build/tools/processor && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/processorExec.dir/processor.cpp.o -c /home/lev/Documents/processorChertov/tools/processor/processor.cpp

tools/processor/CMakeFiles/processorExec.dir/processor.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/processorExec.dir/processor.cpp.i"
	cd /home/lev/Documents/processorChertov/build/tools/processor && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/lev/Documents/processorChertov/tools/processor/processor.cpp > CMakeFiles/processorExec.dir/processor.cpp.i

tools/processor/CMakeFiles/processorExec.dir/processor.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/processorExec.dir/processor.cpp.s"
	cd /home/lev/Documents/processorChertov/build/tools/processor && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/lev/Documents/processorChertov/tools/processor/processor.cpp -o CMakeFiles/processorExec.dir/processor.cpp.s

# Object files for target processorExec
processorExec_OBJECTS = \
"CMakeFiles/processorExec.dir/processor.cpp.o"

# External object files for target processorExec
processorExec_EXTERNAL_OBJECTS =

tools/processor/processorExec: tools/processor/CMakeFiles/processorExec.dir/processor.cpp.o
tools/processor/processorExec: tools/processor/CMakeFiles/processorExec.dir/build.make
tools/processor/processorExec: tools/processor/CMakeFiles/processorExec.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/lev/Documents/processorChertov/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable processorExec"
	cd /home/lev/Documents/processorChertov/build/tools/processor && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/processorExec.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
tools/processor/CMakeFiles/processorExec.dir/build: tools/processor/processorExec

.PHONY : tools/processor/CMakeFiles/processorExec.dir/build

tools/processor/CMakeFiles/processorExec.dir/clean:
	cd /home/lev/Documents/processorChertov/build/tools/processor && $(CMAKE_COMMAND) -P CMakeFiles/processorExec.dir/cmake_clean.cmake
.PHONY : tools/processor/CMakeFiles/processorExec.dir/clean

tools/processor/CMakeFiles/processorExec.dir/depend:
	cd /home/lev/Documents/processorChertov/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/lev/Documents/processorChertov /home/lev/Documents/processorChertov/tools/processor /home/lev/Documents/processorChertov/build /home/lev/Documents/processorChertov/build/tools/processor /home/lev/Documents/processorChertov/build/tools/processor/CMakeFiles/processorExec.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : tools/processor/CMakeFiles/processorExec.dir/depend

