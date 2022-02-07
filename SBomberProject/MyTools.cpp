
#include <conio.h>
#include <windows.h>
#include <stdint.h>
#include <time.h> 

#include <string>
#include <iostream>
#include <fstream>
#include <chrono>


#include "MyTools.h"

using namespace std;


    ofstream logOut;
	
    //=============================================================================================

    void ScreenSingleton::ClrScr()
    {
        system("cls");
    }

    void ScreenSingleton::GotoXY(double x, double y)
    {
        const COORD cc = { short(x), short(y) };
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cc);
    }

    uint16_t ScreenSingleton::GetMaxX()
    {
        HANDLE hWndConsole;
        if (hWndConsole = GetStdHandle(-12))
        {
            CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
            if (GetConsoleScreenBufferInfo(hWndConsole, &consoleInfo))
            {
				//int height = consoleInfo.srWindow.Bottom - consoleInfo.srWindow.Top + 1;
				return consoleInfo.srWindow.Right;
            }
        }

        return 0;
    }

    uint16_t ScreenSingleton::GetMaxY()
    {
        HANDLE hWndConsole;
        if (hWndConsole = GetStdHandle(-12))
        {
            CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
            if (GetConsoleScreenBufferInfo(hWndConsole, &consoleInfo))
            {
                return consoleInfo.srWindow.Bottom;
            }
        }

        return 0;
    }

    void ScreenSingleton::SetColor(ConsoleColor color)
    {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, color); // color =  (WORD)((BackgroundColor << 4) | TextColor))
    }

    //=============================================================================================
	
	//Proxy
	void LoggerSingletone::OpenLogFile(const string& FN)
	{
		FileLoggerSingletone::getInstance().OpenLogFile(FN);
	}

	void LoggerSingletone::CloseLogFile()
	{
		FileLoggerSingletone::getInstance().CloseLogFile();
	}

	string LoggerSingletone::GetCurDateTime()
	{
		return FileLoggerSingletone::getInstance().GetCurDateTime();
	}

	void LoggerSingletone::WriteToLog(const string& str)
	{
		
		if (logOut.is_open())
		{
			logOut << loggerEventNum<<' ';
			FileLoggerSingletone::getInstance().WriteToLog(str);
			++loggerEventNum;
		}
	}

	void LoggerSingletone::WriteToLog(const string& str, int n)
	{
		if (logOut.is_open())
		{
			logOut << loggerEventNum << ' ';
			FileLoggerSingletone::getInstance().WriteToLog(str, n);
			++loggerEventNum;
		}
	}

	void LoggerSingletone::WriteToLog(const string& str, double d)
	{
		if (logOut.is_open())
		{
			logOut << loggerEventNum << ' ';
			FileLoggerSingletone::getInstance().WriteToLog(str, d);
			++loggerEventNum;
		}
	}

	//Singletone
    void FileLoggerSingletone::OpenLogFile(const string& FN)
    {
        logOut.open(FN, ios_base::out);
    }


    void FileLoggerSingletone::CloseLogFile()
    {
        if (logOut.is_open())
        {
            logOut.close();
        }
    }

	string FileLoggerSingletone::GetCurDateTime()
	{
		auto cur = std::chrono::system_clock::now();
		time_t time = std::chrono::system_clock::to_time_t(cur);
		char buf[64] = { 0 };
		ctime_s(buf, 64, &time);
		buf[strlen(buf) - 1] = '\0';
		return string(buf);
	}

    void FileLoggerSingletone::WriteToLog(const string& str)
    {
        if (logOut.is_open())
        {
            logOut << GetCurDateTime() << " - " << str << endl;
        }
    }

    void FileLoggerSingletone::WriteToLog(const string& str, int n)
    {
        if (logOut.is_open())
        {
            logOut << GetCurDateTime() << " - " << str << n << endl;
        }
    }

    void FileLoggerSingletone::WriteToLog(const string& str, double d)
    {
        if (logOut.is_open())
        {
            logOut << GetCurDateTime() << " - " << str << d << endl;
        }
    }



    //===========================================================================================