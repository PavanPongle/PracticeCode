// FileSignature.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <boost/filesystem.hpp>

using namespace boost::filesystem;

int main()
{

    path dir_path("C:\\Users\\source\\repos\\FileSignature\\FileSignature\\SampleFiles");

    unsigned char zip_signature[4] = { 0x50, 0x4B, 0x03, 0x04 };
    unsigned char gzip_signature[4] = { 0x1F, 0x8B, 0x0, 0x0 };
	
    for (recursive_directory_iterator it(dir_path), end; it != end; ++it)
    {
        try
        {
            if (is_regular_file(it->status()))
            {
                const auto& ext = it->path().extension();
                //if (ext == ".zip")
                {
                    std::cout << it->path().filename().string() << ": ";
                    unsigned char sig[4] = {0};
                    std::ifstream fs(it->path().string().c_str(), std::ios::binary | std::ios::in);

                    if (!fs.is_open())
                    {
                        std::cout << "file is not open";
                    }

                    fs.read((char*)sig, 4);
                    if (memcmp(sig, zip_signature, 4) == 0)
                    {
                        std::cout << "zip file ";
                    }
                    else if (memcmp(sig, gzip_signature, 2) == 0)
                    {
                        std::cout << "gzip file ";
                    }
                    else
                    {
                        std::cout << "not a compressed file ";
                    }
                    fs.close();
                    std::cout << std::endl;
                    //std::cout << std::hex << (int)sig[0] << (int)sig[1] << (int)sig[2] << (int)sig[3] << std::endl;
                }
            }
        }
        catch (const filesystem_error& e)
        {
            std::cout << "Exception in accessing file attributes" << it->path().string().c_str() << e.what();
        }
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
