cmake_minimum_required(VERSION 3.10)
project(calculator)

include(FetchContent)

# загружаем либу с GitHub
FetchContent_Declare(
    math
    GIT_REPOSITORY https://github.com/The-Hopee/math_lib.git
    GIT_TAG main
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

# clang-format target
add_custom_target(format
    COMMAND clang-format -i -style=file main.cpp src/interface.cpp include/interface.h
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

# clang-tidy target
add_custom_target(tidy
    COMMAND clang-tidy -p ${CMAKE_BINARY_DIR} -extra-arg=-I${CMAKE_CURRENT_SOURCE_DIR}/include -extra-arg=-I${CMAKE_CURRENT_SOURCE_DIR}/math_lib main.cpp src/interface.cpp
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    DEPENDS calculator
)
