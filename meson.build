project(
	'halide_sample',
	'cpp',
	default_options:[
		'cpp_std=c++11',
		'warning_level=2'
	])
sources = [
	'back_projection.cpp',
	'GenGen.cpp',
]
prefix = get_option('prefix')
cc = meson.get_compiler('cpp')
curses = cc.find_library('libcurses')
halide_incdir = join_paths(prefix, get_option('includedir'))
halide = declare_dependency(
	include_directories: halide_incdir,
	dependencies: cc.find_library(
		'libHalide',
		dirs:[join_paths(prefix, get_option('bindir'))
	]),
)
gengen = executable(
	'generator',
	sources,
	# cpp_args is currently used to suppress Halide's
	# compiler warnings.
	cpp_args:[
		'-Wno-unused-parameter',
		'-Wno-missing-field-initializers',
	],
	dependencies:[
		halide,
		curses
	])

ct_name = 'back_projection_basic'
ct_dir = '.'
ct_target = custom_target(
	ct_name+'[ah]',
	output : [ct_name+'.a', ct_name+'.h'],
	command : [
		gengen,
		'-g', 'back_projection',
		'-f', ct_name,
		'-o', ct_dir,
		'target=host-x86-64'
	])
ctlib_dep = declare_dependency(
	sources: ct_target,
)
subdir('test')
