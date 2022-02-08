#pragma once

#include <stdint.h>
#include <string>
#include <fstream>

	// Палитра цветов от 0 до 15
	enum ConsoleColor
	{
		CC_Black = 0,
		CC_Blue,
		CC_Green,
		CC_Cyan,
		CC_Red,
		CC_Magenta,
		CC_Brown,
		CC_LightGray,
		CC_DarkGray,
		CC_LightBlue,
		CC_LightGreen,
		CC_LightCyan,
		CC_LightRed,
		CC_LightMagenta,
		CC_Yellow,
		CC_White
	};

	//=============================================================================================

	class ScreenSingleton
	{
	public:
		static ScreenSingleton& getInstance()
		{
			static ScreenSingleton theInstance;
			return theInstance;
		}
		void ClrScr();
		void GotoXY(double x, double y);
		uint16_t GetMaxX();
		uint16_t GetMaxY();
		void SetColor(ConsoleColor color);
	private:
		ScreenSingleton() {}
		ScreenSingleton(const ScreenSingleton& root) = delete;
		ScreenSingleton& operator=(const ScreenSingleton&) = delete;
	};

	//=============================================================================================

//Interface
	class LoggerInterface
	{
		virtual void OpenLogFile(const std::string& FN)=0;
		virtual void CloseLogFile()=0;
		virtual std::string GetCurDateTime()=0;
		virtual void WriteToLog(const std::string& str)=0;
		virtual void WriteToLog(const std::string& str, int n)=0;
		virtual void WriteToLog(const std::string& str, double d)=0;
		
	};

	//Singletone
	class FileLoggerSingleton : public LoggerInterface
	{
	public:
		static FileLoggerSingleton& getInstance()
		{
			static FileLoggerSingleton theInstance;
			return theInstance;
		}
		void OpenLogFile(const std::string& FN)override;
		void CloseLogFile()override;
		std::string GetCurDateTime()override;
		void WriteToLog(const std::string& str)override;
		void WriteToLog(const std::string& str, int n)override;
		void WriteToLog(const std::string& str, double d)override;

	private:
		std::ofstream logOut;

		FileLoggerSingleton(){}
		FileLoggerSingleton(const FileLoggerSingleton& root) = delete;
		const FileLoggerSingleton& operator=(const FileLoggerSingleton&) = delete;
	};

//Proxy
	class LoggerSingleton : public LoggerInterface
	{
	public:
		static LoggerSingleton& getInstance()
		{
			static LoggerSingleton theInstance;
			return theInstance;
		}
		void OpenLogFile(const std::string& FN) override;
		void CloseLogFile()override;
		std::string GetCurDateTime()override;
		void WriteToLog(const std::string& str)override;
		void WriteToLog(const std::string& str, int n)override;
		void WriteToLog(const std::string& str, double d)override;
	private: 
		uint32_t loggerEventNum;

		LoggerSingleton() :loggerEventNum(1) {}
		LoggerSingleton(const LoggerSingleton& root) = delete;
		const LoggerSingleton& operator=(const LoggerSingleton&) = delete;
	};

	//=============================================================================================