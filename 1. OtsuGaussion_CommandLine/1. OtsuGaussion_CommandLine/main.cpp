#include <iostream>
#include <QFile>

using namespace std;

QString strFileName;													// 圖檔位置
int ImageWidth, ImageHeight;											// 圖片的高跟寬

int main(int argc, char *argv[])
{
	// 判斷沒有 Otsu + Gaussian 的參數(2) & 有參數 (5)
	if (argc != 2 && argc != 5)
	{
		cout << "參數錯誤!!" << endl;
		//system("PAUSE");
		return -1;
	}

	// 判斷檔案在不在
	strFileName = QString(argv[1]);
	QFile file(strFileName);
	cout << "File: " << argv[1];
	if (!file.exists())
	{
		cout << "不存在!!" << endl;
		return -1;
	}

	cv::Mat gray_image;
	//cv::cvtColor(this->)
	return 0;
}
