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
prefix = get_option('prefix')
inc = include_directories('include')
cc = meson.get_compiler('cpp')
curses = cc.find_library('libcurses')
halide = declare_dependency(
	include_directories: join_paths(prefix, get_option('includedir')),
	dependencies: cc.find_library(
		'libHalide',
		dirs:[join_paths(prefix, get_option('bindir'))
	]),
)
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
	],
	dependencies:[
		halide,
		curses
	])
ctlib_dep = declare_dependency(
	include_directories: inc,
	link_with: ctlib)
subdir('test')
