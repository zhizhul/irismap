//
//  definition.hpp
//  Irismap
//
//  Created by Zhizhu Liu on 2020/1/3.

// Define parameters, data structures, global variables ... in the file.

#ifndef definition_hpp
#define definition_hpp

#include <string>

using namespace std;

// Base number
extern int base_num;
// Total dimension number
extern int total_dimension;

// Space tree node
struct SpaceTreeNode
{
    // Node number
    int number;
    // Lower bound index
    int inf;
    // Upper bound index
    int sup;
    // Region expression
    string subspace;
    // Static dimension number
    int static_dimension;
    // Parent node pointer
    struct SpaceTreeNode *parent;
    // Child node pointers
    struct SpaceTreeNode **children;
    // Number of child nodes
    int children_num;

    // Number of discovered addresses
    int NDA;
    // Density of active addresses
    double density;
};

// File name of iris information
#define _IRIS_FILE "iris_info"
// Base color information (RGB)
#define _BASE_R 0
#define _BASE_G 0
#define _BASE_B 128
// Alias color information (RGB)
#define _ALIAS_R 128
#define _ALIAS_G 0
#define _ALIAS_B 0

#endif  /* definition_hpp */
