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
	string				fileName;			// �ɮצW��
	string				outDir;				// ��X���ؿ�
	bool				bool_debug;

	cv::Mat				inpImg;				// �n�ާ@����
	int					img_ori_width;		// ��ϼe
	int					img_ori_height;		// ��ϰ�
};

#endif // CARTOONTEXTURE_SEGMENT_LIBRARY_H
