#include <iostream>
#include <QFile>
#include <QDir>
#include <QStringList>
#include "..\OtsuGaussion_Library\otsugaussion_library.h"

using namespace std;
struct DoInfo{
	QString fileName;													// �ɮצW��
	int method;															// �ϥΪ���k
	QString outDir;														// ��X�ɫe���|�h�[�o�ӦW��
};
vector<DoInfo *>	DoList;												// �n�����Ϥ� list
bool				UseMethod = false;									// �����n�O true
bool				bool_debug = false;
int					g_sigma = 0;
int					bs_sigma = 0;
int					ws_sigma = 0;

//////////////////////////////////////////////////////////////////////////
// �P�_�ɮצs���s�b
//////////////////////////////////////////////////////////////////////////
bool CheckFileExist(QString fileName)
{
	QFile file(fileName);
	if (file.exists())
		return true;
	return false;
}

//////////////////////////////////////////////////////////////////////////
// �P�_ "-" ���Ѽ�
//////////////////////////////////////////////////////////////////////////
void ParamsSet(int &i, char **argv)
{
	QString params(argv[i]);
	QString tempStr;
	if (params == "-h")
	{
		cout << "===== �ѼƳ]�w =====" << endl;
		cout << "���n���Ѽ�(�\�b�e��)�G" << endl;
		cout << "-i <�Ϥ�>			Ū�Ϥ�" << endl;
		cout << "-t <�ؿ�>			���ӥؿ����G�Ȥ�" << endl;
		cout << endl;
		cout << "�ѦҰѼ�(�\�b�᭱)�G" << endl;
		cout << "-m < 0 or 1 or 2>		0 �u�ϥ� Otsu�A1 �u�ϥ� Gaussian�A 2 �O��Ӥ�k���ϥ�" << endl;
		cout << "-op <�Ʀr> <�Ʀr>		Otsu ���Ѽ�" << endl;
		cout << "-gp <�Ʀr> <�Ʀr> <�Ʀr>	Gaussian �ѼƳ]�w <����> <black> <white>" << endl;
		cout << "-d				��� Debug ��T" << endl;
		cout << endl;
		cout << "�d�ҡG" << endl;
		cout << "	���]�u�����i�Ϥ��A�i�H��" << endl;
		cout << "<exe��> -i 1.png -m 2" << endl;
		cout << "	���]�n�����ɭӥؿ��̭������ɡA�i�H��" << endl;
		cout << "<exe��> -t \"D:/123/\" -m 2" << endl;
		exit(0);
	}
	else if (params == "-i")
	{
		tempStr = QString(argv[++i]);
		if (CheckFileExist(tempStr))
		{
			DoInfo *tempDoList = new DoInfo;
			tempDoList->fileName = tempStr;
			tempDoList->method = -1;
			tempDoList->outDir = "";
			DoList.push_back(tempDoList);
		}
		else
			cout << tempStr.toStdString() << "	�ɮפ��s�b" << endl;
	}
	else if (params == "-t")
	{
		QDir dir(argv[++i]);
		QStringList temp1 = dir.entryList();
		 
		// �h���e����� . �� ..
		for (int j = 2; j < temp1.size(); j++)
		{
			if (temp1[j].contains(".bmp") || temp1[j].contains(".png") || temp1[j].contains(".jpg"))
			{
				DoInfo *tempDoList = new DoInfo;
				tempDoList->fileName = dir.absolutePath() + "/" + temp1[j];
				tempDoList->method = -1;
				tempDoList->outDir = dir.absolutePath().split("/").last() + "/";
				DoList.push_back(tempDoList);
			}
		}
	}
	else if (params == "-m")
	{
		tempStr = QString(argv[++i]);
		if (tempStr == "0" || tempStr == "1" || tempStr == "2")
		{
			for (int i = 0; i < DoList.size(); i++)
				DoList[i]->method = tempStr.toInt();
			UseMethod = true;
		}
		else
		{
			cout << "�S���o�Ӥ�k" << endl;
			exit(0);
		}
	}
	else if (params == "-op")
		return;
	else if (params == "-gp")
	{
		g_sigma = QString(argv[++i]).toInt();
		bs_sigma = QString(argv[++i]).toInt();
		ws_sigma = QString(argv[++i]).toInt();
	}
	else if (params == "-d")
		bool_debug = true;
	else
	{
		cout << "�S���o�Ӥ�k��!!" << endl;
		cout << "�аѦһ��� -h" << endl;
		exit(0);
	}
}

int main(int argc, char *argv[])
{
	for (int i = 1; i < argc; i++)
		if (argv[i][0] == '-')
			ParamsSet(i, argv);

	// �T�w���S���i�H�Ϊ���k
	if (!UseMethod)
	{
		cout << "�S�����w��k�A�ҥH�L�k����!!" << endl;
		return -1;
	}

	OtsuGaussion_Library *tempImage;
	for (int i = 0; i < DoList.size(); i++)
	{
		cout << "���b���� " << (i + 1) << " / " << DoList.size() << endl;
		tempImage = new OtsuGaussion_Library(DoList[i]->fileName.toStdString(), g_sigma, bs_sigma, ws_sigma, bool_debug ,DoList[i]->outDir.toStdString());
		tempImage->ComputeOtsuGaussian();
		delete tempImage;
		cout << "���� " << (i + 1) << " / " << DoList.size() << endl;
	}
	return 0;
}