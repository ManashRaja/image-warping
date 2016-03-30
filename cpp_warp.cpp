//#include "stdafx.h"
#include <stdio.h>
#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
//#include <opencv2/nonfree/features2d.hpp>
#include <opencv2/video/tracking.hpp>
#include<stdlib.h>
using namespace cv;
using namespace std;

void rotateImage(const Mat &input, Mat &output, double alpha, double beta, double gamma, double dx, double dy, double dz, double f)

  {

    alpha = (alpha - 90.)*CV_PI/180.;

    beta = (beta - 90.)*CV_PI/180.;

    gamma = (gamma - 90.)*CV_PI/180.;

    // get width and height for ease of use in matrices

    double w = (double)input.cols;

    double h = (double)input.rows;

    // Projection 2D -> 3D matrix

    Mat A1 = (Mat_<double>(4,3) <<

              1, 0, -w/2,

              0, 1, -h/2,

              0, 0,    0,

              0, 0,    1);

    // Rotation matrices around the X, Y, and Z axis

    Mat RX = (Mat_<double>(4, 4) <<

              1,          0,           0, 0,

              0, cos(alpha), -sin(alpha), 0,

              0, sin(alpha),  cos(alpha), 0,

              0,          0,           0, 1);

    Mat RY = (Mat_<double>(4, 4) <<

              cos(beta), 0, -sin(beta), 0,

              0, 1,          0, 0,

              sin(beta), 0,  cos(beta), 0,

              0, 0,          0, 1);

    Mat RZ = (Mat_<double>(4, 4) <<

              cos(gamma), -sin(gamma), 0, 0,

              sin(gamma),  cos(gamma), 0, 0,

              0,          0,           1, 0,

              0,          0,           0, 1);

    // Composed rotation matrix with (RX, RY, RZ)

    Mat R = RX * RY * RZ;

    // Translation matrix

    Mat T = (Mat_<double>(4, 4) <<

             1, 0, 0, dx,

             0, 1, 0, dy,

             0, 0, 1, dz,

             0, 0, 0, 1);

    // 3D -> 2D matrix

    Mat A2 = (Mat_<double>(3,4) <<

              f, 0, w/2, 0,

              0, f, h/2, 0,

              0, 0,   1, 0);

    // Final transformation matrix

    Mat trans = A2 * (T * (R * A1));

    // Apply matrix transformation

    warpPerspective(input, output, trans, input.size(), INTER_LANCZOS4);

  }


int main()
{
	Mat frame, output;
	VideoCapture stream(0);
	stream.read(frame);
	imshow("Input",frame);
	rotateImage(frame, output, 105, 90, 90, 0, 0, 200, 200);
	imshow("output",output);
	waitKey(0);
	
	return 0;
}
