cmake_minimum_required(VERSION 3.10)
project(calculator)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)

FetchContent_Declare(
    math
    GIT_REPOSITORY https://github.com/The-Hopee/math_lib.git
    GIT_TAG main
)

FetchContent_Declare( 
    json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG v3.11.3
)


FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.14.0
)

FetchContent_Declare(
    spdlog
    GIT_REPOSITORY https://github.com/gabime/spdlog.git
    GIT_TAG v1.13.0
)

FetchContent_MakeAvailable(math json googletest spdlog)

add_executable(calculator
                main.cpp
                src/interface.cpp)

target_include_directories(
    calculator
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/tools
)

target_link_libraries(calculator
                    PRIVATE
                    math
                    nlohmann_json::nlohmann_json
                    spdlog::spdlog
)

enable_testing()

add_executable(calculator_test
    tests/test_calculator.cpp
    src/interface.cpp
)

target_include_directories(
    calculator_test
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/tools
)

target_link_libraries(calculator_test PRIVATE 
    math 
    nlohmann_json::nlohmann_json 
    spdlog::spdlog 
    gtest_main
)

include(GoogleTest)
gtest_discover_tests(calculator_test)

# clang-format target
add_custom_target(format
    COMMAND clang-format -i -style=file main.cpp src/interface.cpp include/interface.h
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

# clang-tidy target
add_custom_target(tidy
    COMMAND clang-tidy -p ${CMAKE_BINARY_DIR} -extra-arg=-I${CMAKE_CURRENT_SOURCE_DIR}/include -extra-arg=-I${CMAKE_CURRENT_SOURCE_DIR}/math_lib -extra-arg=-I${CMAKE_CURRENT_SOURCE_DIR}/json/include main.cpp src/interface.cpp
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    DEPENDS calculator
)
