#pragma once
#include <cstddef>
#include <exception>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

// #define DEBUG_MODE // Comment out this line if debugging is not needed


class Logger
{
    public:
    
        template<typename... Args>
		static void log(const Args&... args)
		{
			ofstream logfile(msDebugFileName, ios_base::app);
			if (logfile.fail()) {
				cerr << "Unable to open debug file" << endl;
				return;
			}
			// Write to file using a standard C++17 unary right fold
			((logfile << args), ...);
			logfile << endl;

            ((std::cout << args), ...);
			std::cout << endl;
		}

    private:

        // static const string msDebugFileName = "debugfile2.txt";
		static const string msDebugFileName;
		
};

#ifdef DEBUG_MODE

// class Logger
// {
//     public:
    
//         template<typename... Args>
// 		static void log(const Args&... args)
// 		{
// 			ofstream logfile(msDebugFileName, ios_base::app);
// 			if (logfile.fail()) {
// 				cerr << "Unable to open debug file" << endl;
// 				return;
// 			}
// 			// Write to file using a standard C++17 unary right fold
// 			((logfile << args), ...);
// 			logfile << endl;

//             ((std::cout << args), ...);
// 			std::cout << endl;
// 		}

//     private:

//         // static const string msDebugFileName = "debugfile2.txt";
// 		static const string msDebugFileName;
		
// };

// const string Logger::msDebugFileName = "debugfile.txt";

	#define log(...) Logger::log(__func__, "(): ", __VA_ARGS__)
#else
	#define log(...)
#endif