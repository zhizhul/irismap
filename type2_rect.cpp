//
//  type2_rect.cpp
//  Irismap
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
#include "image_interface.hpp"
#include "type1_disc.hpp"
#include "type2_rect.hpp"

using namespace std;

void t2_access(string scale, string info_file, string init_node_number, string out_file)
{
    // irismap -type=rect -scale=*pixel info (width x height)* -info-file=*iris info* -init-node=*node number* -out-file=*iris img*
    
    // 1. Get the pixel info.
    t1_print_time();
    cout << "[Iris] Get the pixel info." << endl;
    vector<string> split_res = t1_str_split(scale, 'x');
    int width = atoi(split_res[0].c_str());
    int heiht = atoi(split_res[1].c_str());
    if (width <= 0 || heiht <= 0)
    {
	cout << "[Error] The instruction \"-scale\" is incorrect." << endl;
        return ;
    }
    t1_print_time();
    cout << "[Iris] Get the pixel info finished." << endl;

    // 2. Get the iris information and check the initial node number.
    t1_print_time();
    cout << "[Iris] Generate the space tree." << endl;
    int arr_scale = 0;
    struct SpaceTreeNode **arr = t1_read_spetree(info_file, arr_scale);
    if (arr == NULL)
    {
        cout << "[Error] The instruction \"-info-file\" or its content is incorrect." << endl;
        return ;
    }
    int init_num = atoi(init_node_number.c_str());
    if (init_num > arr_scale || init_num < 1 || arr[init_num]->children_num == 0)
    {
        cout << "[Error] The instruction \"-init-node\" is incorrect." << endl;
        return ;
    }
    t1_print_time();
    cout << "[Iris] Generate the space tree finished." << endl;

    // 3. Generate the iris map.
    t1_print_time();
    cout << "[Iris] Generate the iris map." << endl;
    i_generate_rect_iris(arr, arr_scale, arr[init_num], width, heiht, out_file);
    t1_print_time();
    cout << "[Iris] Generate the iris map finished." << endl;

    // 4. Release data structures.
    for (int i = 1; i <= arr_scale; i++)
    {
	if (arr[i] != NULL) delete arr[i];
    }
    delete [] arr;
}
