//
//  image_interface.cpp
//  Irismap
//
//  Created by Zhizhu Liu on 2020/1/3.
//

// Define image interface functions, parameters, variables ... in the file.

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <random>
#include <chrono>
#include <cmath>
#include <cstdio>
#include <ctime>
#include <sys/stat.h>
#include <sys/types.h>
#include "definition.hpp"
#include "type1_disc.hpp"
#include "type2_rect.hpp"
#include "image_interface.hpp"

using namespace std;

void i_mkbmp_api(int width, int height, unsigned char *data, string bmp_name)
{
    unsigned short type = 0x4d42;
    int modified_byte_width = 0;
    if ((width * 3) % 4 != 0)
    {
	modified_byte_width = 4 - (width * 3) % 4;
    }
    int header[] = {(width * 3 + modified_byte_width) * height + 54,
		    0, 54, 40, width, height,
		    1 | 3 * 8 << 16, 0,
		    (width * 3 + modified_byte_width) * height,
		    0, 0, 0, 0};
    ofstream out;
    out.open(bmp_name, ios::out | ios::binary);
    out.write((char *)&type, 2);
    out.write((char *)header, 52);
    out.write((char *)data, (width * 3 + modified_byte_width) * height);
    out.close();
}

void i_rgb_to_hsv(unsigned char r, unsigned char g, unsigned char b, double &h, double &s, double &v)
{
    // r/g/b: 0-255, h/s/v: 0.0-1.0
    
    unsigned char max;
    if (r > g) max = r;
    else max = g;
    if (max < b) max = b;
    unsigned char min;
    if (r > g) min = g;
    else min = r;
    if (min > b) min = b;
    
    // h
    if (max == min) h = 0.0;
    else if (max == r && g >= b)
    {
	h = ((double)g - (double)b) / ((double)max - (double)min) / 6.0;
	if (h < 0.0) h += 1.0;
    }
    else if (max == r && g < b)
    {
	h = (((double)g - (double)b) / ((double)max - (double)min) / 6.0) + 1.0;
	if (h > 1.0) h -= 1.0;
    }
    else if (max == g)
    {
	h = (((double)b - (double)r) / ((double)max - (double)min) / 6.0) + (1.0 / 3.0);
    }
    else if (max == b)
    {
	h = (((double)r - (double)g) / ((double)max - (double)min) / 6.0) + (2.0 / 3.0);
    }
    else h = 0.0;
    
    // s
    if (max == 0) s = 0.0;
    else
    {
	s = 1.0 - ((double)min / (double)max);
    }
    
    // v
    v = (double)max / 255.0;
}

void i_hsv_to_rgb(double h, double s, double v, unsigned char &r, unsigned char &g, unsigned char &b)
{
    // r/g/b: 0-255, h/s/v: 0.0-1.0
    
    int h_i = (int)floor(h * 6.0) % 6;
    double f = h * 6.0 - (double)h_i;
    double p = v * (1.0 - s);
    double q = v * (1.0 - f * s);
    double t = v * (1.0 - (1.0 - f) * s);
    unsigned char rv = (int)floor(v * 255.0);
    unsigned char rp = (int)floor(p * 255.0);
    unsigned char rq = (int)floor(q * 255.0);;
    unsigned char rt = (int)floor(t * 255.0);
    
    switch (h_i)
    {
    case 0:
	r = rv; g = rt; b = rp; break;
    case 1:
	r = rq; g = rv; b = rp; break;
    case 2: 
	r = rp; g = rv; b = rt; break;
    case 3: 
	r = rp; g = rq; b = rv; break;
    case 4: 
	r = rt; g = rp; b = rv; break;
    case 5: 
	r = rv; g = rp; b = rq; break;
    }
}

double i_find_density_disc(int x, int y, int x_center, int y_center, int radius, struct SpaceTreeNode **arr, int arr_scale, struct SpaceTreeNode *root)
{
    int rx = x - x_center;
    int ry = y - y_center;
    
    double theta;
    double alpha = acos((double)ry / (double)sqrt((double)(rx * rx + ry * ry)));
    double pi = 3.14159265358979;
    if (rx < 0) theta = 2 * pi - alpha;
    else if (rx == 0 && ry > 0) theta = 0;
    else if (rx == 0 && ry < 0) theta = pi;
    else theta = alpha;
    
    int inf = root->inf;
    int sup = root->sup;
    int addr_sit = inf + (int)floor((double)(sup - inf) * theta / (2 * pi));
    int dist = (int)sqrt(rx * rx + ry * ry);
    
    int td = total_dimension;
    struct SpaceTreeNode *ptr = root;
    while (ptr != NULL)
    {
	if (ptr->children_num == 0) break;
	int sd = ptr->static_dimension;
	if (dist * td <= radius * sd) break;
	for (int i = 0; i < ptr->children_num; i++)
	{
	    int sinf = ptr->children[i]->inf;
	    int ssup = ptr->children[i]->sup;
	    if (sinf <= addr_sit && addr_sit <= ssup)
	    {
		ptr = ptr->children[i];
		break;
	    }
	}
    }
    return ptr->density;
}

