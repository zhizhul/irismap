//
//  type1_disc.cpp
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

using namespace std;

void t1_print_time()
{
    // Output the time.
    time_t now = time(0);
    tm *ltm = localtime(&now);
    cout << "[" << (1900 + ltm->tm_year) << "/" << (1 + ltm->tm_mon) << "/" << ltm->tm_mday << " " << ltm->tm_hour << ":" << ltm->tm_min << ":" << ltm->tm_sec << "]";
}

vector<string> t1_str_split(string &s, const char &c)
{
    // Split the string.
    string buff = "";
    vector<string> v;
    
    for (auto n : s)
    {
	if (n != c) buff += n;
	else
	{
	    v.push_back(buff);
	    buff = "";
	}
    }
    if (buff != "") v.push_back(buff);
    return v;
}

void t1_trim(string &s)
{
    // Delete space characters in the string.
    int index = 0;
    if (!s.empty())
    {
        while ((index = (int )(s.find(' ', index))) != string::npos)
        {
            s.erase(index, 1);
        }
    }
}

struct SpaceTreeNode **t1_read_spetree(string resdir_name, int &arr_scale)
{
    // Read the space tree iris information.
    ifstream irisfile;
    string line;
    irisfile.open("./" + resdir_name + "/" + _IRIS_FILE);
    if (irisfile.is_open() == false) return NULL;
    
    // Read the base number.
    getline(irisfile, line);
    vector<string> split_res = t1_str_split(line, ':');
    string num_str = split_res[1];
    split_res.clear();
    t1_trim(num_str);
    base_num = atoi(num_str.c_str());
    if (base_num < 0) return NULL;
    
    // Read the number of space tree nodes.
    getline(irisfile, line);
    split_res = t1_str_split(line, ':');
    num_str = split_res[1];
    split_res.clear();
    t1_trim(num_str);
    int node_num = atoi(num_str.c_str());
    arr_scale = node_num;
    if (arr_scale < 0) return NULL;
    
    // Generate a node array, then read node information.
    // Its index starts from 1.
    struct SpaceTreeNode **node_arr = new struct SpaceTreeNode *[node_num + 10];
    getline(irisfile, line);
    while (getline(irisfile, line))
    {
	split_res = t1_str_split(line, ',');	
	string str = split_res[0];
	t1_trim(str);
	int num = atoi(str.c_str());	
	str = split_res[1];
	t1_trim(str);
	int inf = atoi(str.c_str());	
	str = split_res[2];
	t1_trim(str);
	int sup = atoi(str.c_str());	
	str = split_res[3];
	t1_trim(str);
	int parent_num = atoi(str.c_str());	
	str = split_res[4];
	t1_trim(str);
	int children_num = atoi(str.c_str());	
	str = split_res[5];
	t1_trim(str);
	int nda = atoi(str.c_str());	
	str = split_res[6];
	t1_trim(str);
	double density = atof(str.c_str());	
	string subspace = split_res[7];
	int static_dimension = 0;
	for (int i = 0; i < subspace.size(); i++)
	{
	    if (subspace[i] != '*') static_dimension++;
	}
	split_res.clear();
		
	node_arr[num] = new struct SpaceTreeNode;
	node_arr[num]->number = num;
	node_arr[num]->inf = inf;
	node_arr[num]->sup = sup;
	node_arr[num]->subspace = subspace;
	node_arr[num]->static_dimension = static_dimension;
	node_arr[num]->NDA = nda;
	node_arr[num]->density = density;
	
	if (parent_num == 0) node_arr[num]->parent = NULL;
	else
	{
	    node_arr[num]->parent = node_arr[parent_num];
	    int original_children_num = node_arr[parent_num]->children_num;
	    node_arr[parent_num]->children[original_children_num] = node_arr[num];
	    node_arr[parent_num]->children_num++;
	}
	
	node_arr[num]->children_num = 0;
	if (children_num != 0) node_arr[num]->children = new struct SpaceTreeNode *[children_num + 2];
	else node_arr[num]->children = NULL;
    }
    irisfile.close();
    return node_arr;
}

void t1_access(string scale, string info_file, string init_node_number, string out_file)
{
    // irismap -type=disc -scale=*pixel_radius* -info-file=*res_dir* -init-node=*node_number* -out-file=*iris_img*

    // 1. Get the pixel radius.
    t1_print_time();
    cout << "[Iris] Get the pixel radius." << endl;
    int radius = atoi(scale.c_str());
    if (radius <= 0)
    {
	cout << "[Error] The instruction \"-scale\" is incorrect." << endl;
        return ;
    }
    t1_print_time();
    cout << "[Iris] Get the pixel radius finished." << endl;

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
    i_generate_disc_iris(arr, arr_scale, arr[init_num], radius, out_file);
    t1_print_time();
    cout << "[Iris] Generate the iris map finished." << endl;
    
    // 4. Release data structures.
    for (int i = 1; i <= arr_scale; i++)
    {
	if (arr[i] != NULL) delete arr[i];
    }
    delete [] arr;
}
