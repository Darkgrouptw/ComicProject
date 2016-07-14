#ifndef CARTOONTEXTURE_SEGMENT_LIBRARY_H
#define CARTOONTEXTURE_SEGMENT_LIBRARY_H

#include <iostream>
#include "../../Common/SystemParams.h"

// OpenCV
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;

class CartoonTexture_Segment_Library
{
public:
	CartoonTexture_Segment_Library(string filename);
	~CartoonTexture_Segment_Library();

	//void ComputeCTSegmentation();
	//void RemoveSmallArea1(cv::Mat&);
	//void RemoveSmallArea2(cv::Mat&);

	//string Os
	string MakeFileNameWithFlag(string, int, string);
	bool IsBinary();
private:
	string				filename;			// 檔案名稱

	cv::Mat				inpImg;				// 要操作的圖
	int					img_ori_width;		// 原圖寬
	int					img_ori_height;		// 原圖高
};

#endif // CARTOONTEXTURE_SEGMENT_LIBRARY_H
