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
include source/stackFunctions/CMakeFiles/stackFunctions.dir/depend.make

# Include the progress variables for this target.
include source/stackFunctions/CMakeFiles/stackFunctions.dir/progress.make

# Include the compile flags for this target's objects.
include source/stackFunctions/CMakeFiles/stackFunctions.dir/flags.make

source/stackFunctions/CMakeFiles/stackFunctions.dir/stackFunctions.cpp.o: source/stackFunctions/CMakeFiles/stackFunctions.dir/flags.make
source/stackFunctions/CMakeFiles/stackFunctions.dir/stackFunctions.cpp.o: ../source/stackFunctions/stackFunctions.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lev/Documents/processorChertov/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object source/stackFunctions/CMakeFiles/stackFunctions.dir/stackFunctions.cpp.o"
	cd /home/lev/Documents/processorChertov/build/source/stackFunctions && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/stackFunctions.dir/stackFunctions.cpp.o -c /home/lev/Documents/processorChertov/source/stackFunctions/stackFunctions.cpp

source/stackFunctions/CMakeFiles/stackFunctions.dir/stackFunctions.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/stackFunctions.dir/stackFunctions.cpp.i"
	cd /home/lev/Documents/processorChertov/build/source/stackFunctions && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/lev/Documents/processorChertov/source/stackFunctions/stackFunctions.cpp > CMakeFiles/stackFunctions.dir/stackFunctions.cpp.i

source/stackFunctions/CMakeFiles/stackFunctions.dir/stackFunctions.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/stackFunctions.dir/stackFunctions.cpp.s"
	cd /home/lev/Documents/processorChertov/build/source/stackFunctions && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/lev/Documents/processorChertov/source/stackFunctions/stackFunctions.cpp -o CMakeFiles/stackFunctions.dir/stackFunctions.cpp.s

# Object files for target stackFunctions
stackFunctions_OBJECTS = \
"CMakeFiles/stackFunctions.dir/stackFunctions.cpp.o"

# External object files for target stackFunctions
stackFunctions_EXTERNAL_OBJECTS =

source/stackFunctions/libstackFunctions.a: source/stackFunctions/CMakeFiles/stackFunctions.dir/stackFunctions.cpp.o
source/stackFunctions/libstackFunctions.a: source/stackFunctions/CMakeFiles/stackFunctions.dir/build.make
source/stackFunctions/libstackFunctions.a: source/stackFunctions/CMakeFiles/stackFunctions.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/lev/Documents/processorChertov/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libstackFunctions.a"
	cd /home/lev/Documents/processorChertov/build/source/stackFunctions && $(CMAKE_COMMAND) -P CMakeFiles/stackFunctions.dir/cmake_clean_target.cmake
	cd /home/lev/Documents/processorChertov/build/source/stackFunctions && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/stackFunctions.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
source/stackFunctions/CMakeFiles/stackFunctions.dir/build: source/stackFunctions/libstackFunctions.a

.PHONY : source/stackFunctions/CMakeFiles/stackFunctions.dir/build

source/stackFunctions/CMakeFiles/stackFunctions.dir/clean:
	cd /home/lev/Documents/processorChertov/build/source/stackFunctions && $(CMAKE_COMMAND) -P CMakeFiles/stackFunctions.dir/cmake_clean.cmake
.PHONY : source/stackFunctions/CMakeFiles/stackFunctions.dir/clean

source/stackFunctions/CMakeFiles/stackFunctions.dir/depend:
	cd /home/lev/Documents/processorChertov/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/lev/Documents/processorChertov /home/lev/Documents/processorChertov/source/stackFunctions /home/lev/Documents/processorChertov/build /home/lev/Documents/processorChertov/build/source/stackFunctions /home/lev/Documents/processorChertov/build/source/stackFunctions/CMakeFiles/stackFunctions.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : source/stackFunctions/CMakeFiles/stackFunctions.dir/depend

