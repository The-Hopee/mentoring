cmake_minimum_required(VERSION 3.10)

project(static_library)

add_library(lib STATIC # добавляем статическую библиотеку и указываем файлы которые в ней будут. STATIC - это тип библиотеки, который говорит о том что мы хотим создать статическую библиотеку. Аналог символа -c в командной строке
    sum.cpp
    sum.h
)