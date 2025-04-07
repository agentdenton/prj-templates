project(
  'app',
  'cpp',
  version: '0.0.1',
  license: 'MIT',
  default_options: ['cpp_std=c++23']
)

deps = [
  dependency('fmt'),
  dependency('spdlog')
]

srcs = [
  'src/main.cpp',
]

executable(
  'app',
  srcs,
  dependencies: deps,
)