void i_get_rgb(double density, double base_h, double base_s, double base_v, unsigned char &r, unsigned char &g, unsigned char &b)
{
    // Get the RGB value based on the density, with log10 function.

    if (density < 0)
    {
	// Means that its an alias region.
	r = _ALIAS_R;
	g = _ALIAS_G;
	b = _ALIAS_B;
	return ;
    }
    // Low density means high alpha.
    double alpha;
    if (density == 0.0) alpha = 1.0;
    else alpha = (-1.0 * log(density) / log((double)base_num)) / (double)total_dimension;
    base_s = 1.0 - alpha;
    base_v = 0.5 + alpha * 0.5;
    i_hsv_to_rgb(base_h, base_s, base_v, r, g, b);
}

void i_generate_disc_iris(struct SpaceTreeNode **arr, int arr_scale, struct SpaceTreeNode *root, int radius, string output_name)
{
    // Generate the data arr which includes RGB information of 
    // each pixel, then use API to generate iris BMP file.
    
    // Iris map generate from the 12:00 situation and be clockwise.
    
    int td = 32;
    if (base_num == 32) td = 25;
    else if (base_num == 16) td = 32;
    else if (base_num == 8) td = 42;
    else if (base_num == 4) td = 64;
    else if (base_num == 2) td = 128;
    total_dimension = td;
    
    double base_h, base_s, base_v;
    i_rgb_to_hsv(_BASE_R, _BASE_G, _BASE_B, base_h, base_s, base_v);
    
    int width = (radius << 1) - 1;
    int heiht = (radius << 1) - 1;
    
    int modified_byte_width = 0;
    if ((width * 3) % 4 != 0)
    {
	modified_byte_width = 4 - (width * 3) % 4;
    }
        
    unsigned char *data = new unsigned char [(width * 3 + modified_byte_width) * heiht + 2];
    int index = 0;
    
    int x_center = radius;
    int y_center = radius;
    for (int y = 0; y < heiht; y++)
    {
	for (int x = 0; x < width; x++)
	{
	    int rx = x - x_center;
	    int ry = y - y_center;
	    int dist2 = rx * rx + ry * ry;

	    if (dist2 >= radius * radius)
	    {
		data[index++] = 0xff;
		data[index++] = 0xff;
		data[index++] = 0xff;
	    }
	    else
	    {
		double density = i_find_density_disc(x, y, x_center, y_center, radius, arr, arr_scale, root);
		unsigned char r, g, b;
		i_get_rgb(density, base_h, base_s, base_v, r, g, b);
		data[index++] = b;
		data[index++] = g;
		data[index++] = r;
	    }
	}
	for (int x = 1; x <= modified_byte_width; x++)
	{
	    data[index++] = 0xff;
	}
    }
    i_mkbmp_api(width, heiht, data, output_name);
    delete [] data;
}

double i_find_density_rect(int x, int y, int width, int heiht, struct SpaceTreeNode **arr, int arr_scale, struct SpaceTreeNode *root)
{
    int inf = root->inf;
    int sup = root->sup;
    int addr_sit = inf + (int)floor((double)(sup - inf) * ((double)x / (double)width));
    double dist = (double)y;
    
    int td = total_dimension;
    struct SpaceTreeNode *ptr = root;
    while (ptr != NULL)
    {
	if (ptr->children_num == 0) break;
	int sd = ptr->static_dimension;
	if (dist * td <= heiht * sd) break;
	for (int i = 0; i < ptr->children_num; i++)
	{
	    int sinf = ptr->children[i]->inf;
	    int ssup = ptr->children[i]->sup;
	    if (sinf <= addr_sit && addr_sit <= ssup)
	    {
		ptr = ptr->children[i];
		break;
	    }
	}
    }
    return ptr->density;
}

void i_generate_rect_iris(struct SpaceTreeNode **arr, int arr_scale, struct SpaceTreeNode *root, int width, int heiht, string output_name)
{
    // Generate the data arr which includes RGB information of 
    // each pixel, then use API to generate iris BMP file.
    
    // Rectangle mode.
    
    int td = 32;
    if (base_num == 32) td = 25;
    else if (base_num == 16) td = 32;
    else if (base_num == 8) td = 42;
    else if (base_num == 4) td = 64;
    else if (base_num == 2) td = 128;
    total_dimension = td;
    
    double base_h, base_s, base_v;
    i_rgb_to_hsv(_BASE_R, _BASE_G, _BASE_B, base_h, base_s, base_v);
    
    int modified_byte_width = 0;
    if ((width * 3) % 4 != 0)
    {
	modified_byte_width = 4 - (width * 3) % 4;
    }
    
    unsigned char *data = new unsigned char [(width * 3 + modified_byte_width) * heiht + 2];
    int index = 0;
    
    for (int y = 0; y < heiht; y++)
    {
	for (int x = 0; x < width; x++)
	{
	    double density = i_find_density_rect(x, y, width, heiht, arr, arr_scale, root);
	    unsigned char r, g, b;
	    i_get_rgb(density, base_h, base_s, base_v, r, g, b);
	    data[index++] = b;
	    data[index++] = g;
	    data[index++] = r;
	}
	for (int x = 0; x < modified_byte_width; x++)
	{
	    data[index++] = 0xff;
	}
    }
    i_mkbmp_api(width, heiht, data, output_name);
    delete [] data;
}
