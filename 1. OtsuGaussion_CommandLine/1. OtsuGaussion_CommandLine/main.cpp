#include <iostream>
#include <QFile>

using namespace std;

QString strFileName;													// ���ɦ�m
int ImageWidth, ImageHeight;											// �Ϥ�������e

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
	cout << "File: " << argv[1];
	if (!file.exists())
	{
		cout << "���s�b!!" << endl;
		return -1;
	}

	cv::Mat gray_image;
	//cv::cvtColor(this->)
	return 0;
}
