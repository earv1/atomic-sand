project('atomic_sand', 'c', default_options : ['c_std=c18'])

add_project_arguments('-g',  language : 'c')

cmake = import('cmake')

# Configure the CMake project
sdl2_dep = dependency('sdl2')


subdir('src')

dir_base = meson.current_source_dir()
dir_include = join_paths(dir_base, 'include')

executable('run_atomic_sand', all_files, dependencies: [sdl2_dep])