# Set the minimum version of CMake that can be used
# To find the cmake version run
# $ cmake --version
cmake_minimum_required(VERSION 3.5)

# Set the project name
project (elfsection)

SET(CMAKE_C_COMPILER gcc)
SET(CMAKE_C_FLAGS "-Wall -g -O2")

add_library(elfsection	
	SHARED
	#STATIC
	elf_section.c
)

