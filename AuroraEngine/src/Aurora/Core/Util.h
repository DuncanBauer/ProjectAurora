// Aurora Engine Library
// Header file

// For more information visit: https://github.com/DuncanBauer/ProjectAurora#table-of-contents

// Developed by Duncan Bauer and every direct or indirect contributors to the GitHub.
// LICENSING INFORMATION

// It is recommended that you don't modify any source code! It will become difficult for you to update the library.
// Note that 'Aurora::' being a namespace, you can add functions into the namespace from your own source files, without
// modifying Util.h or Util.cpp. Discussing your changes on the GitHub Issue Tracker may lead you
// to a better solution or official support for them.

// Index of this file:
// CODE
//   - [SECTION] PREPROCESSOR DIRECTIVES
//   - [SECTION] INCLUDES
//   - [SECTION] FORWARD DECLARATIONS
//   - [SECTION] TYPENAMES
//   - [SECTION] CONSTANTS
//   - [SECTION] ENUMS
//   - [SECTION] CLASSES
//   - [SECTION] STRUCTS
//   - [SECTION] FUNCTIONS
//   - [SECTION] MACROS

#pragma once

/************************************************************************************
* [SECTION] PREPROCESSOR DIRECTIVES
************************************************************************************/
#pragma region Preprocessor
// Library Version
// (Integer encoded as XYYZZ for use in #if preprocessor conditionals, e.g. '#if IMGUI_VERSION_NUM > 12345')
#define AURORA_UTIL_VERSION     "0.0.1 ALPHA"
#define AURORA_UTIL_VERSION_NUM 00001
#pragma endregion

/************************************************************************************
* [SECTION] INCLUDES
************************************************************************************/
#pragma region Includes
// Project Specific Headers
#include "Core.h"

// C++ Standard Library Headers

// Third Party Library Headers
// SPDLog
#pragma warning(push)
#pragma warning(disable: 26451)
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>
#pragma endregion
#pragma warning(pop)

namespace Aurora
{
/************************************************************************************
* [SECTION] FORWARD DECLARATIONS
************************************************************************************/
#pragma region Forward Declaration
#pragma endregion

/************************************************************************************
* [SECTION] TYPENAMES
************************************************************************************/
#pragma region Typenames
#pragma endregion

/************************************************************************************
* [SECTION] CONSTANTS
************************************************************************************/
#pragma region Constants
#pragma endregion

/************************************************************************************
* [SECTION] ENUMS
************************************************************************************/
#pragma region Enums
#pragma endregion

/************************************************************************************
* [SECTION] STRUCTS
************************************************************************************/
#pragma region Structs
#pragma endregion

/************************************************************************************
* [SECTION] CLASSES
************************************************************************************/
#pragma region Classes
    /********************************************************************************
    * [CLASS] Time
    *********************************************************************************
    * The Time class provides static methods to obtain the current time since the UNIX
    * epoch in both seconds and milliseconds.
    ********************************************************************************/
    class AURORA_ENGINE_API Time
    {
      public:
        static inline long long GetTimeSeconds()
        {
          std::chrono::seconds s = std::chrono::duration_cast<std::chrono::seconds>(
            std::chrono::system_clock::now().time_since_epoch());
          return s.count();
        }

