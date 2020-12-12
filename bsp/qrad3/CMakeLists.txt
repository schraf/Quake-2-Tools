cmake_minimum_required(VERSION 3.16)

project(qrad3)

add_executable(qrad3
	qrad3.c
	patches.c
	trace.c
	lightmap.c
	../../common/cmdlib.c
	../../common/lbmlib.c
	../../common/mathlib.c
	../../common/polylib.c
	../../common/scriplib.c
	../../common/threads.c
	../../common/bspfile.c)

target_include_directories(qrad3 PRIVATE ../../common)
