cmake_minimum_required (VERSION 2.6)
project (SHMUP-Test)
# The version number.
set (SHMUP-Test_Version_Major 0)
set (SHMUP-Test_Version_Minor 1)

# configure a header file to pass some of the CMake settings
# to the source code
configure_file (
	"${PROJECT_SOURCE_DIR}/shmuptest.h.in"
	"${PROJECT_BINARY_DIR}/shmuptest.h"
	)

# add the binary tree to the search path for include files
# so that we will find TutorialConfig.h
include_directories("${PROJECT_BINARY_DIR}")

# add the executable
add_executable(shmup-test main.cxx)