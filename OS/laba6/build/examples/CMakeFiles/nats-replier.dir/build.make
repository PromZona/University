# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.14

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
CMAKE_COMMAND = /usr/bin/cmake.exe

# The command to remove a file.
RM = /usr/bin/cmake.exe -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/cygdrive/d/YaDisk/YandexDisk/МАИ/Andrew/2 курс/labs/University/OS/laba6/nats_client"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/cygdrive/d/YaDisk/YandexDisk/МАИ/Andrew/2 курс/labs/University/OS/laba6/build"

# Include any dependencies generated for this target.
include examples/CMakeFiles/nats-replier.dir/depend.make

# Include the progress variables for this target.
include examples/CMakeFiles/nats-replier.dir/progress.make

# Include the compile flags for this target's objects.
include examples/CMakeFiles/nats-replier.dir/flags.make

examples/CMakeFiles/nats-replier.dir/replier.c.o: examples/CMakeFiles/nats-replier.dir/flags.make
examples/CMakeFiles/nats-replier.dir/replier.c.o: /cygdrive/d/YaDisk/YandexDisk/МАИ/Andrew/2\ курс/labs/University/OS/laba6/nats_client/examples/replier.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/cygdrive/d/YaDisk/YandexDisk/МАИ/Andrew/2 курс/labs/University/OS/laba6/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building C object examples/CMakeFiles/nats-replier.dir/replier.c.o"
	cd "/cygdrive/d/YaDisk/YandexDisk/МАИ/Andrew/2 курс/labs/University/OS/laba6/build/examples" && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/nats-replier.dir/replier.c.o   -c "/cygdrive/d/YaDisk/YandexDisk/МАИ/Andrew/2 курс/labs/University/OS/laba6/nats_client/examples/replier.c"

examples/CMakeFiles/nats-replier.dir/replier.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/nats-replier.dir/replier.c.i"
	cd "/cygdrive/d/YaDisk/YandexDisk/МАИ/Andrew/2 курс/labs/University/OS/laba6/build/examples" && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/cygdrive/d/YaDisk/YandexDisk/МАИ/Andrew/2 курс/labs/University/OS/laba6/nats_client/examples/replier.c" > CMakeFiles/nats-replier.dir/replier.c.i

examples/CMakeFiles/nats-replier.dir/replier.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/nats-replier.dir/replier.c.s"
	cd "/cygdrive/d/YaDisk/YandexDisk/МАИ/Andrew/2 курс/labs/University/OS/laba6/build/examples" && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/cygdrive/d/YaDisk/YandexDisk/МАИ/Andrew/2 курс/labs/University/OS/laba6/nats_client/examples/replier.c" -o CMakeFiles/nats-replier.dir/replier.c.s

# Object files for target nats-replier
nats__replier_OBJECTS = \
"CMakeFiles/nats-replier.dir/replier.c.o"

# External object files for target nats-replier
nats__replier_EXTERNAL_OBJECTS =

examples/nats-replier.exe: examples/CMakeFiles/nats-replier.dir/replier.c.o
examples/nats-replier.exe: examples/CMakeFiles/nats-replier.dir/build.make
examples/nats-replier.exe: src/libnats.dll.a
examples/nats-replier.exe: examples/CMakeFiles/nats-replier.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/cygdrive/d/YaDisk/YandexDisk/МАИ/Andrew/2 курс/labs/University/OS/laba6/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable nats-replier.exe"
	cd "/cygdrive/d/YaDisk/YandexDisk/МАИ/Andrew/2 курс/labs/University/OS/laba6/build/examples" && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/nats-replier.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
examples/CMakeFiles/nats-replier.dir/build: examples/nats-replier.exe

.PHONY : examples/CMakeFiles/nats-replier.dir/build

examples/CMakeFiles/nats-replier.dir/clean:
	cd "/cygdrive/d/YaDisk/YandexDisk/МАИ/Andrew/2 курс/labs/University/OS/laba6/build/examples" && $(CMAKE_COMMAND) -P CMakeFiles/nats-replier.dir/cmake_clean.cmake
.PHONY : examples/CMakeFiles/nats-replier.dir/clean

examples/CMakeFiles/nats-replier.dir/depend:
	cd "/cygdrive/d/YaDisk/YandexDisk/МАИ/Andrew/2 курс/labs/University/OS/laba6/build" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/cygdrive/d/YaDisk/YandexDisk/МАИ/Andrew/2 курс/labs/University/OS/laba6/nats_client" "/cygdrive/d/YaDisk/YandexDisk/МАИ/Andrew/2 курс/labs/University/OS/laba6/nats_client/examples" "/cygdrive/d/YaDisk/YandexDisk/МАИ/Andrew/2 курс/labs/University/OS/laba6/build" "/cygdrive/d/YaDisk/YandexDisk/МАИ/Andrew/2 курс/labs/University/OS/laba6/build/examples" "/cygdrive/d/YaDisk/YandexDisk/МАИ/Andrew/2 курс/labs/University/OS/laba6/build/examples/CMakeFiles/nats-replier.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : examples/CMakeFiles/nats-replier.dir/depend

