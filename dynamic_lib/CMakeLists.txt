cmake_minimum_required(VERSION 3.10)

project(dynamic_library_usage)

add_subdirectory(lib) # добавляем поддиректорию с библиотекой где есть CMakeLists.txt

add_executable( dynamic_library_usage
                main.cpp) # добавляем исполняемый файл

target_link_libraries(dynamic_library_usage # линкуем его с нашей библиотекой ( аналог символа -L в командной строке)
                    PRIVATE
                    lib # указываем путь к нашей динамической библиотеке ( аналог символа -l в командной строке, но с указанием пути)
) # тк у меня имя цели lib то в итоге будет создана библиотека с именем liblib.so (на Linux) или liblib.dll (на Windows). Если бы я указал другое имя цели, например mylib, то в итоге была бы создана библиотека с именем libmylib.so (на Linux) или mylib.dll (на Windows)

target_include_directories(dynamic_library_usage # указываем директории для того чтобы наш проект собрался (в нашем случае это папка lib, так как там лежит наш заголовочный файл)
                    PRIVATE
                    ${CMAKE_CURRENT_SOURCE_DIR}/lib # аналог символа -I в командной строке
)
