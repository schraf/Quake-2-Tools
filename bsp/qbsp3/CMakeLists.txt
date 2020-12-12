cmake_minimum_required(VERSION 3.16)

project(qbsp3)

add_executable(qbsp3
	brushbsp.c
	faces.c
	nodraw.c
	glfile.c
	leakfile.c
	map.c
	portals.c
	prtfile.c
	qbsp3.c
	tree.c
	textures.c
	writebsp.c
	csg.c
	../../common/cmdlib.c
	../../common/mathlib.c
	../../common/polylib.c
	../../common/scriplib.c
	../../common/threads.c
	../../common/bspfile.c)

target_include_directories(qbsp3 PRIVATE ../../common)
