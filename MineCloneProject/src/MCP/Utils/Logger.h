#pragma once
#include <string>



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
				TRACE = 0,
				WARNING,
				ERROR,
				FATAL,
			};

			Logger();
			~Logger();

			static void Log(const char* string, const Level level);
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

#define MC_ASSERT(x) if(!x) __debugbreak()

#ifdef  MC_DEBUG
#define MC_LOG_TRACE(...) MC::Debug::Logger::Log(__VA_ARGS__, MC::Debug::Logger::Level::TRACE);
#define MC_LOG_WARNING(...) MC::Debug::Logger::Log(__VA_ARGS__,  MC::Debug::Logger::Level::WARNING);
#define MC_LOG_ERROR(...)  MC::Debug::Logger::Log(__VA_ARGS__,  MC::Debug::Logger::Level::ERROR);
#define MC_LOG_FATAL(...)  MC::Debug::Logger::Log(__VA_ARGS__,  MC::Debug::Logger::Level::FATAL);

#else
#define MC_LOG_TRACE(...) 
#define MC_LOG_WARNING(...)
#define MC_LOG_ERROR(...) 
#define MC_LOG_FATAL(...) 

#endif