//
//  definition.hpp
//  Iris
//
//  Created by Zhizhu Liu on 2020/1/3.

// Define parameters, data structures, global variables ... in the file.

#ifndef definition_hpp
#define definition_hpp

#include <string>

using namespace std;

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
    // Parent node pointer
    struct SpaceTreeNode *parent;
    // Child node pointers
    struct SpaceTreeNode *children;
    // Number of child nodes
    int children_num;

    // Number of discovered addresses
    int NDA;
    // Density of active addresses
    double density;
};

// Base number
extern int base_num;

#endif  /* definition_hpp */
