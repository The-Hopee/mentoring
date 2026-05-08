#pragma once
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <memory>

inline spdlog::logger& getLogger() {
    static auto logger = spdlog::stdout_color_mt("calculator", spdlog::color_mode::automatic);
    return *logger;
}