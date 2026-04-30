cmake_minimum_required(VERSION 3.10)
project(calculator)

include(FetchContent)

# загружаем либу из локального репозитория
FetchContent_Declare(
    math
    SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/math_lib
)

# делаем либу доступной
FetchContent_MakeAvailable(math)

add_executable(calculator
                main.cpp
                src/interface.cpp)

target_include_directories(
    calculator
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(calculator
                    PRIVATE
                    math
)
