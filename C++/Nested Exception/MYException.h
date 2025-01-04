#pragma once

#include <stdexcept>
#include <string>
#include <iostream>
#include <string>
#include <cstdlib>

#include "log.h"

namespace
{
	// Custom exception class to be used for more practical throwing
	class MyException : public std::runtime_error
	{
	public:
		MyException(const char* file, unsigned int line, const std::string& message) :
			std::runtime_error(message)
		{
			if (!message.empty())
			{
				_traceAndException = std::string(file) + ":" + std::to_string(line) + " : " + message;
				_exceptionStr = message;
			}
			else
				_traceAndException = std::string(file) + ":" + std::to_string(line);
		}

		MyException(const char* file, unsigned int line, const int iLoglevel, const std::string& message) :
			std::runtime_error(message), _loglevel(iLoglevel)
		{
			if (!message.empty())
			{	_traceAndException = std::string(file) + ":" + std::to_string(line) + " : " + message;
				_exceptionStr = message;
			}
			else
				_traceAndException = std::string(file) + ":" + std::to_string(line);
		}

		~MyException() throw() {}

		const char* what() const throw()
		{
			return _traceAndException.c_str();
		}

		std::string GetExceptionMessage() const throw()
		{
			return _exceptionStr;
		}

		int GetLoglevel() const
		{
			return _loglevel;
		}

	private:
		std::string _traceAndException;
		std::string _exceptionStr;
		int _loglevel = ERROR_LEVEL;
	};

	std::string MyExceptionStr(const char* format, ...)
	{
		va_list argptr;
		char* szMessage = NULL;
		int bytesPrinted = 0;

		va_start(argptr, format);
		bytesPrinted = vasprintf(&szMessage, format, argptr);
		va_end(argptr);

		std::string message;
		if (bytesPrinted != -1)
			message = std::string(szMessage);

		return message;
	}

	// Rethrow (creates a std::nested_exception) an exception, using the Exception class
	// which contains function and line info. The original exception is preserved...
	void rethrow(const char* file, unsigned int line, const std::string& message = "")
	{
		try
		{
			std::rethrow_exception(std::current_exception());
		}
		catch (...)
		{
			std::throw_with_nested(MyException(file, line, message));
		}
	}

	// Backtrace an exception by recursively unwrapping the nested exceptions
	void Backtrace(std::exception& ex, std::string& trace, std::string& exceptionStr, int& loglevel)
	{
		try
		{
			std::rethrow_if_nested(ex);

			//If it is innermost exception then find out log level
			trace += ex.what() + std::string("\n");
			MyException* ptr = dynamic_cast<MyException*>(&ex);
			if (ptr)
			{
				loglevel = ptr->GetLoglevel();
			}
			else
				exceptionStr += trace;
		}
		catch (std::exception& nested_ex)
		{
			Backtrace(nested_ex, trace, exceptionStr, loglevel);
			trace += ex.what() + std::string("\n");
			auto ptr = dynamic_cast<MyException*>(&nested_ex);
			if (ptr && !ptr->GetExceptionMessage().empty())
				exceptionStr += ptr->GetExceptionMessage() + "\n";
		}
	}

	// General Exception handler
	std::string Handle_Exception(std::exception& ex, const std::string& function = "")
	{
		std::string trace;
		std::string exceptionStr;
		int logLevel = ERROR_LEVEL;

		try
		{
			Backtrace(ex, trace, exceptionStr, logLevel);

			if (function != "")
				trace += "Exception caught in function : " + function + "\n";

			const MyException* const ptr = dynamic_cast<MyException*>(&ex);
			if (ptr && !ptr->GetExceptionMessage().empty())
			{
				exceptionStr += ptr->GetExceptionMessage() + "\n";
			}

			logger_fun("MyException", logLevel, __FILE__, SYSTEM_FUNCTION, __LINE__, trace.c_str(), "");
		}
		catch (const std::exception& nested_ex)
		{
			LGMLOG(ERROR, nested_ex.what());
		}
		return exceptionStr;
	}
}

// Shorthand for throwing an Exception with function and line info using macros
#define MY_THROW(M,message,...) throw MyException(__FUNCTION__, __LINE__, M##_LEVEL, MyExceptionStr(message, ##__VA_ARGS__));

// Shorthand for rethrowing and Exception with function and line info using macros
#define MY_RETHROW(message) rethrow(__FUNCTION__, __LINE__, message);

// Shorthand for handling an exception, including a backtrace
#define MY_HANDLE_EXCEPTION(ex) std::string exceptionStr = Handle_Exception(ex, __func__);

#define RETHROW_TRY_END(...)       	} \
    catch (std::exception &) { \
	CT_RETHROW(__VA_ARGS__); } \
    catch(...) { \
	LGMLOG (ERROR, "Caught Exception in function : %s at line %d ", __FUNCTION__, __LINE__); \
	std::rethrow_exception(std::current_exception()); } \

