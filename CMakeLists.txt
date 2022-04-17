cmake_minimum_required(VERSION 3.8.2)
project(simple-c-compiler VERSION 1.0)

add_library(
    lexer_aux
    src/lexer_aux.c 
    src/lexer_aux.h)

add_executable(
    lexer 
    src/lexer.c 
    src/lexer.h
    )

target_link_libraries(lexer PRIVATE lexer_aux)