        static inline long long GetTimeMilliseconds()
        {
          std::chrono::milliseconds ms = std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::system_clock::now().time_since_epoch());
          return ms.count();
        }
    };

    /********************************************************************************
    * [CLASS] DeltaTime
    *********************************************************************************
    * The DeltaTime class represents a duration of time, with methods for obtaining
    * the duration in seconds or milliseconds, converting it to a string, and assigning
    * a value to it. The duration is stored as a private member variable m_Time in
    * seconds, and can be initialized with a default value of 0.0 seconds.
    ********************************************************************************/
    class AURORA_ENGINE_API DeltaTime
    {
      public:
        DeltaTime(float _time = 0.0f) : m_Time(_time) {}
        
        operator float() const { return m_Time; }
        DeltaTime& operator=(const float& _time)
        {
          m_Time = _time;
          return *this;
        }
        
        float GetSeconds() const { return m_Time; }
        float GetMilliseconds() const { return m_Time * 1000; }
        
        std::string ToString() const 
        {
          std::stringstream ss;
          ss << std::fixed << "Delta Time: " << m_Time << std::scientific;
          return ss.str();
        }

      private:
        float m_Time;
    };

    /********************************************************************************
    * [CLASS] Log
    *********************************************************************************
    * The Log class provides a logging mechanism, with methods for initializing and
    * obtaining logger objects for different parts of an application.
    ********************************************************************************/
    class AURORA_ENGINE_API Log
    {
      public:
        static void Init()
        {
          std::vector<spdlog::sink_ptr> logSinks;
          logSinks.emplace_back(std::make_shared<spdlog::sinks::stdout_color_sink_mt>());
          logSinks.emplace_back(std::make_shared<spdlog::sinks::basic_file_sink_mt>("Aurora.log", true));

          logSinks[0]->set_pattern("%^[%T] %n: %v%$");
          logSinks[1]->set_pattern("[%T] [%l] %n: %v");

          sm_EngineLogger = std::make_shared<spdlog::logger>("AURORA", begin(logSinks), end(logSinks));
          spdlog::register_logger(sm_EngineLogger);
          sm_EngineLogger->set_level(spdlog::level::trace);
          sm_EngineLogger->flush_on(spdlog::level::trace);

          sm_ClientLogger = std::make_shared<spdlog::logger>("CLIENT", begin(logSinks), end(logSinks));
          spdlog::register_logger(sm_ClientLogger);
          sm_ClientLogger->set_level(spdlog::level::trace);
          sm_ClientLogger->flush_on(spdlog::level::trace);
        }
        
        static inline Ref<spdlog::logger>& GetEngineLogger() { return sm_EngineLogger; }
        static inline Ref<spdlog::logger>& GetClientLogger() { return sm_ClientLogger; }

      private:
        static Ref<spdlog::logger> sm_EngineLogger;
        static Ref<spdlog::logger> sm_ClientLogger;
    };
#pragma endregion

/************************************************************************************
* [SECTION] FUNCTIONS
************************************************************************************/
#pragma region Functions
#pragma endregion

/************************************************************************************
* [SECTION] MACROS
************************************************************************************/
#pragma region Macros

#ifdef PA_DEBUG
  // SPDLog Macros for the Project Aurora Engine Library
  #define PA_ENGINE_INFO(...)     ::Aurora::Log::GetEngineLogger()->info(__VA_ARGS__)
  #define PA_ENGINE_TRACE(...)    ::Aurora::Log::GetEngineLogger()->trace(__VA_ARGS__)
  #define PA_ENGINE_WARN(...)     ::Aurora::Log::GetEngineLogger()->warn(__VA_ARGS__)
  #define PA_ENGINE_ERROR(...)    ::Aurora::Log::GetEngineLogger()->error(__VA_ARGS__)
  #define PA_ENGINE_CRITICAL(...) ::Aurora::Log::GetEngineLogger()->critical(__VA_ARGS__)

  // SPDLog Macros for projects made with the Project Aurora Libraries 
  #define PA_CLIENT_INFO(...)     ::Aurora::Log::GetClientLogger()->info(__VA_ARGS__)
  #define PA_CLIENT_TRACE(...)    ::Aurora::Log::GetClientLogger()->trace(__VA_ARGS__)
  #define PA_CLIENT_WARN(...)     ::Aurora::Log::GetClientLogger()->warn(__VA_ARGS__)
  #define PA_CLIENT_ERROR(...)    ::Aurora::Log::GetClientLogger()->error(__VA_ARGS__)
  #define PA_CLIENT_CRITICAL(...) ::Aurora::Log::GetClientLogger()->critical(__VA_ARGS__)
#else
  // SPDLog Macros for the Project Aurora Engine Library
  #define PA_ENGINE_INFO(...)
  #define PA_ENGINE_TRACE(...)
  #define PA_ENGINE_WARN(...)
  #define PA_ENGINE_ERROR(...)
  #define PA_ENGINE_CRITICAL(...)

  // SPDLog Macros for projects made with the Project Aurora Libraries 
  #define PA_CLIENT_INFO(...)
  #define PA_CLIENT_TRACE(...)
  #define PA_CLIENT_WARN(...)
  #define PA_CLIENT_ERROR(...)
  #define PA_CLIENT_CRITICAL(...) 
#endif

#pragma endregion
}
