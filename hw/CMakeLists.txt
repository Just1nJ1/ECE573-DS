cmake_minimum_required(VERSION 3.24)
project(01_Complexity)
project(02_DynArray)
project(02_DynArray_extra)
project(03_LinkedList)

set(CMAKE_CXX_STANDARD 14)

add_compile_definitions(DEBUG)

add_executable(01_Complexity 01_Complexity/intersectingboxes.cpp)
add_executable(02_DynArray 02_DynArray/HWDynArray.cc)
add_executable(02_DynArray_extra 02_DynArray/HWCircularBuffer.cpp)
add_executable(03_LinkedList 03_LinkedList/hwDoubleLinkedList.cc)
