//
//  main.cpp
//  Irismap
//
//  Created by Zhizhu Liu on 2019/12/28.
//

// Programming language standard: C++11.
// Operation system environment: MacOS, Linux.

#include <iostream>
#include <string>
#include "definition.hpp"
#include "type1_disc.hpp"
#include "type2_rect.hpp"

using namespace std;

string m_get_secd_ins(int argc, const char * argv[], string seci)
{
    int len = seci.length();
    for (int i = 0; i < argc; i++)
    {
        string strl = string(argv[i]);
        if (strl.length() > len && strl.substr(0, len) == seci)
        {
            return strl.substr(len);
        }
    }
    return "";
}

void work(int argc, const char * argv[])
{
    // Analyze secondary instructions.
    if (argc != 6)
    {
        cout << "[Error] The secondary instruction number is incorrect." << endl;
        return ;
    }
    string type = m_get_secd_ins(argc, argv, "-type=");
    string scale = m_get_secd_ins(argc, argv, "-scale=");
    string info_file = m_get_secd_ins(argc, argv, "-info-file=");
    string init_node = m_get_secd_ins(argc, argv, "-init-node=");
    string out_file = m_get_secd_ins(argc, argv, "-out-file=");

    // Perform the iris generation.
    if (type == "disc")
    {
        // Generate disc type image.
        t1_access(scale, info_file, init_node, out_file);
    }
    else if (type == "rect")
    {
        // Generate rect type image.
        t2_access(scale, info_file, init_node, out_file);
    }
    else
    {
        cout << "[Error] The instruction \"-type\" is incorrect." << endl;
    }
}

int main(int argc, const char * argv[])
{
    work(argc, argv);
    return 0;
}
