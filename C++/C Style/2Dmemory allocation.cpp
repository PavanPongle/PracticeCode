/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, OCaml, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

using namespace std;


int** fun(int m, int n)
{
    int** ptr = (int**)malloc( m * sizeof(int*));
    for(int i = 0 ; i < m ; ++i)
    {
        ptr[i] = (int*)malloc( n * sizeof(int));
    }
    
    return ptr;
}

int main()
{
    
    int **ptr = fun(2,3);
    
    ptr[0][1] = int(5);
    
    cout << ptr[0][1] << endl;
    
    return 0;
}