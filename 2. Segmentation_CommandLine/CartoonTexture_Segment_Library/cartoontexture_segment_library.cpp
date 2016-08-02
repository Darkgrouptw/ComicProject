#include "cartoontexture_segment_library.h"
#include "CartoonTextureFilter.h"

CartoonTexture_Segment_Library::CartoonTexture_Segment_Library(string filename, string outDir, bool bool_debug)
{
	this->fileName = filename;
	this->inpImg = cv::imread(filename, CV_LOAD_IMAGE_GRAYSCALE);
	this->img_ori_width = inpImg.size().width;
	this->img_ori_height = inpImg.size().height;
	this->bool_debug = bool_debug;

	if (bool_debug)
		cout << "Width => " << img_ori_width << " Height => " << img_ori_height << endl;

	QDir *dir = new QDir(QString::fromStdString(SystemParams::str_Resources_CFR));
	if (!dir->exists())
		dir->mkdir(".");
	delete dir;

	dir = new QDir(QString::fromStdString(SystemParams::str_Resources_CFC));
	if (!dir->exists())
		dir->mkdir(".");
	delete dir;

	if (outDir != "")
	{
		dir = new QDir(QString::fromStdString(SystemParams::str_Resources_Binarization + outDir));
		if (!dir->exists())
			dir->mkdir(".");
		delete dir;

		dir = new QDir(QString::fromStdString(SystemParams::str_Resources_CFR + outDir));
		if (!dir->exists())
			dir->mkdir(".");
		delete dir;

		dir = new QDir(QString::fromStdString(SystemParams::str_Resources_CFC + outDir));
		if (!dir->exists())
			dir->mkdir(".");
		delete dir;
	}
	this->outDir = outDir;
}
CartoonTexture_Segment_Library::~CartoonTexture_Segment_Library()
{

}

