# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.3

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
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.3.2/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.3.2/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/george/Documents/cpp/City-Map

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/george/Documents/cpp/City-Map/build

# Include any dependencies generated for this target.
include CMakeFiles/solution.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/solution.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/solution.dir/flags.make

CMakeFiles/solution.dir/src/city_map.cpp.o: CMakeFiles/solution.dir/flags.make
CMakeFiles/solution.dir/src/city_map.cpp.o: ../src/city_map.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/george/Documents/cpp/City-Map/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/solution.dir/src/city_map.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/solution.dir/src/city_map.cpp.o -c /Users/george/Documents/cpp/City-Map/src/city_map.cpp

CMakeFiles/solution.dir/src/city_map.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/solution.dir/src/city_map.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /Users/george/Documents/cpp/City-Map/src/city_map.cpp > CMakeFiles/solution.dir/src/city_map.cpp.i

CMakeFiles/solution.dir/src/city_map.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/solution.dir/src/city_map.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /Users/george/Documents/cpp/City-Map/src/city_map.cpp -o CMakeFiles/solution.dir/src/city_map.cpp.s

CMakeFiles/solution.dir/src/city_map.cpp.o.requires:

.PHONY : CMakeFiles/solution.dir/src/city_map.cpp.o.requires

CMakeFiles/solution.dir/src/city_map.cpp.o.provides: CMakeFiles/solution.dir/src/city_map.cpp.o.requires
	$(MAKE) -f CMakeFiles/solution.dir/build.make CMakeFiles/solution.dir/src/city_map.cpp.o.provides.build
.PHONY : CMakeFiles/solution.dir/src/city_map.cpp.o.provides

CMakeFiles/solution.dir/src/city_map.cpp.o.provides.build: CMakeFiles/solution.dir/src/city_map.cpp.o


CMakeFiles/solution.dir/src/interactive_city_map.cpp.o: CMakeFiles/solution.dir/flags.make
CMakeFiles/solution.dir/src/interactive_city_map.cpp.o: ../src/interactive_city_map.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/george/Documents/cpp/City-Map/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/solution.dir/src/interactive_city_map.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/solution.dir/src/interactive_city_map.cpp.o -c /Users/george/Documents/cpp/City-Map/src/interactive_city_map.cpp

CMakeFiles/solution.dir/src/interactive_city_map.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/solution.dir/src/interactive_city_map.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /Users/george/Documents/cpp/City-Map/src/interactive_city_map.cpp > CMakeFiles/solution.dir/src/interactive_city_map.cpp.i

CMakeFiles/solution.dir/src/interactive_city_map.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/solution.dir/src/interactive_city_map.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /Users/george/Documents/cpp/City-Map/src/interactive_city_map.cpp -o CMakeFiles/solution.dir/src/interactive_city_map.cpp.s

CMakeFiles/solution.dir/src/interactive_city_map.cpp.o.requires:

.PHONY : CMakeFiles/solution.dir/src/interactive_city_map.cpp.o.requires

CMakeFiles/solution.dir/src/interactive_city_map.cpp.o.provides: CMakeFiles/solution.dir/src/interactive_city_map.cpp.o.requires
	$(MAKE) -f CMakeFiles/solution.dir/build.make CMakeFiles/solution.dir/src/interactive_city_map.cpp.o.provides.build
.PHONY : CMakeFiles/solution.dir/src/interactive_city_map.cpp.o.provides

CMakeFiles/solution.dir/src/interactive_city_map.cpp.o.provides.build: CMakeFiles/solution.dir/src/interactive_city_map.cpp.o


CMakeFiles/solution.dir/src/main.cpp.o: CMakeFiles/solution.dir/flags.make
CMakeFiles/solution.dir/src/main.cpp.o: ../src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/george/Documents/cpp/City-Map/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/solution.dir/src/main.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/solution.dir/src/main.cpp.o -c /Users/george/Documents/cpp/City-Map/src/main.cpp

CMakeFiles/solution.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/solution.dir/src/main.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /Users/george/Documents/cpp/City-Map/src/main.cpp > CMakeFiles/solution.dir/src/main.cpp.i

CMakeFiles/solution.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/solution.dir/src/main.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /Users/george/Documents/cpp/City-Map/src/main.cpp -o CMakeFiles/solution.dir/src/main.cpp.s

CMakeFiles/solution.dir/src/main.cpp.o.requires:

.PHONY : CMakeFiles/solution.dir/src/main.cpp.o.requires

CMakeFiles/solution.dir/src/main.cpp.o.provides: CMakeFiles/solution.dir/src/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/solution.dir/build.make CMakeFiles/solution.dir/src/main.cpp.o.provides.build
.PHONY : CMakeFiles/solution.dir/src/main.cpp.o.provides

CMakeFiles/solution.dir/src/main.cpp.o.provides.build: CMakeFiles/solution.dir/src/main.cpp.o


# Object files for target solution
solution_OBJECTS = \
"CMakeFiles/solution.dir/src/city_map.cpp.o" \
"CMakeFiles/solution.dir/src/interactive_city_map.cpp.o" \
"CMakeFiles/solution.dir/src/main.cpp.o"

# External object files for target solution
solution_EXTERNAL_OBJECTS =

solution: CMakeFiles/solution.dir/src/city_map.cpp.o
solution: CMakeFiles/solution.dir/src/interactive_city_map.cpp.o
solution: CMakeFiles/solution.dir/src/main.cpp.o
solution: CMakeFiles/solution.dir/build.make
solution: CMakeFiles/solution.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/george/Documents/cpp/City-Map/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable solution"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/solution.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/solution.dir/build: solution

.PHONY : CMakeFiles/solution.dir/build

CMakeFiles/solution.dir/requires: CMakeFiles/solution.dir/src/city_map.cpp.o.requires
CMakeFiles/solution.dir/requires: CMakeFiles/solution.dir/src/interactive_city_map.cpp.o.requires
CMakeFiles/solution.dir/requires: CMakeFiles/solution.dir/src/main.cpp.o.requires

.PHONY : CMakeFiles/solution.dir/requires

CMakeFiles/solution.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/solution.dir/cmake_clean.cmake
.PHONY : CMakeFiles/solution.dir/clean

CMakeFiles/solution.dir/depend:
	cd /Users/george/Documents/cpp/City-Map/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/george/Documents/cpp/City-Map /Users/george/Documents/cpp/City-Map /Users/george/Documents/cpp/City-Map/build /Users/george/Documents/cpp/City-Map/build /Users/george/Documents/cpp/City-Map/build/CMakeFiles/solution.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/solution.dir/depend

