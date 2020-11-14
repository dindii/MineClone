#pragma once
#include <string>
#include "MCP/Core.h"
#include <sstream>
#include <iostream>

/*      @ TODO:
* Mutex if needed.
*/

/*  
* Not the fastest but should do the job if great flexibility. It is meant to be used only for debugging mode and can be easily extended with operator<< overload.
*/

namespace MC {
	namespace Debug
	{
		struct Logger
		{
			enum Level : uint8_t
			{
				MCTRACE = 0,
				MCWARNING,
				MCERROR,
				MCFATAL,
			};

			Logger()
			{
				levelLabels[0] = "TRACE";
				levelLabels[1] = "WARNING";
				levelLabels[2] = "ERROR";
				levelLabels[3] = "FATAL";
			}
			~Logger() = default;

			template<typename ... Args>
			inline static void Log(Level level, Args&& ... args)
			{
				oss << levelLabels[level] << ": ";
				(oss << ... << std::forward<Args>(args)) << '\n';
				
				checkFatal(level);
			}
			
			inline static void Flush()
			{
				//Avoiding to use str with no purpose (which uses a considerable chunk of memory)
				oss.seekp(0, std::ios::end);
				uint32_t size = (uint32_t)oss.tellp();
				
				if (size > 0)
				{
					std::cout << oss.str();
					
					//Clears stream
					oss.str("");
				}
			}
		private:
			inline static void checkFatal(const Level& level)
			{
				if (level == Level::MCFATAL)
				{
					Flush();
					MC_ASSERT(false);
				}
			}

		private:
			static std::string levelLabels[4];
			static std::ostringstream oss;
		};
	}
}


#ifdef  MC_DEBUG
#define MC_LOG_TRACE(...)   MC::Debug::Logger::Log(MC::Debug::Logger::Level::MCTRACE  ,                                 __VA_ARGS__)
#define MC_LOG_WARNING(...) MC::Debug::Logger::Log(MC::Debug::Logger::Level::MCWARNING, __LINE__, " ", __FILE__, " - ", __VA_ARGS__)
#define MC_LOG_ERROR(...)   MC::Debug::Logger::Log(MC::Debug::Logger::Level::MCERROR  , __LINE__, " ", __FILE__, " - ", __VA_ARGS__)
#define MC_LOG_FATAL(...)   MC::Debug::Logger::Log(MC::Debug::Logger::Level::MCFATAL  , __LINE__, " ", __FILE__, " - ", __VA_ARGS__)

#else
#define MC_LOG_TRACE(...) 
#define MC_LOG_WARNING(...)
#define MC_LOG_ERROR(...) 
#define MC_LOG_FATAL(...) 

#endif


