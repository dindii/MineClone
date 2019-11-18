#include "mcpch.h"
#include "Logger.h"


namespace MC {
	namespace Debug
	{
		std::string* Logger::levelLabels;

		Logger::Logger()
		{
			levelLabels = new std::string[4];

			levelLabels[0] = "TRACE";
			levelLabels[1] = "WARNING";
			levelLabels[2] = "ERROR";
			levelLabels[3] = "FATAL";
		}

		Logger::~Logger()
		{
			delete[] levelLabels;
		}

		void Logger::Log(const char* string, const Level level)
		{
			printf("%s:  %s\n", levelLabels[level].c_str(), string);
			Dispatch();
			checkFatal(level);
		}

		void Logger::Log(const int num, const Level level)
		{
			printf("%s %i\n", levelLabels[level].c_str(), num);
			Dispatch();
			checkFatal(level);
		}

		void Logger::Log(const float num, const  Level level)
		{
			printf("%s %f\n", levelLabels[level].c_str(), num);
			Dispatch();
			checkFatal(level);
		}

		void Logger::Log(std::string string, const Level level)
		{
			printf("%s:  %s\n", levelLabels[level].c_str(), string.c_str());
			Dispatch();
			checkFatal(level);
		}

		void Logger::Log(Event& event, const Level level)
		{
			printf("%s:  %s\n", levelLabels[level].c_str(), event.ToString().c_str());
			Dispatch();
			checkFatal(level);
		}

		void Logger::Log(const char* string, const char* message, const Level level)
		{
			printf("%s: %s %s\n", levelLabels[level].c_str(), string, message);
			Dispatch();
			checkFatal(level);
		}

		//Since the main purpose of this log it's human interaction, i will be flushing in every message.
		void Logger::Dispatch()
		{
			fflush(stdout);
		}

		void Logger::checkFatal(const Level& level)
		{
			if (level == Level::MCFATAL)
				MC_ASSERT(false);
		}
	}
}