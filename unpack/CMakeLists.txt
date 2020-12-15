cmake_minimum_required(VERSION 3.16)

project(unpack)

add_executable(unpack
	unpack.c
	../common/cmdlib.c)

target_include_directories(unpack PRIVATE ../common)
