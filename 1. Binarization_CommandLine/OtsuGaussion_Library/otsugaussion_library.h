#ifndef OTSUGAUSSION_LIBRARY_H
#define OTSUGAUSSION_LIBRARY_H

#include <iostream>
#include "../../Common/SystemParams.h"
#include <QDir>

// OpenCV
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;

class OtsuGaussion_Library
{
public:
	OtsuGaussion_Library(string, int g_sigma = 0, int bs_sigma = 0, int ws_sigma = 0, bool bool_debug = false, string outDir = "");
	~OtsuGaussion_Library();

	void ComputeOtsuGaussian();
	int Threshold(int *);									// �p�� Otsu �� threshold
	string MakeFileNameWithFlag(string, int, string);		// �b��X���ɦW�U�A�h�[ Fag

private:
	string								filename;			// �ɮצW��
	string								binary_output;		// �G�Ȥƭn��X���ɮסA�q�`�᭱���|��� _1200_B => 1200 dpi B => Binary
	string								outDir;				// ��X���ؿ�
	bool								bool_debug;			// �O�_�n��� debug ��T

	cv::Mat								local;
	cv::Mat								inpImg;				// �n�ާ@����
	cv::Mat								oriInpImg;			// ���
	int									img_ori_width;		// ��ϼe
	int									img_ori_height;		// ��ϰ�
	int									img_width_scale;	// Scale �����᪺�e
	int									img_height_scale;	// Scale �����᪺��

	bool								shouldCalc;			// �ݭn�p��?
};

#endif // OTSUGAUSSION_LIBRARY_H
