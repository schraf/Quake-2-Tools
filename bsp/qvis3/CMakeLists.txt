cmake_minimum_required(VERSION 3.16)

project(qvis3)

add_executable(qvis3
	qvis3.c
	flow.c
	../../common/cmdlib.c
	../../common/mathlib.c
	../../common/scriplib.c
	../../common/threads.c
	../../common/bspfile.c)

target_include_directories(qvis3 PRIVATE ../../common)
