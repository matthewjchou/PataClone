# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

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
CMAKE_SOURCE_DIR = /home/matt/Downloads/Box2D_v2.1.2/Box2D/Testbed

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/matt/Downloads/Box2D_v2.1.2/Box2D/Testbed

# Include any dependencies generated for this target.
include CMakeFiles/Testbed.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Testbed.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Testbed.dir/flags.make

CMakeFiles/Testbed.dir/Framework/Main.o: CMakeFiles/Testbed.dir/flags.make
CMakeFiles/Testbed.dir/Framework/Main.o: Framework/Main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/matt/Downloads/Box2D_v2.1.2/Box2D/Testbed/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Testbed.dir/Framework/Main.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Testbed.dir/Framework/Main.o -c /home/matt/Downloads/Box2D_v2.1.2/Box2D/Testbed/Framework/Main.cpp

CMakeFiles/Testbed.dir/Framework/Main.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Testbed.dir/Framework/Main.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/matt/Downloads/Box2D_v2.1.2/Box2D/Testbed/Framework/Main.cpp > CMakeFiles/Testbed.dir/Framework/Main.i

CMakeFiles/Testbed.dir/Framework/Main.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Testbed.dir/Framework/Main.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/matt/Downloads/Box2D_v2.1.2/Box2D/Testbed/Framework/Main.cpp -o CMakeFiles/Testbed.dir/Framework/Main.s

CMakeFiles/Testbed.dir/Framework/Main.o.requires:

.PHONY : CMakeFiles/Testbed.dir/Framework/Main.o.requires

CMakeFiles/Testbed.dir/Framework/Main.o.provides: CMakeFiles/Testbed.dir/Framework/Main.o.requires
	$(MAKE) -f CMakeFiles/Testbed.dir/build.make CMakeFiles/Testbed.dir/Framework/Main.o.provides.build
.PHONY : CMakeFiles/Testbed.dir/Framework/Main.o.provides

CMakeFiles/Testbed.dir/Framework/Main.o.provides.build: CMakeFiles/Testbed.dir/Framework/Main.o


CMakeFiles/Testbed.dir/Framework/Render.o: CMakeFiles/Testbed.dir/flags.make
CMakeFiles/Testbed.dir/Framework/Render.o: Framework/Render.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/matt/Downloads/Box2D_v2.1.2/Box2D/Testbed/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/Testbed.dir/Framework/Render.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Testbed.dir/Framework/Render.o -c /home/matt/Downloads/Box2D_v2.1.2/Box2D/Testbed/Framework/Render.cpp

CMakeFiles/Testbed.dir/Framework/Render.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Testbed.dir/Framework/Render.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/matt/Downloads/Box2D_v2.1.2/Box2D/Testbed/Framework/Render.cpp > CMakeFiles/Testbed.dir/Framework/Render.i

CMakeFiles/Testbed.dir/Framework/Render.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Testbed.dir/Framework/Render.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/matt/Downloads/Box2D_v2.1.2/Box2D/Testbed/Framework/Render.cpp -o CMakeFiles/Testbed.dir/Framework/Render.s

CMakeFiles/Testbed.dir/Framework/Render.o.requires:

.PHONY : CMakeFiles/Testbed.dir/Framework/Render.o.requires

CMakeFiles/Testbed.dir/Framework/Render.o.provides: CMakeFiles/Testbed.dir/Framework/Render.o.requires
	$(MAKE) -f CMakeFiles/Testbed.dir/build.make CMakeFiles/Testbed.dir/Framework/Render.o.provides.build
.PHONY : CMakeFiles/Testbed.dir/Framework/Render.o.provides

CMakeFiles/Testbed.dir/Framework/Render.o.provides.build: CMakeFiles/Testbed.dir/Framework/Render.o


CMakeFiles/Testbed.dir/Framework/Test.o: CMakeFiles/Testbed.dir/flags.make
CMakeFiles/Testbed.dir/Framework/Test.o: Framework/Test.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/matt/Downloads/Box2D_v2.1.2/Box2D/Testbed/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/Testbed.dir/Framework/Test.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Testbed.dir/Framework/Test.o -c /home/matt/Downloads/Box2D_v2.1.2/Box2D/Testbed/Framework/Test.cpp

CMakeFiles/Testbed.dir/Framework/Test.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Testbed.dir/Framework/Test.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/matt/Downloads/Box2D_v2.1.2/Box2D/Testbed/Framework/Test.cpp > CMakeFiles/Testbed.dir/Framework/Test.i

CMakeFiles/Testbed.dir/Framework/Test.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Testbed.dir/Framework/Test.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/matt/Downloads/Box2D_v2.1.2/Box2D/Testbed/Framework/Test.cpp -o CMakeFiles/Testbed.dir/Framework/Test.s

