#pragma once
#include <string>
#include "MCP/Event/Event.h"


/*      @ TODO:
* Mutex if needed.
* Add all classes of the engine
*/

namespace MC {
	namespace Debug
	{
		struct Logger
		{
			enum Level
			{
				MCTRACE = 0,
				MCWARNING,
				MCERROR,
				MCFATAL,
			};

			Logger();
			~Logger();

			static void Log(Event& event, const Level level);
			static void Log(const char* string, const Level level);
			static void Log(const char* string, const char* message, const Level level);
			static void Log(std::string string, const Level level);
			static void Log(const int num, const Level level);
			static void Log(const float num, const Level level);

		private:
			static void Dispatch();
			static void checkFatal(const Level& level);
		private:
			static std::string* levelLabels;
		};
	}
}


#ifdef  MC_DEBUG
#define MC_LOG_TRACE(...)   MC::Debug::Logger::Log(__VA_ARGS__,  MC::Debug::Logger::Level::MCTRACE)
#define MC_LOG_WARNING(...) MC::Debug::Logger::Log(__VA_ARGS__,  MC::Debug::Logger::Level::MCWARNING)
#define MC_LOG_ERROR(...)   MC::Debug::Logger::Log(__VA_ARGS__,  MC::Debug::Logger::Level::MCERROR)
#define MC_LOG_FATAL(...)   MC::Debug::Logger::Log(__VA_ARGS__,  MC::Debug::Logger::Level::MCFATAL)

#else
#define MC_LOG_TRACE(...) 
#define MC_LOG_WARNING(...)
#define MC_LOG_ERROR(...) 
#define MC_LOG_FATAL(...) 

#endif

#define MC_ASSERT(x) if(!x)  __debugbreak()