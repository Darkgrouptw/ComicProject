#include <iostream>
#include <QFile>
#include "..\OtsuGaussion_Library\otsugaussion_library.h"

using namespace std;

QString strFileName;													// 瓜郎竚

int main(int argc, char *argv[])
{
	// 耞⊿Τ Otsu + Gaussian 把计(2) & Τ把计 (5)
	if (argc != 2 && argc != 5)
	{
		cout << "把计岿粇!!" << endl;
		//system("PAUSE");
		return -1;
	}

	// 耞郎ぃ
	strFileName = QString(argv[1]);
	QFile file(strFileName);
	cout << "File: " << argv[1] << endl;
	if (!file.exists())
	{
		cout << "ぃ!!" << endl;
		return -1;
	}
	OtsuGaussion_Library *tempImage;
	if (argc == 5)
		tempImage = new OtsuGaussion_Library(strFileName.toStdString(), QString(argv[2]).toInt(), QString(argv[3]).toInt(), QString(argv[4]).toInt());
	else
		tempImage = new OtsuGaussion_Library(strFileName.toStdString());
	tempImage->ComputeOtsuGaussian();
	return 0;
}
