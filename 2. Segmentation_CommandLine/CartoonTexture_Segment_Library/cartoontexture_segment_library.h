#ifndef CARTOONTEXTURE_SEGMENT_LIBRARY_H
#define CARTOONTEXTURE_SEGMENT_LIBRARY_H

#include <iostream>
#include "../../Common/SystemParams.h"
#include <QDir>

// OpenCV
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;

class CartoonTexture_Segment_Library
{
public:
	CartoonTexture_Segment_Library(string, string, bool);
	~CartoonTexture_Segment_Library();

	void ComputeCTSegmentation();
	void RemoveSmallArea1(cv::Mat&);
	void RemoveSmallArea2(cv::Mat&);

	string MakeFileNameWithFlag(string, int, string);
	bool IsBinary();
private:
	string				fileName;			// 檔案名稱
	string				outDir;				// 輸出的目錄
	bool				bool_debug;

	cv::Mat				inpImg;				// 要操作的圖
	int					img_ori_width;		// 原圖寬
	int					img_ori_height;		// 原圖高
};

#endif // CARTOONTEXTURE_SEGMENT_LIBRARY_H
