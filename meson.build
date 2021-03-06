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
# generate code for all backends
gen_name = 'back_projection_generic'
gen_target = custom_target(
	gen_name+'_oh',
	output : [gen_name+'.o', gen_name+'.h'],
	command : [
		gengen,
		'-g', 'back_projection',
		'-f', gen_name,
		'-e', 'o,h',
		'-o', meson.current_build_dir(),
		'target=host'
	])
cpu_name = 'back_projection_cpu'
cpu_target = custom_target(
	cpu_name+'_oh',
	output : [cpu_name+'.o', cpu_name+'.h'],
	command : [
		gengen,
		'-g', 'back_projection',
		'-f', cpu_name,
		'-e', 'o,h',
		'-o', meson.current_build_dir(),
		'backend=cpu',
		'target=host'
	])
runtime_target = custom_target(
	'halide_runtime',
	output : ['halide_runtime_x86.o'],
	command : [
		gengen,
		'-r', 'halide_runtime_x86',
		'-e', 'o',
		'-o', meson.current_build_dir(),
		'target=host'
	])
ct_lib = static_library(
	'ct',
	[gen_target, cpu_target, runtime_target])
ctlib_dep = declare_dependency(
	link_with: ct_lib,
	sources: [gen_target, cpu_target]
	)
subdir('test')
