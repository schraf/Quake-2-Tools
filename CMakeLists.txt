cmake_minimum_required(VERSION 3.16)

project(Quake2Tools)

if (MSVC)
	add_compile_options(/W4 /WX)
	add_compile_definitions(_CRT_SECURE_NO_DEPRECATE)
else()
	add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()

add_subdirectory("bsp")
add_subdirectory("unpack")
