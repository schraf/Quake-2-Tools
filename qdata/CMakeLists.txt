cmake_minimum_required(VERSION 3.16)

project(qdata)

add_executable(qdata
	qdata.c
	models.c
	sprites.c
	images.c
	tables.c
	video.c
	../common/bspfile.c
	../common/cmdlib.c
	../common/scriplib.c
	../common/lbmlib.c
	../common/mathlib.c
	../common/mdfour.c
	../common/trilib.c
	../common/l3dslib.c
	../common/threads.c)

target_include_directories(qdata PRIVATE ../common)
