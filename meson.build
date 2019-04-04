project(
	'halide_sample',
	'cpp',
	default_options:['cpp_std=c++11', 'warning_level=2'])
sources = [
	'back_projection.cpp',
]
LOCAL_DIR = '/home/masato/.local'
HALIDE_BIN_DIR = join_paths(LOCAL_DIR, 'bin')
HALIDE_INC_DIR = join_paths(LOCAL_DIR, 'include')
cc = meson.get_compiler('cpp')
curses = cc.find_library('libcurses')
halide = cc.find_library('libHalide', dirs:[HALIDE_BIN_DIR])
ctlib = static_library(
	'ct',
	sources,
	include_directories:[
		HALIDE_INC_DIR,
	],
	dependencies:[
		halide,
		curses
	])

subdir('test')
