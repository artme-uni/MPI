cmake_minimum_required(VERSION 3.15)
project(MPI)

SET(CMAKE_C_COMPILER /usr//local/bin/mpicc)
SET(CMAKE_CXX_COMPILER /usr//local/bin/mpic++)

include_directories(/usr/local/opt/open-mpi/include)
link_directories(/usr/local/opt/open-mpi/lib)

add_executable(MPI main.cpp Matrix/Matrix.cpp Matrix/Matrix.h Matrix/Column.cpp Matrix/Column.h Sole.cpp Sole.h Scan/Scaner.cpp Scan/Scaner.h)

target_link_libraries (MPI mpi)