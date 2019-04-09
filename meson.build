project(
	'halide_sample',
	'cpp',
	default_options:[
		'cpp_std=c++11',
		'warning_level=2'
	])
sources = [
	'back_projection.cpp',
]
LOCAL_DIR = '/home/masato/.local'
inc = include_directories('include')
HALIDE_BIN_DIR = join_paths(LOCAL_DIR, 'bin')
HALIDE_INC_DIR = join_paths(LOCAL_DIR, 'include')
cc = meson.get_compiler('cpp')
curses = cc.find_library('libcurses')
halide = cc.find_library('libHalide', dirs:[HALIDE_BIN_DIR])
ctlib = static_library(
	'ct',
	sources,
	# cpp_args is currently used to suppress Halide's
	# compiler warnings.
	cpp_args:[
		'-Wno-unused-parameter',
		'-Wno-missing-field-initializers',
	],
	include_directories:[
		inc,
		HALIDE_INC_DIR,
	],
	dependencies:[
		halide,
		curses
	])
ctlib_dep = declare_dependency(
	include_directories: inc,
	link_with: ctlib)
subdir('test')
