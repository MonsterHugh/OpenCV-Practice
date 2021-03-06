// OpenCVPractice07（灰度直方图的实现）.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include<iostream>
#include<opencv2\highgui\highgui.hpp>
#include<opencv2\imgproc\imgproc.hpp>

using namespace std;
using namespace cv;

#define WINDOW_NAME1 "原图像"
#define WINDOW_NAME2 "灰度图像"
#define WINDOW_NAME3 "灰度直方图"



int main()
{
	Mat srcImage = imread("b9f3699560ad2f6396d81bf1b7432041.jpg", 0);
	namedWindow(WINDOW_NAME1,WINDOW_AUTOSIZE);
	imshow("原图像", srcImage);
    sp = srcImage.shape
    print sp
    sz1 = sp[0]#height(rows) of image
    sz2 = sp[1]#width(colums) of image
    sz3 = sp[2]#the pixels value is made up of three primary colors
	//MatND类型用于存放直方图数据
	MatND dstHist;
	int dims = 1;
	float hranges[] = { 0,255 };
	const float *ranges[] = { hranges };
	int size = 256;
	int channels = 0;
	calcHist(&srcImage, 1, &channels, Mat(),dstHist, dims, &size, ranges);
	int scale = 1;
	Mat dstImage(size*scale, size, CV_8U, Scalar(0));
	//获取最大值和最小值
	double minValue = 0;
	double maxValue = 0;
	minMaxLoc(dstHist, &minValue, &maxValue, 0, 0);
	cout << "最大值是：" << maxValue << ",最小值是：" << minValue << endl;
	//绘制直方图
	int hpt = saturate_cast<int>(0.9*size);
	for (int i = 0; i < 256; i++)
	{
		float binValue = dstHist.at<float>(i);
		int realValue = saturate_cast<int>(binValue*hpt/maxValue);
		rectangle(dstImage, Point(i*scale, size - 1), Point((i + 1)*scale - 1, size - realValue), Scalar(255));
	}
	imshow("灰度直方图", dstImage);
	waitKey(0);
    return 0;
}


// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门提示: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
