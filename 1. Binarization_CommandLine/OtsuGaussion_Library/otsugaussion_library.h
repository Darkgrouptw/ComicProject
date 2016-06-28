#ifndef OTSUGAUSSION_LIBRARY_H
#define OTSUGAUSSION_LIBRARY_H

#include <iostream>
#include "../../Common/SystemParams.h"

// OpenCV
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;

class OtsuGaussion_Library
{
public:
	OtsuGaussion_Library(string, int g_sigma = 0, int bs_sigma = 0, int ws_sigma = 0);
	~OtsuGaussion_Library();

	void ComputeOtsuGaussian();
	int Threshold(int *);									// 計算 Otsu 的 threshold
	string MakeFileNameWithFlag(string, int, string);		// 在輸出的檔名下，多加 Fag

private:
	string								filename;			// 檔案名稱
	string								binary_output;		// 二值化要輸出的檔案，通常後面都會跟著 _1200_B => 1200 dpi B => Binary

	cv::Mat								local;
	cv::Mat								inpImg;				// 要操作的圖
	cv::Mat								oriInpImg;			// 原圖
	int									img_ori_width;		// 原圖寬
	int									img_ori_height;		// 原圖高
	int									img_width_scale;	// Scale 完之後的寬
	int									img_height_scale;	// Scale 完之後的高

	bool								shouldCalc;			// 需要計算?
};

#endif // OTSUGAUSSION_LIBRARY_H
