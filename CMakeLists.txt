cmake_minimum_required(VERSION 3.27)
project(lab2_4 C)

set(CMAKE_C_STANDARD 11)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
add_executable(lab2_4 main.c
        Tranzactie.c
        Tranzactie.h
        MyList.c
        MyList.h
        service.c
        service.h
)
