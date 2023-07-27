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

link_args = [
  '-lgcc',
  '-nostdlib',
  '-nostartfiles',
]

if get_option('buildtype') == 'debug'
  build_args += debug_args
else
  build_args += release_args
endif

asm_sources = [
  'src/asm/startup.s'
]

c_sources = [
  'src/main.c'
]

srcs = asm_sources + c_sources

inc_dirs = include_directories(
  'src'
)

executable('app',
  srcs,
  c_args: build_args,
  link_args: link_args,
  include_directories: inc_dirs
)
