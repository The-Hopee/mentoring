#include <gtest/gtest.h>
#include "interface.h"

TEST(CalculatorTest, Addition) {
    interface::app app;
    std::string json_query = R"({"num1": 5, "num2": 3, "op": "+"})";

    testing::internal::CaptureStdout();
    app.run(json_query);

    std::string output = testing::internal::GetCapturedStdout();
    
    EXPECT_TRUE(output.find("Result: 5 + 3 = 8") != std::string::npos);
}

TEST(CalculatorTest, Subtraction) {
    interface::app app;
    std::string json_query = R"({"num1": 5, "num2": 3, "op": "-"})";

    testing::internal::CaptureStdout();
    app.run(json_query);

    std::string output = testing::internal::GetCapturedStdout();
    
    EXPECT_TRUE(output.find("Result: 5 - 3 = 2") != std::string::npos);
}

TEST(CalculatorTest, Multiplication) {
    interface::app app;
    std::string json_query = R"({"num1": 5, "num2": 3, "op": "x"})";

    testing::internal::CaptureStdout();
    app.run(json_query);

    std::string output = testing::internal::GetCapturedStdout();
    
    EXPECT_TRUE(output.find("Result: 5 x 3 = 15") != std::string::npos); // вот эта штука нужна, чтобы проверять что тест пройден или не пройден
}

TEST(CalculatorTest, Division) {
    interface::app app;
    std::string json_query = R"({"num1": 6, "num2": 3, "op": "/"})";

    testing::internal::CaptureStdout();
    app.run(json_query);

    std::string output = testing::internal::GetCapturedStdout();
    
    EXPECT_TRUE(output.find("Result: 6 / 3 = 2") != std::string::npos);
}

TEST(CalculatorTest, Pow) {
    interface::app app;
    std::string json_query = R"({"num1": 5, "num2": 3, "op": "^"})";

    testing::internal::CaptureStdout();
    app.run(json_query);

    std::string output = testing::internal::GetCapturedStdout();
    
    EXPECT_TRUE(output.find("Result: 5 ^ 3 = 125") != std::string::npos);
}

TEST(CalculatorTest, Factorial) {
    interface::app app;
    std::string json_query = R"({"num1": 5, "op": "!"})";

    testing::internal::CaptureStdout();
    app.run(json_query);

    std::string output = testing::internal::GetCapturedStdout();
    
    EXPECT_TRUE(output.find("Result: 5 ! = 120") != std::string::npos);
}