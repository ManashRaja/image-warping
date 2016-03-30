# image-warping

Implementation of 3D image rotation as shown in http://jepsonsblog.blogspot.in/2012/11/rotation-in-3d-using-opencvs.html  
The cpp code is same as in the tutorial, while the python implentation is new but based on the cpp implementation itself.  

Usage:  
Variable are pretty self expalatory. f = focal length and its better to have f = z_trans = around 200  
*Rotation is in degee with 90 as normal*  
**cpp**
- Function: ```rotateImage(input_img, output_img, x_rot, y_rot, z_rot, x_tarns, y_tarns, z_tarns, f);```
- Execute: ```g++ cpp_warp.cpp -o warpCpp `pkg-config --cflags --libs opencv` ```

**python**
- Function: ```dst = rotateImage(input_img, x_rot, y_rot, z_rot, x_tarns, y_tarns, z_tarns, f)```
- Execute: ```python python_warp.py```
