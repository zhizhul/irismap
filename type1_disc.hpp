//
//  type1_disc.hpp
//  Iris
//
//  Created by Zhizhu Liu on 2020/1/3.
//

#ifndef type1_disc_hpp
#define type1_disc_hpp

#include <string>

using namespace std;

void t1_print_time();

struct SpaceTreeNode *t1_read_spetree(string info_file, int &arr_scale);

void t1_access(string scale, string info_file, string init_node_number, string out_file);

#endif /* type1_disc_hpp */
