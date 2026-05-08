cmake_minimum_required(VERSION 3.10)

project(dynamic_library)

add_library(lib SHARED # добавляем динамическую библиотеку и указываем файлы которые в ней будут. SHARED - это тип библиотеки, который говорит о том что мы хотим создать динамическую библиотеку. Аналог символа -fPIC в командной строке
    sum.cpp
    sum.h
) # тк у меня имя цели lib то в итоге будет создана библиотека с именем liblib.so (на Linux) или liblib.dll (на Windows). Если бы я указал другое имя цели, например mylib, то в итоге была бы создана библиотека с именем libmylib.so (на Linux) или mylib.dll (на Windows)