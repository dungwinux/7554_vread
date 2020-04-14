#include <iostream>
#include <fstream>
#include <string>

#ifndef LENGTH
#define LENGTH 4096
#endif

const char key = 0x55;

int main(int argc, char **argv)
{
    if (argc == 1)
    {
        std::cout
            << "7554 .v Reader\n"
            << '\n'
            << "Usage: " << argv[0] << " [filename]\n"
            << '\n'
            << "This tool is able to decrypt/encrypt `.v` resource data file in 7554.\n";
    }
    if (argc != 2)
    {
        std::cerr << "You may drag and drop file into executable.\n";
        return 1;
    }

    std::string filename(argv[1]);
    auto outname = filename + ".zip";

    std::cout << "Input: " << filename << '\n'
              << "Output: " << outname << '\n';

    std::ifstream f_inp(filename, f_inp.in | f_inp.binary);
    std::ofstream f_out(outname, f_out.out | f_out.binary | f_out.trunc);

    if (!f_inp.is_open())
    {
        std::cout << "Failed to open " << filename << '\n';
    }
    else
    {
        while (!f_inp.eof())
        {
            char buffer[LENGTH];
            f_inp.read(buffer, LENGTH);
            int real_len = f_inp.gcount();
            for (int i = 0; i < real_len; i++)
            {
                buffer[i] ^= key;
            }
            f_out.write(buffer, real_len);
        }
        f_inp.close();
        f_out.close();
        std::cout << "Done !!\n";
    }

    return 0;
}