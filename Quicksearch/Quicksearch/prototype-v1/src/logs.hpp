#pragma once

#include <memory>
#include <spdlog/common.h>
#include <spdlog/logger.h>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/basic_file_sink.h>

std::shared_ptr<spdlog::logger> initLog();
void LOGINFO(std::shared_ptr<spdlog::logger> FILE_LOGS, std::string msg);
void LOGERROR(std::shared_ptr<spdlog::logger> FILE_LOGS, std::string msg);
void LOGWARNING(std::shared_ptr<spdlog::logger> FILE_LOGS, std::string msg);
void LOGFATAL(std::shared_ptr<spdlog::logger> FILE_LOGS, std::string msg);