CMakeFiles/Testbed.dir/Framework/Test.o.requires:

.PHONY : CMakeFiles/Testbed.dir/Framework/Test.o.requires

CMakeFiles/Testbed.dir/Framework/Test.o.provides: CMakeFiles/Testbed.dir/Framework/Test.o.requires
	$(MAKE) -f CMakeFiles/Testbed.dir/build.make CMakeFiles/Testbed.dir/Framework/Test.o.provides.build
.PHONY : CMakeFiles/Testbed.dir/Framework/Test.o.provides

CMakeFiles/Testbed.dir/Framework/Test.o.provides.build: CMakeFiles/Testbed.dir/Framework/Test.o


CMakeFiles/Testbed.dir/Tests/TestEntries.o: CMakeFiles/Testbed.dir/flags.make
CMakeFiles/Testbed.dir/Tests/TestEntries.o: Tests/TestEntries.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/matt/Downloads/Box2D_v2.1.2/Box2D/Testbed/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/Testbed.dir/Tests/TestEntries.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Testbed.dir/Tests/TestEntries.o -c /home/matt/Downloads/Box2D_v2.1.2/Box2D/Testbed/Tests/TestEntries.cpp

CMakeFiles/Testbed.dir/Tests/TestEntries.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Testbed.dir/Tests/TestEntries.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/matt/Downloads/Box2D_v2.1.2/Box2D/Testbed/Tests/TestEntries.cpp > CMakeFiles/Testbed.dir/Tests/TestEntries.i

CMakeFiles/Testbed.dir/Tests/TestEntries.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Testbed.dir/Tests/TestEntries.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/matt/Downloads/Box2D_v2.1.2/Box2D/Testbed/Tests/TestEntries.cpp -o CMakeFiles/Testbed.dir/Tests/TestEntries.s

CMakeFiles/Testbed.dir/Tests/TestEntries.o.requires:

.PHONY : CMakeFiles/Testbed.dir/Tests/TestEntries.o.requires

CMakeFiles/Testbed.dir/Tests/TestEntries.o.provides: CMakeFiles/Testbed.dir/Tests/TestEntries.o.requires
	$(MAKE) -f CMakeFiles/Testbed.dir/build.make CMakeFiles/Testbed.dir/Tests/TestEntries.o.provides.build
.PHONY : CMakeFiles/Testbed.dir/Tests/TestEntries.o.provides

CMakeFiles/Testbed.dir/Tests/TestEntries.o.provides.build: CMakeFiles/Testbed.dir/Tests/TestEntries.o


# Object files for target Testbed
Testbed_OBJECTS = \
"CMakeFiles/Testbed.dir/Framework/Main.o" \
"CMakeFiles/Testbed.dir/Framework/Render.o" \
"CMakeFiles/Testbed.dir/Framework/Test.o" \
"CMakeFiles/Testbed.dir/Tests/TestEntries.o"

# External object files for target Testbed
Testbed_EXTERNAL_OBJECTS =

Testbed: CMakeFiles/Testbed.dir/Framework/Main.o
Testbed: CMakeFiles/Testbed.dir/Framework/Render.o
Testbed: CMakeFiles/Testbed.dir/Framework/Test.o
Testbed: CMakeFiles/Testbed.dir/Tests/TestEntries.o
Testbed: CMakeFiles/Testbed.dir/build.make
Testbed: CMakeFiles/Testbed.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/matt/Downloads/Box2D_v2.1.2/Box2D/Testbed/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX executable Testbed"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Testbed.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Testbed.dir/build: Testbed

.PHONY : CMakeFiles/Testbed.dir/build

CMakeFiles/Testbed.dir/requires: CMakeFiles/Testbed.dir/Framework/Main.o.requires
CMakeFiles/Testbed.dir/requires: CMakeFiles/Testbed.dir/Framework/Render.o.requires
CMakeFiles/Testbed.dir/requires: CMakeFiles/Testbed.dir/Framework/Test.o.requires
CMakeFiles/Testbed.dir/requires: CMakeFiles/Testbed.dir/Tests/TestEntries.o.requires

.PHONY : CMakeFiles/Testbed.dir/requires

CMakeFiles/Testbed.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Testbed.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Testbed.dir/clean

CMakeFiles/Testbed.dir/depend:
	cd /home/matt/Downloads/Box2D_v2.1.2/Box2D/Testbed && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/matt/Downloads/Box2D_v2.1.2/Box2D/Testbed /home/matt/Downloads/Box2D_v2.1.2/Box2D/Testbed /home/matt/Downloads/Box2D_v2.1.2/Box2D/Testbed /home/matt/Downloads/Box2D_v2.1.2/Box2D/Testbed /home/matt/Downloads/Box2D_v2.1.2/Box2D/Testbed/CMakeFiles/Testbed.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Testbed.dir/depend

