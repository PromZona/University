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
include examples/CMakeFiles/nats-connect.dir/depend.make

# Include the progress variables for this target.
include examples/CMakeFiles/nats-connect.dir/progress.make

# Include the compile flags for this target's objects.
include examples/CMakeFiles/nats-connect.dir/flags.make

examples/CMakeFiles/nats-connect.dir/connect.c.o: examples/CMakeFiles/nats-connect.dir/flags.make
examples/CMakeFiles/nats-connect.dir/connect.c.o: /cygdrive/d/YaDisk/YandexDisk/МАИ/Andrew/2\ курс/labs/University/OS/laba6/nats_client/examples/connect.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/cygdrive/d/YaDisk/YandexDisk/МАИ/Andrew/2 курс/labs/University/OS/laba6/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building C object examples/CMakeFiles/nats-connect.dir/connect.c.o"
	cd "/cygdrive/d/YaDisk/YandexDisk/МАИ/Andrew/2 курс/labs/University/OS/laba6/build/examples" && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/nats-connect.dir/connect.c.o   -c "/cygdrive/d/YaDisk/YandexDisk/МАИ/Andrew/2 курс/labs/University/OS/laba6/nats_client/examples/connect.c"

examples/CMakeFiles/nats-connect.dir/connect.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/nats-connect.dir/connect.c.i"
	cd "/cygdrive/d/YaDisk/YandexDisk/МАИ/Andrew/2 курс/labs/University/OS/laba6/build/examples" && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/cygdrive/d/YaDisk/YandexDisk/МАИ/Andrew/2 курс/labs/University/OS/laba6/nats_client/examples/connect.c" > CMakeFiles/nats-connect.dir/connect.c.i

examples/CMakeFiles/nats-connect.dir/connect.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/nats-connect.dir/connect.c.s"
	cd "/cygdrive/d/YaDisk/YandexDisk/МАИ/Andrew/2 курс/labs/University/OS/laba6/build/examples" && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/cygdrive/d/YaDisk/YandexDisk/МАИ/Andrew/2 курс/labs/University/OS/laba6/nats_client/examples/connect.c" -o CMakeFiles/nats-connect.dir/connect.c.s

# Object files for target nats-connect
nats__connect_OBJECTS = \
"CMakeFiles/nats-connect.dir/connect.c.o"

# External object files for target nats-connect
nats__connect_EXTERNAL_OBJECTS =

examples/nats-connect.exe: examples/CMakeFiles/nats-connect.dir/connect.c.o
examples/nats-connect.exe: examples/CMakeFiles/nats-connect.dir/build.make
examples/nats-connect.exe: src/libnats.dll.a
examples/nats-connect.exe: examples/CMakeFiles/nats-connect.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/cygdrive/d/YaDisk/YandexDisk/МАИ/Andrew/2 курс/labs/University/OS/laba6/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable nats-connect.exe"
	cd "/cygdrive/d/YaDisk/YandexDisk/МАИ/Andrew/2 курс/labs/University/OS/laba6/build/examples" && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/nats-connect.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
examples/CMakeFiles/nats-connect.dir/build: examples/nats-connect.exe

.PHONY : examples/CMakeFiles/nats-connect.dir/build

examples/CMakeFiles/nats-connect.dir/clean:
	cd "/cygdrive/d/YaDisk/YandexDisk/МАИ/Andrew/2 курс/labs/University/OS/laba6/build/examples" && $(CMAKE_COMMAND) -P CMakeFiles/nats-connect.dir/cmake_clean.cmake
.PHONY : examples/CMakeFiles/nats-connect.dir/clean

examples/CMakeFiles/nats-connect.dir/depend:
	cd "/cygdrive/d/YaDisk/YandexDisk/МАИ/Andrew/2 курс/labs/University/OS/laba6/build" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/cygdrive/d/YaDisk/YandexDisk/МАИ/Andrew/2 курс/labs/University/OS/laba6/nats_client" "/cygdrive/d/YaDisk/YandexDisk/МАИ/Andrew/2 курс/labs/University/OS/laba6/nats_client/examples" "/cygdrive/d/YaDisk/YandexDisk/МАИ/Andrew/2 курс/labs/University/OS/laba6/build" "/cygdrive/d/YaDisk/YandexDisk/МАИ/Andrew/2 курс/labs/University/OS/laba6/build/examples" "/cygdrive/d/YaDisk/YandexDisk/МАИ/Andrew/2 курс/labs/University/OS/laba6/build/examples/CMakeFiles/nats-connect.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : examples/CMakeFiles/nats-connect.dir/depend

