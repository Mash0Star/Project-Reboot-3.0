#pragma once

#include <iostream>
#include <format>

// #define Log(...) std::cout << std::format(__VA_ARGS__) << '\n';

#include <vector>
#include <spdlog/spdlog.h>

#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <filesystem>

// #define ENABLE_SPD_LOG

static inline std::vector<spdlog::sink_ptr> sinks;

enum ELogLevel : uint8_t
{
    Trace,
    Debug,
    Info,
    Warning,
    Error,
    Critical,
    Disabled,
    All = Trace
};

inline void MakeLogger(const std::string& LoggerName)
{
    auto logger = std::make_shared<spdlog::logger>(LoggerName, sinks.begin(), sinks.end());
    spdlog::register_logger(logger);

    logger->set_level(spdlog::level::level_enum::info);
    logger->flush_on(spdlog::level::level_enum::info);
}

inline void InitLogger()
{
    // FreeConsole();
    // AttachConsole(ATTACH_PARENT_PROCESS);

    FILE* stream = nullptr;

    bool bStopFortniteOutput = false;

    if (bStopFortniteOutput)
    {
        AllocConsole();

        freopen_s(&stream, "in.txt", "r", stdin);
        freopen_s(&stream, "out.txt", "w+", stdout);
        freopen_s(&stream, "err.txt", "w", stderr);
    }

    SetConsoleTitleA("Project Reboot 3.0");
    
#ifdef ENABLE_SPD_LOG

    std::string logName = "reboot.log"; // GenerateLogFileName();

    sinks.emplace_back(std::make_shared<spdlog::sinks::stdout_color_sink_mt>())->set_pattern("[%D-%T] %n: %^%v%$");
    sinks.emplace_back(std::make_shared<spdlog::sinks::basic_file_sink_mt>(logName, true))->set_pattern("[%D-%T] %n: %l: %v");

    MakeLogger("LogTeams");
    MakeLogger("LogMemory");
    MakeLogger("LogFinder");
    MakeLogger("LogInit");
    MakeLogger("LogNet");
    MakeLogger("LogDev");
    MakeLogger("LogPlayer");
    MakeLogger("LogLoot");
    MakeLogger("LogMinigame");
    MakeLogger("LogLoading");
    MakeLogger("LogHook");
    MakeLogger("LogAbilities");
    MakeLogger("LogEvent");
    MakeLogger("LogPlaylist");
    MakeLogger("LogGame");
    MakeLogger("LogAI");
    MakeLogger("LogInteraction");
    MakeLogger("LogCreative");
    MakeLogger("LogZone");
    MakeLogger("LogReplication");
    MakeLogger("LogMutator");
    MakeLogger("LogVehicles");
    MakeLogger("LogUI");
    MakeLogger("LogBots");
    MakeLogger("LogCosmetics");
    MakeLogger("LogMatchmaker");
    MakeLogger("LogRebooting");
    MakeLogger("LogObjectViewer");
    MakeLogger("LogLateGame");
#endif
}

#ifdef ENABLE_SPD_LOG
#define LOG_DEBUG(loggerName, ...)                                            \
    if (spdlog::get(#loggerName))          \
        spdlog::get(#loggerName)->debug(std::format(__VA_ARGS__));
#define LOG_INFO(loggerName, ...)                                            \
    if (spdlog::get(#loggerName))         \
        spdlog::get(#loggerName)->info(std::format(__VA_ARGS__));
#define LOG_WARN(loggerName, ...)                                            \
    if (spdlog::get(#loggerName))         \
        spdlog::get(#loggerName)->warn(std::format(__VA_ARGS__));
#define LOG_ERROR(loggerName, ...)                                            \
    if (spdlog::get(#loggerName))          \
        spdlog::get(#loggerName)->error(std::format(__VA_ARGS__));
#define LOG_FATAL(loggerName, ...)                                               \
    if (spdlog::get(#loggerName))             \
        spdlog::get(#loggerName)->critical(std::format(__VA_ARGS__));
#else
#pragma warning( disable : 4390 ) // cuz then it will produce if (blahblah) ;
#define LOG_DEBUG(loggerName, ...)
#define LOG_INFO(loggerName, ...)
#define LOG_WARN(loggerName, ...)
#define LOG_ERROR(loggerName, ...)
#define LOG_FATAL(loggerName, ...)
#endif