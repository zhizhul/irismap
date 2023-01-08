//
//  image_interface.hpp
//  Irismap
//
//  Created by Zhizhu Liu on 2020/1/3.
//

// Define image interface functions, parameters, variables ... in the file.

#include <string>

#ifndef image_interface_hpp
#define image_interface_hpp

using namespace std;

void i_mkbmp_api(int width, int height, unsigned char *data, string bmp_name);

void i_rgb_to_hsv(unsigned char r, unsigned char g, unsigned char b, double &h, double &s, double &v);

void i_hsv_to_rgb(double h, double s, double v, unsigned char &r, unsigned char &g, unsigned char &b);

double i_find_density_disc(int x, int y, int x_center, int y_center, int radius, struct SpaceTreeNode **arr, int arr_scale, struct SpaceTreeNode *root);

void i_get_rgb(double density, double base_h, double base_s, double base_v, unsigned char &r, unsigned char &g, unsigned char &b);

void i_generate_disc_iris(struct SpaceTreeNode **arr, int arr_scale, struct SpaceTreeNode *root, int radius, string output_name);

double i_find_density_rect(int x, int y, int width, int heiht, struct SpaceTreeNode **arr, int arr_scale, struct SpaceTreeNode *root);

void i_generate_rect_iris(struct SpaceTreeNode **arr, int arr_scale, struct SpaceTreeNode *root, int width, int heiht, string output_name);

#endif /* image_interface_hpp */
