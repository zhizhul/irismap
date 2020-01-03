//
//  type1_disc.cpp
//  Iris
//
//  Created by Zhizhu Liu on 2020/1/3.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <cmath>
#include <ctime>
#include "definition.hpp"
#include "type1_disc.hpp"

using namespace std;

void t1_print_time()
{
    // Output the time.
    time_t now = time(0);
    tm *ltm = localtime(&now);
    cout << "[" << (1900 + ltm->tm_year) << "/" << (1 + ltm->tm_mon) << "/" << ltm->tm_mday << " " << ltm->tm_hour << ":" << ltm->tm_min << ":" << ltm->tm_sec << "]";
}

struct SpaceTreeNode *t1_read_spetree(string info_file, int &arr_scale)
{
    // 之后要读取iris_info信息，生成对应进制模式和规模的空间树
    // 同时也要检查一下node_number看是否符合要求，node_number区间在[1, 结点总数]，并且不能为叶子结点的编号

    // 首先要读取文件，检查是否能够正确读取：在读取的过程中，只要出现读取错误，就报错并释放数据然后退出程序（返回NULL值）。
}

void t1_access(string scale, string info_file, string init_node_number, string out_file)
{
    // irismap -type=disc -scale=*pixel_radius* -info-file=*iris_info* -init-node=*node_number* -out-file=*iris_img*

    // 1. Get the pixel radius.
    t1_print_time();
    cout << "[Iris] Get the pixel radius."
    int radius = atoi(scale.c_str());
    if (radius <= 0)
    {
        cout << "[Error] The instruction \"-scale\" is incorrect." << endl;
        return ;
    }
    t1_print_time();
    cout << "[Iris] Get the pixel radius finished."

    // 2. Get the iris information and check the initial node number.
    t1_print_time();
    cout << "[Iris] Generate the space tree."
    int arr_scale = 0;
    struct SpaceTreeNode *arr = t1_read_spetree(info_file, arr_scale); // -- need work
    if (arr == NULL)
    {
        cout << "[Error] The instruction \"-info-file\" or its content is incorrect." << endl;
        return ;
    }
    struct SpaceTreeNode *init_node = t1_get_init_node(arr, arr_scale, init_node_number); // -- need work
    if (init_node == NULL)
    {
        cout << "[Error] The instruction \"-init-node\" is incorrect." << endl;
        return ;
    }
    t1_print_time();
    cout << "[Iris] Generate the space tree finished."

    // -- need work
    // 最后进行像素矩阵的生成并保存为bmp位图
    // 像素矩阵的生成就要交给图像接口来实现了
    // 也就是说图像接口要接收这么几个参数：空间树（以init_node为根结点）、像素半径（radius）、成图名称（outfile前缀）、成图后缀（根据后缀可以解析出图像类型）

    // 别忘了最后还要释放空间树
}
