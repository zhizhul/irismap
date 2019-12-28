//
//  main.cpp
//  Iris
//
//  Created by Zhizhu Liu on 2019/12/28.
//

// Programming language standard: C++11.
// Operation system environment: MacOS, Linux.

#include <iostream>
#include <string>

using namespace std;

string m_get_info_file(const char * argv[])
{
    // -- need work
}

string m_get_scale(const char * argv[])
{
    // -- need work
}

string m_get_type(const char * argv[])
{
    // -- need work: 正在写这里。
    // 找出4个指令中前面是-type=的指令（显然首先要求指令长度大于6），然后解析后面的内容并返回。
    // 如果没有找到，就返回一个空串。
}

void work(int argc, const char * argv[])
{
    // 首先分析指令，检查二级指令是否有三个，如果不是三个就报错退出。

    // 在这里也会依次检查二级指令是不是-type=, -scale=, -info-file=，如果不是就仍然报错退出。

    // Analyze the instruction.
    if (argc != 4)
    {
        cout << "[Error] The instruction is incorrect." << endl;
        return ;
    }

    string type = m_get_type(argv);
    string scale = m_get_scale(argv);
    string info_file= m_get_info_file(argv);

    if (type == "disc")
    {
        // Generate disc type iris map.
        // -- need work
        // scale, info_file
    }
    else if (type == "rect")
    {
        // Generate rect type iris map.
        // -- need work
        // scale, info_file
    }
    else
    {
        cout << "[Error] The instruction is incorrect." << endl;
    }
}

int main(int argc, const char * argv[])
{
    work(argc, argv);
    return 0;
}
