#include "cartoontexture_segment_library.h"

CartoonTexture_Segment_Library::CartoonTexture_Segment_Library(string filename)
{
	this->filename = filename;
	this->inpImg = cv::imread(filename);
	this->img_ori_width = inpImg.size().width;
	this->img_ori_height = inpImg.size().height;

	cout << "Width => " << img_ori_width << " Height => " << img_ori_height << endl;
}

CartoonTexture_Segment_Library::~CartoonTexture_Segment_Library()
{

}

/*void CartoonTexture_Segment_Library::RemoveSmallArea1(cv::Mat& segm)
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

	// bug ???
	for (int i = 0; i < segm.cols; i++)
		for (int j = 0; j < segm.rows; j++)
		{
			if (segm.ptr<uchar>(j, i)[0] > 0)
			{
				segm.ptr<uchar>(j, i)[0] = 255;
			}
		}

	contours.clear();
}
void CartoonTexture_Segment_Library::RemoveSmallArea2(cv::Mat& segm)
{
	if (SystemParams::s_min_size_area == 0)
	{
		return;
	}

	vector<vector<cv::Point>> contours;
	cv::findContours(segm, contours, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE);

	for (size_t a = 0; a < contours.size(); a++)
	{
		double areaSize = cv::contourArea(contours[a]);
		if (areaSize < SystemParams::s_min_size_area)
			cv::drawContours(segm, contours, a, cv::Scalar(255), -1);
	}

	// bug ???
	for (int i = 0; i < segm.cols; i++)
		for (int j = 0; j < segm.rows; j++)
		{
			if (segm.ptr<uchar>(j, i)[0] > 0)
			{
				segm.ptr<uchar>(j, i)[0] = 255;
			}
		}

	contours.clear();
}*/
void CartoonTexture_Segment_Library::ComputeCTSegmentation()
{
	if (!IsBinary())
	{
		cout << "此沒有二值化過喔!!" << endl;
		return;
	}

	// 	複製原圖
	string ori_fileName = filename.substr(filename.find_last_of("/") + 1);
	cout << ori_fileName << endl;
	// 拿副檔名的格式，為了把 _1200_B 拿掉
	string subName = ori_fileName.substr(ori_fileName.find_last_of("."), ori_fileName.length() - ori_fileName.find_last_of("."));
	ori_fileName = ori_fileName.substr(0, ori_fileName.find_last_of("_B") - 1);
	ori_fileName = ori_fileName.substr(0, ori_fileName.find_last_of("_"));
	ori_fileName += subName;
	int width = inpImg.cols;
	int height = inpImg.rows;
	float scale = 1.0f;
	float stage = 0.2f;
	int dpi = 1200;

	cv::Mat resizeMat = ori_loacl_r.clone();
	cv::Mat outSegm;
	cv::Mat drawing;
	//Timing calculation
	using namespace boost::chrono;
	auto start = steady_clock::now();
	for (int resizeTimes = 0; scale < 4.1f; resizeTimes++, scale += stage, dpi = 12000 / ((int)(scale * 10)), width = ori_width / scale, height = ori_height / scale)
	{
		string fileName;
		if (resizeTimes != 0)
		{
			cv::resize(ori_loacl_r, resizeMat, cv::Size(width, height), 0, 0, cv::INTER_NEAREST);
			fileName = MakeFileNameWithFlag(ori_fileName, dpi, "_B");//Binarization
			if (!cv::imwrite(SystemParams::str_Resources_Binarization + "/" + fileName, resizeMat)){
				cout << "Write File Failed: " << SystemParams::str_Resources_Binarization << "/" << fileName << endl;
			}
		}
		outSegm = CartoonTextureFilter::DoSegmentation(resizeMat);
		RemoveSmallArea1(outSegm);
		RemoveSmallArea2(outSegm);
		fileName = MakeFileNameWithFlag(ori_fileName, dpi, "_CFR");//Cartoon Filter Region

		if (!cv::imwrite(SystemParams::str_Resources_CFR + "/" + fileName, outSegm)){
			cout << "Write File Failed: " << SystemParams::str_Resources_CFR << "/" << fileName << endl;
		}

		drawing = cv::Mat::zeros(cv::Size(width, height), CV_8UC3);
		//網點區域上色
		for (int i = 0; i < outSegm.rows; i++)
		{
			for (int j = 0; j < outSegm.cols; j++)
			{
				if (resizeMat.at<uchar>(i, j) != 0)
				{
					drawing.at<cv::Vec3b>(i, j) = cv::Vec3b(255, 255, 255);
					//網點區域
					if (outSegm.at<uchar>(i, j) != 0)
					{
						drawing.at<cv::Vec3b>(i, j) = cv::Vec3b(71, 137, 244);//shader +30
					}
				}
			}
		}
		fileName = MakeFileNameWithFlag(ori_fileName, dpi, "_CFC");//Cartoon Filter Color


		if (!cv::imwrite(SystemParams::str_Resources_CFC + "/" + fileName, drawing)){
			cout << "Write File Failed: " << SystemParams::str_Resources_CFC << "/" << fileName << endl;
		}


		if (ShowFrame && resizeTimes == 0)
		{
			// Copy to label map
			for (int i = 0; i < height; i++)
			{
				for (int j = 0; j < width; j++)
				{
					if (outSegm.ptr<uchar>(i, j)[0] > 0)
						labelMap[i * width + j] = 0;
					else
						labelMap[i * width + j] = -1;
				}
			}
			// Dilated Label Map (NEED TO FIX THIS!)
			cv::Mat elem2 = cv::getStructuringElement(2, cv::Size(10, 10));
			//for(int a = 0; a < 3; a++)
			cv::morphologyEx(outSegm, outSegm, cv::MORPH_DILATE, elem2);
			cv::morphologyEx(outSegm, outSegm, cv::MORPH_DILATE, elem2);

			// Dilated Label Map
			outSegm.convertTo(outSegm, CV_8UC1);
			for (int i = 0; i < height; i++)
			{
				for (int j = 0; j < width; j++)
				{
					if (outSegm.ptr<uchar>(i, j)[0] > 0)
						dilatedLabelMap[i * width + j] = 0;
					else
						dilatedLabelMap[i * width + j] = -1;
				}
			}
		}

		resizeMat.release();
		outSegm.release();
		drawing.release();

	}
	ori_loacl_r.release();
	auto dur = steady_clock::now() - start;
	auto msDur = duration_cast<milliseconds>(dur).count();
	cout << ori_fileName << " Done : " << msDur << " milliseconds\n";
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

