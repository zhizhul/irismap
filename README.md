Irismap
=======

Dear readers,

This is a visualization tool prototype for ["6Tree"](https://github.com/zhizhul/6tree) results.

Environment & Compilation
-------------------------

The code is written based on C++11 and can be compiled by g++. It can run in macOS or Linux. To compile the code, just type

> g++ -std=c++11 *.cpp -o irismap

Function 1: Generate a disc Iris image
--------------------------------------

> ./irismap -type=disc -scale=**pixel_radius** -info-file=**res_dir** -init-node=**node_number** -out-file=**iris_img**

It could generate a disc Iris image which is a BMP file. *pixel_radius* means the pixel size of the radius, *res_dir* means the name of the result directory generated after a 6Tree search, *node_number* means the start node number which you want to use to generate the map in the space tree, and *iris_img* means the plan name of the Iris image. Besides, the node of *node_number* can not be a leaf node.

For instance, if you want to: generate a disc Iris image whose radius has 2000 pixels, search result directory is *res-100k-hex* (should be in the irismap's directory), start node number is 1 (means the root node of the tree), output file name is *iris-100k-hex.bmp*, type

> ./irismap -type=disc -scale=2000 -info-file=*res-100k-hex* -init-node=1 -out-file=*iris.bmp*

Function 2: Generate a rectangle Iris image
-------------------------------------------

> ./irismap -type=rect -scale=**pixel_info** -info-file=**res_dir** -init-node=**node_number** -out-file=**iris_img**

Generates a rectangle Iris image, in the *-scale=*, input the width and the height for the image size.

For instance, type

> ./irismap -type=rect -scale=2000x1000 -info-file=*res-100k-hex* -init-node=1 -out-file=*iris.bmp*
