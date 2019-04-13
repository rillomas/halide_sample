sources = [
	'test.cpp',
]
gtest = dependency('gtest_main')
opencv = dependency('opencv')
dl = cc.find_library('libdl')
executable('test_halide',
	sources,
	cpp_args:[
		'-Wno-missing-field-initializers',
	],
	include_directories:[
		halide_incdir
	],
	dependencies:[
		opencv,
		gtest,
		ctlib_dep,
		dl
	])
