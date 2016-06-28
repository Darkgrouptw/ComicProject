#include <iostream>
#include <QFile>
#include "..\OtsuGaussion_Library\otsugaussion_library.h"

using namespace std;

QString strFileName;													// ���ɦ�m

int main(int argc, char *argv[])
{
	// �P�_�S�� Otsu + Gaussian ���Ѽ�(2) & ���Ѽ� (5)
	if (argc != 2 && argc != 5)
	{
		cout << "�Ѽƿ��~!!" << endl;
		//system("PAUSE");
		return -1;
	}

	// �P�_�ɮצb���b
	strFileName = QString(argv[1]);
	QFile file(strFileName);
	cout << "File: " << argv[1] << endl;
	if (!file.exists())
	{
		cout << "���s�b!!" << endl;
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
