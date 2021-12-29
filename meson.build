project('atomic_sand', 'c', default_options : ['c_std=c18'])

cmake = import('cmake')

# Configure the CMake project
sdl2_dep = dependency('sdl2')


subdir('src')

executable('run_atomic_sand', all_files, dependencies: [sdl2_dep])