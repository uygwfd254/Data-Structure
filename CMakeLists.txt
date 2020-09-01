cmake_minimum_required( VERSION 3.0 )

project( data-structure )

# flags

# includes
include_directories( ./include ./src/linked_list)


# target
add_executable( binary ./src/linked_list/single_linkedlist.cpp ./src/main/single_linkedlist_ex.cpp ./src/data_structure.cpp )

# 3rd party lib
