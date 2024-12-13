cmake_minimum_required(VERSION 3.29)
project(ProjetoGitIIa C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(ProjetoGitIIa
    algoritmo.c
    algoritmo.h
    funcao.c
    funcao.h
    main.c
    utils.c
    utils.h
        algoritmo_evolutivo.c
        algoritmo_evolutivo.h)
