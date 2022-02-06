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

//Proxy
	class LoggerSingletone : public LoggerInterface
	{
	public:
		
		static LoggerSingletone& getInstance()
		{
			static LoggerSingletone theInstance;
			return theInstance;
		}
		void OpenLogFile(const std::string& FN);
		void CloseLogFile();
		std::string GetCurDateTime();
		void WriteToLog(const std::string& str);
		void WriteToLog(const std::string& str, int n);
		void WriteToLog(const std::string& str, double d);
	private: 
		uint32_t loggerEventNum;
	private:
		LoggerSingletone():loggerEventNum(1){}
		LoggerSingletone(const LoggerSingletone& root) = delete;
		const LoggerSingletone& operator=(const LoggerSingletone&) = delete;
	};

//Singletone
	class FileLoggerSingletone : public LoggerInterface
	{
	public:
		

		static FileLoggerSingletone& getInstance()
		{
			static FileLoggerSingletone theInstance;
			return theInstance;
		}
		void OpenLogFile(const std::string& FN);
		void CloseLogFile();
		std::string GetCurDateTime();
		void WriteToLog(const std::string& str);
		void WriteToLog(const std::string& str, int n);
		void WriteToLog(const std::string& str, double d);

	private:
		FileLoggerSingletone() {}
		FileLoggerSingletone(const FileLoggerSingletone& root) = delete;
		const FileLoggerSingletone& operator=(const FileLoggerSingletone&) = delete;
		//=============================================================================================
	};