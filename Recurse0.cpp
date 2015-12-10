#include <iostream> 
#include <fstream>
#include <string>
#include <cstring>
#include <cassert>
#include <stdlib.h>
#include <unistd.h>

using namespace std;

int extract_digit(string this_file_name);

int main(int argc, char **argv)
{
    assert(argc == 2);
    
    ifstream this_file(argv[1]);
    
    int new_file_number = extract_digit(string(argv[1])) + 1;
    string new_file_name = "Recurse" + to_string(new_file_number) + ".cpp";
    
    ofstream new_file(new_file_name.c_str());
    
    if (this_file.is_open() && new_file.is_open())
    {
        string current_line;
        while(getline(this_file, current_line))
        {
            new_file << current_line << endl;
        }
    }
    
    new_file.close();
    this_file.close();
    
    //usleep(1000000);
    
    string system_command = "rm recurse" + to_string(new_file_number - 1);
    system(system_command.c_str());

    system_command = "g++ -std=c++11 " + new_file_name + " -o recurse"
                            + to_string(new_file_number);
    system(system_command.c_str());
    
    system_command = "./recurse" + to_string(new_file_number)
        + " " + new_file_name;
    
    system(system_command.c_str());
    
    return 0;
}

int extract_digit(string this_file_name)
{
    int first_number = 0;
    
    for (int i = 0; i < this_file_name.size(); ++i)
    {
        char current_char = this_file_name[i];
        
        if ('0' <= current_char &&  current_char <= '9')
        {
            int char_number = (current_char - '0');
            first_number = 10 * first_number + char_number;
        }
    }
    
    return first_number;
}
