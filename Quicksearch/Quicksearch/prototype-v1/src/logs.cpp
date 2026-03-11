#include "logs.hpp"

std::shared_ptr<spdlog::logger> initLog() {
    try {
        auto FILE_LOGS = spdlog::basic_logger_mt("file-log", "./tmp/logs.txt");
        FILE_LOGS->flush_on(spdlog::level::info);
        return FILE_LOGS;

    } catch (spdlog::spdlog_ex &error) {
        spdlog::error("Failed to initialize logger file(logs.txt)");
        return nullptr;
    }
}

void LOGINFO(std::shared_ptr<spdlog::logger> FILE_LOGS, std::string msg) {
    FILE_LOGS -> info(msg);
    spdlog::info(msg);
}


void LOGERROR(std::shared_ptr<spdlog::logger> FILE_LOGS, std::string msg) {
    FILE_LOGS -> error(msg);
    spdlog::error(msg);
}


void LOGWARNING(std::shared_ptr<spdlog::logger> FILE_LOGS, std::string msg) {
    FILE_LOGS -> warn(msg);
    spdlog::warn(msg);
}


void LOGFATAL(std::shared_ptr<spdlog::logger> FILE_LOGS, std::string msg) {
    FILE_LOGS -> critical(msg);
    spdlog::critical(msg);
}