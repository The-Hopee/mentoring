cmake_minimum_required(VERSION 3.10)

project(static_library_usage)

add_subdirectory(lib) # добавляем поддиректорию с библиотекой где есть CMakeLists.txt

add_executable( static_library_usage
                main.cpp) # добавляем исполняемый файл

target_link_libraries(static_library_usage # линкуем его с нашей библиотекой ( аналог символа -L в командной строке)
                    PRIVATE
                    lib # указываем путь к нашей статической библиотеке ( аналог символа -l в командной строке, но с указанием пути)
)

target_include_directories(static_library_usage # указываем директории для того чтобы наш проект собрался (в нашем случае это папка lib, так как там лежит наш заголовочный файл)
                    PRIVATE
                    ${CMAKE_CURRENT_SOURCE_DIR}/lib # аналог символа -I в командной строке
)
