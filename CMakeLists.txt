cmake_minimum_required(VERSION 3.28)
project(robocup)

#Add header files 
include_directories(./)

#Add list of cpp files
set (SOURCES
    prueba.cpp
    main.cpp)

# Add the executable 
add_executable(robocup ${SOURCES})

# Use C++ 17
target_compile_features(robocup PRIVATE cxx_std_17)