void CartoonTexture_Segment_Library::RemoveSmallArea1(cv::Mat& segm)
{
	if (SystemParams::s_min_size_area == 0)
		return;

	vector<vector<cv::Point>> contours;
	cv::findContours(segm, contours, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE);

	for (size_t a = 0; a < contours.size(); a++)
	{
		double areaSize = cv::contourArea(contours[a]);
		if (areaSize < SystemParams::s_min_size_area)
			cv::drawContours(segm, contours, a, cv::Scalar(0), -1);
	}

	// 玡 Cartoon 暗家絢ノBox Filter┮Τて场だ程玻ネ獶 0 ┪ 255 场だ
	for (int i = 0; i < segm.cols; i++)
		for (int j = 0; j < segm.rows; j++)
			if (segm.ptr<uchar>(j, i)[0] > 0)
				segm.ptr<uchar>(j, i)[0] = 255;

	contours.clear();
}
void CartoonTexture_Segment_Library::RemoveSmallArea2(cv::Mat& segm)
{
	if (SystemParams::s_min_size_area == 0)
		return;

	vector<vector<cv::Point>> contours;
	cv::findContours(segm, contours, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE);

	for (size_t a = 0; a < contours.size(); a++)
	{
		double areaSize = cv::contourArea(contours[a]);
		if (areaSize < SystemParams::s_min_size_area)
			cv::drawContours(segm, contours, a, cv::Scalar(255), -1);
	}

	// 玡 Cartoon 暗家絢ノBox Filter┮Τて场だ程玻ネ獶 0 ┪ 255 场だ
	for (int i = 0; i < segm.cols; i++)
		for (int j = 0; j < segm.rows; j++)
			if (segm.ptr<uchar>(j, i)[0] > 0)
				segm.ptr<uchar>(j, i)[0] = 255;

	contours.clear();
}
void CartoonTexture_Segment_Library::ComputeCTSegmentation()
{
	if (IsBinary())
	{
		cout << fileName << " 瓜⊿Τ竒筁て!!" << endl;
		return;
	}

	// 	狡籹瓜
	cv::Mat ori_loacl_r = inpImg.clone();
	string ori_fileName = fileName.substr(fileName.find_last_of("/") + 1);
	string subName = ori_fileName.substr(ori_fileName.find_last_of("."), ori_fileName.length() - ori_fileName.find_last_of("."));
	ori_fileName = ori_fileName.substr(0, ori_fileName.find_last_of("_B") - 1);
	ori_fileName = ori_fileName.substr(0, ori_fileName.find_last_of("_"));
	ori_fileName += subName;
	int ori_width = ori_loacl_r.cols;
	int ori_height = ori_loacl_r.rows;
	int width = ori_width;
	int height = ori_height;
	float scale = 1.0f;
	float stage = 0.2f;
	int dpi = 1200;

	for (int resizeTimes = 0; scale < 4.1f; resizeTimes++, scale += stage, dpi = 12000 / ((int)(scale * 10)), width = ori_width / scale, height = ori_height / scale)
	{
		cv::Mat resizeMat = ori_loacl_r.clone();
		cv::Mat outSegm;
		cv::Mat drawing;

		string fileName;
		if (resizeTimes != 0)
		{
			cv::resize(ori_loacl_r, resizeMat, cv::Size(width, height), 0, 0, cv::INTER_NEAREST);
			// Binarization
			fileName = MakeFileNameWithFlag(ori_fileName, dpi, "_B");
			if (!cv::imwrite(SystemParams::str_Resources_Binarization + outDir + fileName, resizeMat))
				cout << "Write File Failed: " << SystemParams::str_Resources_Binarization << outDir << fileName << endl;
		}
		outSegm = CartoonTextureFilter::DoSegmentation(resizeMat);
		RemoveSmallArea1(outSegm);
		RemoveSmallArea2(outSegm);

		// Cartoon Filter Region
		fileName = MakeFileNameWithFlag(ori_fileName, dpi, "_CFR");

		if (!cv::imwrite(SystemParams::str_Resources_CFR + outDir + fileName, outSegm))
			cout << "Write File Failed: " << SystemParams::str_Resources_CFR << outDir << fileName << endl;

		drawing = cv::Mat::zeros(cv::Size(width, height), CV_8UC3);
		// 呼翴跋办︹
		for (int i = 0; i < outSegm.rows; i++)
			for (int j = 0; j < outSegm.cols; j++)
				if (resizeMat.at<uchar>(i, j) != 0)
				{
					drawing.at<cv::Vec3b>(i, j) = cv::Vec3b(255, 255, 255);
					// 呼翴跋办 Shader + 30
					if (outSegm.at<uchar>(i, j) != 0)
						drawing.at<cv::Vec3b>(i, j) = cv::Vec3b(71, 137, 244);
				}
		fileName = MakeFileNameWithFlag(ori_fileName, dpi, "_CFC");//Cartoon Filter Color


		if (!cv::imwrite(SystemParams::str_Resources_CFC + outDir + fileName, drawing))
			cout << "Write File Failed: " << SystemParams::str_Resources_CFC << outDir << fileName << endl;

		resizeMat.release();
		outSegm.release();
		drawing.release();

	}
	ori_loacl_r.release();
}

bool CartoonTexture_Segment_Library::IsBinary()
{
	for (int y = 0; y < img_ori_height; y++)
		for (int x = 0; x < img_ori_width; x++)
		{
			cv::Vec3b temp = inpImg.at<cv::Vec3b>(x, y);
			if (!((temp[0] == 0 && temp[1] == 0 && temp[2] == 0) || (temp[0] == 255 && temp[1] == 255 && temp[2] == 255)))
				return false;
		}
	return true;
}

string CartoonTexture_Segment_Library::MakeFileNameWithFlag(string fileName, int dpi, string flag)
{
	stringstream temp_dpi;
	temp_dpi << dpi;

	string resize_dpi;
	temp_dpi >> resize_dpi;

	resize_dpi = "_" + resize_dpi;

	int find_number = fileName.find_first_of(".");
	string mainName = fileName.substr(0, find_number);
	string fileFlag = resize_dpi + flag;

	return mainName + fileFlag + ".png";
}

