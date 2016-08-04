#include <iostream>
#include <QFile>
#include <QDir>
#include <QStringList>
#include <QTextStream>
#include <QIODevice>
#include <QElapsedTimer>
#include "..\OtsuGaussion_Library\otsugaussion_library.h"

using namespace std;
struct DoInfo{
	QString fileName;													// �ɮצW��
	int method;															// �ϥΪ���k
};
vector<DoInfo *>	DoList;												// �n�����Ϥ� list
QString				outDir;
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
		cout << "-i <�Ϥ�>			Ū�Ϥ����G�Ȥ�" << endl;
		cout << "-t <�ؿ�>			���ӥؿ����G�Ȥ�" << endl;
		cout << endl;
		cout << "�ѦҰѼ�(�\�b�᭱)�G" << endl;
		cout << "-m < 0 or 1 or 2>		0 �u�ϥ� Otsu�A1 �u�ϥ� Gaussian�A 2 �O��Ӥ�k���ϥ�" << endl;
		cout << "-op <�Ʀr> <�Ʀr>		Otsu ���Ѽ�" << endl;
		cout << "-gp <�Ʀr> <�Ʀr> <�Ʀr>	Gaussian �ѼƳ]�w <����> <black> <white>" << endl;
		cout << "-d				��� Debug ��T" << endl;
		cout << "-dir				��X����Ƨ�" << endl;
		cout << endl;
		cout << "===========================================" << endl;
		cout << "�d�ҡG" << endl;
		cout << "===========================================" << endl;
		cout << "�E���]�u�����i�Ϥ��A�i�H��" << endl;
		cout << "<exe��> -i 1.png -m 2" << endl << endl;
		cout << "�E���]�n�����ɭӥؿ��̭������ɡA�i�H��" << endl;
		cout << "<exe��> -t \"D:/123/\" -m 2" << endl << endl;
		cout << "�E���]�n��X�b�S�w����Ƭ[���A�i�H��" << endl;
		cout << "<exe��> -t \"D:/123/\" -m 2 -dir \"abc/\"" << endl << endl;
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
			DoList.push_back(tempDoList);
		}
		else
			cout << tempStr.toStdString() << " �ɮפ��s�b" << endl;
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
	else if (params == "-dir")
		outDir = QString(argv[++i]);
	else
	{
		cout << "�S���o�Ӥ�k��!!" << endl;
		cout << "�аѦһ��� -h" << endl;
		exit(0);
	}
}

int main(int argc, char *argv[])
{
	// �p��
	QElapsedTimer timer;
	timer.start();
	for (int i = 1; i < argc; i++)
		if (argv[i][0] == '-')
			ParamsSet(i, argv);

	// �T�w���S���i�H�Ϊ���k
	if (!UseMethod)
	{
		cout << "�S�����w��k�A�ҥH�L�k����!!" << endl;
		return -1;
	}

	
	// �g�ɮצW�١A�����U�Ӫ��{�ǰ�
	#pragma region ���ͥؿ�
	QDir *dir = new QDir(QString("../Output"));
	if (!dir->exists())
		dir->mkpath(".");
	delete dir;

	dir = new QDir(QString::fromStdString(SystemParams::str_Resources_Original));
	if (!dir->exists())
		dir->mkpath(".");
	delete dir;

	dir = new QDir(QString::fromStdString(SystemParams::str_Resources_Binarization));
	if (!dir->exists())
		dir->mkpath(".");
	delete dir;
	#pragma endregion

	QFile file("../Output/FileLog.txt");
	file.open(QIODevice::WriteOnly | QIODevice::Text);

	int doneIndex = 0;
	#pragma omp parallel for
	for (int i = 0; i < DoList.size(); i++)
	{
		OtsuGaussion_Library *tempImage;
		tempImage = new OtsuGaussion_Library(DoList[i]->fileName.toStdString(), g_sigma, bs_sigma, ws_sigma, bool_debug, outDir.toStdString());
		tempImage->ComputeOtsuGaussian();
		delete tempImage;

		#pragma omp critical
		{
			cout << "���� " << (++doneIndex) << " / " << DoList.size() << endl;
		}
	}


	QTextStream ss(&file);
	ss << "Total File Count: " << DoList.size() << endl;
	ss << "Status: Complete Binarization!!" << endl;
	ss << "Out Dir: " << outDir << endl;
	ss << "Files:" << endl;
	for (int i = 0; i < DoList.size(); i++)
	{
		DoList[i]->fileName = DoList[i]->fileName.replace("\\", "/");
		if (DoList[i]->fileName.endsWith(".bmp"))
			ss << QString::fromStdString(SystemParams::str_Resources_Binarization) << outDir + DoList[i]->fileName.replace(".bmp", "_1200_B.png").split("/").last() << endl;
		else if (DoList[i]->fileName.endsWith(".jpg"))
			ss << QString::fromStdString(SystemParams::str_Resources_Binarization) << outDir + DoList[i]->fileName.replace(".jpg", "_1200_B.png").split("/").last() << endl;
		else if (DoList[i]->fileName.endsWith(".png"))
			ss << QString::fromStdString(SystemParams::str_Resources_Binarization) << outDir + DoList[i]->fileName.replace(".png", "_1200_B.png").split("/").last() << endl;
	}
	cout << "�ɶ� => " << (float)timer.elapsed() / 1000 << " s" << endl;
	return 0;
}