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
basic_target_h = custom_target(
	ct_name+'_h',
	output : ct_name+'.h',
	command : [
		gengen,
		'-g', 'back_projection',
		'-f', ct_name,
		'-e', 'h',
		'-o', meson.current_build_dir(),
		'target=host-x86-64'
	])
basic_target_o = custom_target(
	ct_name+'_o',
	output : ct_name+'.o',
	command : [
		gengen,
		'-g', 'back_projection',
		'-f', ct_name,
		'-e', 'o',
		'-o', meson.current_build_dir(),
		'target=host-x86-64'
	])
runtime_target = custom_target(
	'halide_runtime',
	output : ['halide_runtime_x86.o'],
	command : [
		gengen,
		'-r', 'halide_runtime_x86',
		'-e', 'o',
		'-o', meson.current_build_dir(),
		'target=host-x86-64'
	])
ct_lib = static_library(
	'ct',
	[basic_target_o, runtime_target])
ctlib_dep = declare_dependency(
	link_with: ct_lib,
	sources: [basic_target_h]
	)
subdir('test')
