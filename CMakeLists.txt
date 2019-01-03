cmake_minimum_required(VERSION 3.10)
project(clionpro1)

set(CMAKE_CXX_STANDARD 14)

#CGAL LINK
set (CGAL_LINK_LIBS libCGAL.13.0.2.dylib)

#GMP LINK
set (GMP_LINK_LIBS libgmp.10.dylib)

#MPFR LINK
set (MPFR_LINK_LIBS libmpfr.6.dylib)

#GLFW LINK
set (GLFW_LINK_LIBS libglfw.3.2.dylib)

link_directories(
        /usr/local/Cellar/cgal/4.13/lib/
        /usr/local/Cellar/mpfr/4.0.1/lib/
        /usr/local/Cellar/gmp/6.1.2_2/lib/
        /usr/local/Cellar/glfw/3.2.1/lib/
)

include_directories(include)

file(GLOB SOURCES "src/*")

add_executable(clionpro1 ${SOURCES})

target_link_libraries(clionpro1 ${CGAL_LINK_LIBS} ${GMP_LINK_LIBS} ${MPFR_LINK_LIBS} ${GLFW_LINK_LIBS} ${CMAKE_DL_LIBS})