# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.0

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
CMAKE_SOURCE_DIR = /home/ugrads/class13/csd3221/antegeia

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ugrads/class13/csd3221/antegeia/build

# Include any dependencies generated for this target.
include lib/CMakeFiles/microtcp.dir/depend.make

# Include the progress variables for this target.
include lib/CMakeFiles/microtcp.dir/progress.make

# Include the compile flags for this target's objects.
include lib/CMakeFiles/microtcp.dir/flags.make

lib/CMakeFiles/microtcp.dir/microtcp.c.o: lib/CMakeFiles/microtcp.dir/flags.make
lib/CMakeFiles/microtcp.dir/microtcp.c.o: ../lib/microtcp.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/ugrads/class13/csd3221/antegeia/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object lib/CMakeFiles/microtcp.dir/microtcp.c.o"
	cd /home/ugrads/class13/csd3221/antegeia/build/lib && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/microtcp.dir/microtcp.c.o   -c /home/ugrads/class13/csd3221/antegeia/lib/microtcp.c

lib/CMakeFiles/microtcp.dir/microtcp.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/microtcp.dir/microtcp.c.i"
	cd /home/ugrads/class13/csd3221/antegeia/build/lib && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -E /home/ugrads/class13/csd3221/antegeia/lib/microtcp.c > CMakeFiles/microtcp.dir/microtcp.c.i

lib/CMakeFiles/microtcp.dir/microtcp.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/microtcp.dir/microtcp.c.s"
	cd /home/ugrads/class13/csd3221/antegeia/build/lib && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -S /home/ugrads/class13/csd3221/antegeia/lib/microtcp.c -o CMakeFiles/microtcp.dir/microtcp.c.s

lib/CMakeFiles/microtcp.dir/microtcp.c.o.requires:
.PHONY : lib/CMakeFiles/microtcp.dir/microtcp.c.o.requires

lib/CMakeFiles/microtcp.dir/microtcp.c.o.provides: lib/CMakeFiles/microtcp.dir/microtcp.c.o.requires
	$(MAKE) -f lib/CMakeFiles/microtcp.dir/build.make lib/CMakeFiles/microtcp.dir/microtcp.c.o.provides.build
.PHONY : lib/CMakeFiles/microtcp.dir/microtcp.c.o.provides

lib/CMakeFiles/microtcp.dir/microtcp.c.o.provides.build: lib/CMakeFiles/microtcp.dir/microtcp.c.o

# Object files for target microtcp
microtcp_OBJECTS = \
"CMakeFiles/microtcp.dir/microtcp.c.o"

# External object files for target microtcp
microtcp_EXTERNAL_OBJECTS =

lib/libmicrotcp.so: lib/CMakeFiles/microtcp.dir/microtcp.c.o
lib/libmicrotcp.so: lib/CMakeFiles/microtcp.dir/build.make
lib/libmicrotcp.so: lib/CMakeFiles/microtcp.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking C shared library libmicrotcp.so"
	cd /home/ugrads/class13/csd3221/antegeia/build/lib && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/microtcp.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
lib/CMakeFiles/microtcp.dir/build: lib/libmicrotcp.so
.PHONY : lib/CMakeFiles/microtcp.dir/build

lib/CMakeFiles/microtcp.dir/requires: lib/CMakeFiles/microtcp.dir/microtcp.c.o.requires
.PHONY : lib/CMakeFiles/microtcp.dir/requires

lib/CMakeFiles/microtcp.dir/clean:
	cd /home/ugrads/class13/csd3221/antegeia/build/lib && $(CMAKE_COMMAND) -P CMakeFiles/microtcp.dir/cmake_clean.cmake
.PHONY : lib/CMakeFiles/microtcp.dir/clean

lib/CMakeFiles/microtcp.dir/depend:
	cd /home/ugrads/class13/csd3221/antegeia/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ugrads/class13/csd3221/antegeia /home/ugrads/class13/csd3221/antegeia/lib /home/ugrads/class13/csd3221/antegeia/build /home/ugrads/class13/csd3221/antegeia/build/lib /home/ugrads/class13/csd3221/antegeia/build/lib/CMakeFiles/microtcp.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : lib/CMakeFiles/microtcp.dir/depend

