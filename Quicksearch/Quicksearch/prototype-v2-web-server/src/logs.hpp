#pragma once

#include <cstdlib>
#include <memory>
#include <spdlog/common.h>
#include <spdlog/logger.h>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/basic_file_sink.h>

// std::shared_ptr<spdlog::logger> initLog();
// void LOGINFO(std::shared_ptr<spdlog::logger> FILE_LOGS, std::string msg);
// void LOGERROR(std::shared_ptr<spdlog::logger> FILE_LOGS, std::string msg);
// void LOGWARNING(std::shared_ptr<spdlog::logger> FILE_LOGS, std::string msg);
// void LOGFATAL(std::shared_ptr<spdlog::logger> FILE_LOGS, std::string msg);


inline std::shared_ptr<spdlog::logger> initLog() {
    try {
        spdlog::set_level(spdlog::level::debug);
        auto FILE_LOGS = spdlog::basic_logger_mt("file-log", "./tmp/logs.txt");
        FILE_LOGS->flush_on(spdlog::level::info);
        return FILE_LOGS;

    } catch (spdlog::spdlog_ex &error) {
        spdlog::error("Failed to initialize logger file(logs.txt)");
        exit (EXIT_FAILURE);
    }
}


inline void LOGDEBUG(std::shared_ptr<spdlog::logger>& FILE_LOGS, std::string msg) {
    FILE_LOGS -> debug(msg);
    spdlog::debug(msg);
}

inline void LOGINFO(std::shared_ptr<spdlog::logger>& FILE_LOGS, std::string msg) {
    FILE_LOGS -> info(msg);
    spdlog::info(msg);
}


inline void LOGERROR(std::shared_ptr<spdlog::logger>& FILE_LOGS, std::string msg) {
    FILE_LOGS -> error(msg);
    spdlog::error(msg);
}


inline void LOGWARNING(std::shared_ptr<spdlog::logger>& FILE_LOGS, std::string msg) {
    FILE_LOGS -> warn(msg);
    spdlog::warn(msg);
}


inline void LOGFATAL(std::shared_ptr<spdlog::logger>& FILE_LOGS, std::string msg) {
    FILE_LOGS -> critical(msg);
    spdlog::critical(msg);
}