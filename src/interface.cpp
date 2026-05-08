#include "interface.h"

#include <nlohmann/json.hpp>

namespace interface {

    void app::run(const std::string& json_query) {
        try
        {
            getLogger().info("Received JSON query: {}", json_query);
            app::makeTask(json_query);
            app::makeCalculate();
            app::printResult();
        }
        catch(const std::exception& e)
        {
            getLogger().error("An error occurred: {}", e.what());
        }

        return;
    }

    void app::makeTask(const std::string& json_query) {
        if( json_query.empty() ) {
            throw std::runtime_error("Error: empty JSON query! Try to provide JSON query as a command line argument, e.g. './calculator '{\"num1\": 5, \"num2\": 3, \"op\": \"x\"}'");
        }

        nlohmann::json input;

        try {
            getLogger().info("Parsing JSON query...");
            input = nlohmann::json::parse(json_query);
        }
        catch (const nlohmann::json::parse_error& e) {
            getLogger().error("Failed to parse JSON query: {}", e.what());
            throw std::runtime_error(std::string("Error: invalid JSON format - ") + e.what());
        }

        if (!input.contains("op")) {
            getLogger().error("Missing required field 'op'");
            throw std::runtime_error("Error: missing required field 'op'");
        }

        std::string op = input["op"].get<std::string>();
        task.operator_ = op;

        if (op == "!") {
            if (!input.contains("num1")) {
                getLogger().error("Missing required field 'num1' for factorial");
                throw std::runtime_error("Error: missing required field 'num1' for factorial");
            }
            task.num1 = input["num1"].get<int>();
            task.status = 0;
            getLogger().info("Task created: {} {}", task.num1, task.operator_);
            return;
        }

        if (!input.contains("num1") || !input.contains("num2")) {
            getLogger().error("Missing required fields 'num1' and/or 'num2'");
            throw std::runtime_error("Error: missing required fields 'num1' and/or 'num2'");
        }

        task.num1 = input["num1"].get<int>();
        task.num2 = input["num2"].get<int>();
        task.status = 0;

        getLogger().info("Task created: {} {} {}", task.num1, task.operator_, task.num2);
        return;
    }

    void app::makeCalculate() {
        if (task.status != 0 || task.operator_.empty()) {
            getLogger().error("Cannot do calculating! Task is not created successfully.");
            throw std::runtime_error("Error: cannot do calculating! Task is not created successfully.");
        }

        getLogger().info("Performing calculation...");

        switch (task.operator_[0]) {
            case '+':
                task.result = math::add(task.num1, task.num2);
                break;
            case '-':
                task.result = math::subtract(task.num1, task.num2);
                break;
            case 'x':
                task.result = math::multiply(task.num1, task.num2);
                break;
            case '/':
                task.result = math::divide(task.num1, task.num2);
                break;
            case '^':
                task.result = math::pow(task.num1, task.num2);
                break;
            case '!':
                task.result = math::factorial(task.num1);
                break;
            default:
                throw std::runtime_error("Error: cannot do calculating! Unexpected operator: " + task.operator_);
                task.status = 1;
                return;
        }

        task.status = 0;
        getLogger().info("Calculation completed successfully.");

        return;
    }

    void app::printResult() {
        if (task.operator_.empty()) {
            getLogger().error("Cannot print result! Task is not created successfully.");
            throw std::runtime_error("Error: cannot print result! Task is not created successfully.");
            return;
        }

        if (task.status == 0) {
            if (task.operator_.compare("!") == 0) {
                getLogger().info("Result: {} {} = {}", task.num1, task.operator_, task.result);
                return;
            }
            getLogger().info("Result: {} {} {} = {}", task.num1, task.operator_, task.num2, task.result);
        } else {
            getLogger().error("Cannot print result! Task is not calculated successfully.");
            throw std::runtime_error("Error: cannot print result! Task is not calculated successfully.");
        }

        return;
    }

}  // namespace interface