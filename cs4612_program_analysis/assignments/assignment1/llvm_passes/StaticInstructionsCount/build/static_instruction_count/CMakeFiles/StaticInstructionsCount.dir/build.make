# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

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
CMAKE_SOURCE_DIR = /home/ghani/Documents/Courses/Assignment_1/Project_1/llvm_passes/StaticInstructionsCount

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ghani/Documents/Courses/Assignment_1/Project_1/llvm_passes/StaticInstructionsCount/build

# Include any dependencies generated for this target.
include static_instruction_count/CMakeFiles/StaticInstructionsCount.dir/depend.make

# Include the progress variables for this target.
include static_instruction_count/CMakeFiles/StaticInstructionsCount.dir/progress.make

# Include the compile flags for this target's objects.
include static_instruction_count/CMakeFiles/StaticInstructionsCount.dir/flags.make

static_instruction_count/CMakeFiles/StaticInstructionsCount.dir/StaticInstructionsCount.cpp.o: static_instruction_count/CMakeFiles/StaticInstructionsCount.dir/flags.make
static_instruction_count/CMakeFiles/StaticInstructionsCount.dir/StaticInstructionsCount.cpp.o: ../static_instruction_count/StaticInstructionsCount.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ghani/Documents/Courses/Assignment_1/Project_1/llvm_passes/StaticInstructionsCount/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object static_instruction_count/CMakeFiles/StaticInstructionsCount.dir/StaticInstructionsCount.cpp.o"
	cd /home/ghani/Documents/Courses/Assignment_1/Project_1/llvm_passes/StaticInstructionsCount/build/static_instruction_count && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/StaticInstructionsCount.dir/StaticInstructionsCount.cpp.o -c /home/ghani/Documents/Courses/Assignment_1/Project_1/llvm_passes/StaticInstructionsCount/static_instruction_count/StaticInstructionsCount.cpp

static_instruction_count/CMakeFiles/StaticInstructionsCount.dir/StaticInstructionsCount.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/StaticInstructionsCount.dir/StaticInstructionsCount.cpp.i"
	cd /home/ghani/Documents/Courses/Assignment_1/Project_1/llvm_passes/StaticInstructionsCount/build/static_instruction_count && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ghani/Documents/Courses/Assignment_1/Project_1/llvm_passes/StaticInstructionsCount/static_instruction_count/StaticInstructionsCount.cpp > CMakeFiles/StaticInstructionsCount.dir/StaticInstructionsCount.cpp.i

static_instruction_count/CMakeFiles/StaticInstructionsCount.dir/StaticInstructionsCount.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/StaticInstructionsCount.dir/StaticInstructionsCount.cpp.s"
	cd /home/ghani/Documents/Courses/Assignment_1/Project_1/llvm_passes/StaticInstructionsCount/build/static_instruction_count && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ghani/Documents/Courses/Assignment_1/Project_1/llvm_passes/StaticInstructionsCount/static_instruction_count/StaticInstructionsCount.cpp -o CMakeFiles/StaticInstructionsCount.dir/StaticInstructionsCount.cpp.s

static_instruction_count/CMakeFiles/StaticInstructionsCount.dir/StaticInstructionsCount.cpp.o.requires:

.PHONY : static_instruction_count/CMakeFiles/StaticInstructionsCount.dir/StaticInstructionsCount.cpp.o.requires

static_instruction_count/CMakeFiles/StaticInstructionsCount.dir/StaticInstructionsCount.cpp.o.provides: static_instruction_count/CMakeFiles/StaticInstructionsCount.dir/StaticInstructionsCount.cpp.o.requires
	$(MAKE) -f static_instruction_count/CMakeFiles/StaticInstructionsCount.dir/build.make static_instruction_count/CMakeFiles/StaticInstructionsCount.dir/StaticInstructionsCount.cpp.o.provides.build
.PHONY : static_instruction_count/CMakeFiles/StaticInstructionsCount.dir/StaticInstructionsCount.cpp.o.provides

static_instruction_count/CMakeFiles/StaticInstructionsCount.dir/StaticInstructionsCount.cpp.o.provides.build: static_instruction_count/CMakeFiles/StaticInstructionsCount.dir/StaticInstructionsCount.cpp.o


# Object files for target StaticInstructionsCount
StaticInstructionsCount_OBJECTS = \
"CMakeFiles/StaticInstructionsCount.dir/StaticInstructionsCount.cpp.o"

# External object files for target StaticInstructionsCount
StaticInstructionsCount_EXTERNAL_OBJECTS =

static_instruction_count/libStaticInstructionsCount.so: static_instruction_count/CMakeFiles/StaticInstructionsCount.dir/StaticInstructionsCount.cpp.o
static_instruction_count/libStaticInstructionsCount.so: static_instruction_count/CMakeFiles/StaticInstructionsCount.dir/build.make
static_instruction_count/libStaticInstructionsCount.so: static_instruction_count/CMakeFiles/StaticInstructionsCount.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/ghani/Documents/Courses/Assignment_1/Project_1/llvm_passes/StaticInstructionsCount/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX shared module libStaticInstructionsCount.so"
	cd /home/ghani/Documents/Courses/Assignment_1/Project_1/llvm_passes/StaticInstructionsCount/build/static_instruction_count && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/StaticInstructionsCount.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
static_instruction_count/CMakeFiles/StaticInstructionsCount.dir/build: static_instruction_count/libStaticInstructionsCount.so

.PHONY : static_instruction_count/CMakeFiles/StaticInstructionsCount.dir/build

static_instruction_count/CMakeFiles/StaticInstructionsCount.dir/requires: static_instruction_count/CMakeFiles/StaticInstructionsCount.dir/StaticInstructionsCount.cpp.o.requires

.PHONY : static_instruction_count/CMakeFiles/StaticInstructionsCount.dir/requires

static_instruction_count/CMakeFiles/StaticInstructionsCount.dir/clean:
	cd /home/ghani/Documents/Courses/Assignment_1/Project_1/llvm_passes/StaticInstructionsCount/build/static_instruction_count && $(CMAKE_COMMAND) -P CMakeFiles/StaticInstructionsCount.dir/cmake_clean.cmake
.PHONY : static_instruction_count/CMakeFiles/StaticInstructionsCount.dir/clean

static_instruction_count/CMakeFiles/StaticInstructionsCount.dir/depend:
	cd /home/ghani/Documents/Courses/Assignment_1/Project_1/llvm_passes/StaticInstructionsCount/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ghani/Documents/Courses/Assignment_1/Project_1/llvm_passes/StaticInstructionsCount /home/ghani/Documents/Courses/Assignment_1/Project_1/llvm_passes/StaticInstructionsCount/static_instruction_count /home/ghani/Documents/Courses/Assignment_1/Project_1/llvm_passes/StaticInstructionsCount/build /home/ghani/Documents/Courses/Assignment_1/Project_1/llvm_passes/StaticInstructionsCount/build/static_instruction_count /home/ghani/Documents/Courses/Assignment_1/Project_1/llvm_passes/StaticInstructionsCount/build/static_instruction_count/CMakeFiles/StaticInstructionsCount.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : static_instruction_count/CMakeFiles/StaticInstructionsCount.dir/depend

