project('app', 'c', version: '0.1', default_options: ['c_std=c17'])

debug_defs = [
  '-DDEBUG=1'
]

debug_args = [
  '-g2',
  '-O0'
] + debug_defs

release_args = [
  '-O2'
]

build_args = [
  '-Wall',
  '-Wextra',
]

if get_option('buildtype') == 'debug'
  build_args += debug_args
else
  build_args += release_args
endif

srclist = [
  'src/main.c'
]

inc_dirs = include_directories(
  'src'
)

threads_dep = dependency('threads')
dependencies = [threads_dep]

executable('app',
  srclist,
  c_args: build_args,
  include_directories: inc_dirs,
  # dependencies: dependencies
)
