// EncryptedLogger.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <mutex>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <sstream>
#include <iomanip>

#include "MYException.h"

#define TRY_START          try {
#define TRY_END(...)       	} \
    catch(...) \
{ \
    LOG (ERROR, "Caught Exception in function : %s at line %d", __FUNCTION__, __LINE__); \
    return __VA_ARGS__; \
}

void C()
{
    //TRY_START
    //   CT_THROW(INFO, "Inside C %d", 52);
        //throw("abc");
       throw std::exception("def");
    //RETHROW_TRY_END("Exception in C")
}

void B()
{
	TRY_START
        C();
	RETHROW_TRY_END("")
}

void A()
{
    TRY_START
        B();
    RETHROW_TRY_END("Exception in A")
}

int main()
{
    try
    {
        A();
    }
    catch (std::exception& e)
    {
        MY_HANDLE_EXCEPTION(e);
        std::cout << exceptionStr;
    }
    catch (...)
    {
        LOG(INFO, "Unknown exception");
    }
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
