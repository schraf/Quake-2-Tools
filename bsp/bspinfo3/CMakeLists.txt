cmake_minimum_required(VERSION 3.16)

project(bspinfo3)

add_executable(bspinfo3
	bspinfo3.c
	../../common/cmdlib.c
	../../common/scriplib.c
	../../common/bspfile.c)

target_include_directories(bspinfo3 PRIVATE ../../common)
