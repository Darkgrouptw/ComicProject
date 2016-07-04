#include <iostream>
#include <QFile>
#include <QDir>
#include <QStringList>
#include "..\OtsuGaussion_Library\otsugaussion_library.h"

using namespace std;
struct DoInfo{
	QString fileName;													// �ɮצW��
	int *Ostu_params = NULL;											// Ostu �Ѽ� (<�Ʀr> <�Ʀr>)
	int *Gaussain_params =  NULL;										// Gaussain �Ѽ� (<�Ʀr> <�Ʀr> <�Ʀr>)
	int method = -1;													// �ϥΪ���k
	QString outDir;														// ��X�ɫe���|�h�[�o�ӦW��
};
vector<DoInfo *>	DoList;												// �n�����Ϥ� list
bool				UseMethod = false;									// �����n�O true

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
// �P�_ "/" ���Ѽ�
//////////////////////////////////////////////////////////////////////////
void Slash(QString str)
{
	if (str == "/help")
	{
		cout << "===== �ѼƳ]�w =====" << endl;
		cout << "���n���Ѽ�(�\�b�e��)�G" << endl;
		cout << "-i <�Ϥ�>			Ū�Ϥ�" << endl;
		cout << "-t <�ؿ�>			���ӥؿ����G�Ȥ�" << endl;
		cout << endl;
		cout << "�ѦҰѼ�(�\�b�᭱)�G" << endl;
		cout << "-m < 0 or 1 or 2>		0 �u�ϥ� Otsu�A1 �u�ϥ� Gaussian�A 2 �O��Ӥ�k���ϥ�" << endl;
		cout << "-op <�Ʀr> <�Ʀr>		Otsu ���Ѽ�" << endl;
		cout << "-gp <�Ʀr> <�Ʀr> <�Ʀr>	Gaussian �ѼƳ]�w" << endl;
		cout << "-d				��� Debug ��T" << endl;
		cout << endl;
		cout << "�d�ҡG" << endl;
		cout << "	���]�u�����i�Ϥ��A�i�H��" << endl;
		cout << "<exe��> -i 1.png -m 2" << endl;
		cout << "	���]�n�����ɭӥؿ��̭������ɡA�i�H��" << endl;
		cout << "<exe��> -t \"D:/123/\" -m 2" << endl;
		UseMethod = true;
	}
}

//////////////////////////////////////////////////////////////////////////
// �P�_ "-" ���Ѽ�
//////////////////////////////////////////////////////////////////////////
void ParamsSet(int &i, char **argv)
{
	QString params(argv[i]);
	QString tempStr;
	if (params == "-i")
	{
		tempStr = QString(argv[++i]);
		if (CheckFileExist(tempStr))
		{
			DoInfo *tempDoList = new DoInfo;
			tempDoList->fileName = tempStr;
			DoList.push_back(tempDoList);
		}
		else
			cout << tempStr.toStdString() << "	�ɮפ��s�b" << endl;
		//DoInfo *temp = new DoInfo;
	}
	else if (params == "-t")
	{
		QDir dir(argv[++i]);
		QStringList temp1 = dir.entryList();
		// �h���e����� . �� ..
		for (int j = 2; j < temp1.size(); j++)
		{
			DoInfo *tempDoList = new DoInfo;
			tempDoList->fileName = dir.absolutePath() + "/" + temp1[j];
			cout << tempDoList->fileName.toStdString() << endl;
		}
		//cout << temp1[j].toStdString() << endl;
		cout << endl;
	}
	else if (params == "-m")
	{
		tempStr = QString(argv[++i]);
		if (tempStr == "0" || tempStr == "1" || tempStr == "2")
			for (int i = 0; i < DoList.size(); i++)
				DoList[i]->method = tempStr.toInt();
	}
}


int main(int argc, char *argv[])
{
	for (int i = 1; i < argc; i++)
	{
		if (argv[i][0] == '/')
			Slash(QString(argv[i]));
		else if (argv[i][0] == '-')
			ParamsSet(i, argv);
	}

	// �T�w���S���i�H�Ϊ���k
	if (!UseMethod)
	{
		cout << "�S�����w��k�A�ҥH�L�k����!!" << endl;
		return -1;
	}

	// �P�_�ɮצb���b
	/*strFileName = QString(argv[1]);
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
	tempImage->ComputeOtsuGaussian();*/
	return 0;
}