#include <iostream>
#include <QFile>
#include <QDir>
#include <QString>
#include "..\CartoonTexture_Segment_Library\cartoontexture_segment_library.h"

vector<DoInfo *>	DoList;												// �n�����Ϥ� list
struct DoInfo{
	QString fileName;
	QString outDir = "";
};
bool bool_debug = false;

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

void ParamsSet(int &i, char **argv)
{
	QString params(argv[i]);
	QString tempStr;
	if (params == "-h")
	{
		cout << "===== �ѼƳ]�w =====" << endl;
		cout << "���n���Ѽ�(�\�b�e��)�G" << endl;
		cout << "-i <�Ϥ�>			Ū�Ϥ��� Screentone Detection" << endl;
		cout << "-t <�ؿ�>			���ӥؿ��� Screentone Detection" << endl;
		cout << "-last				�ھڰO���ɪ����G�A�~�򩹤U��" << endl;
		cout << endl;
		cout << "�ѦҰѼ�(�\�b�᭱)�G" << endl;
		cout << "-msize <�Ʀr>			�̤p�϶����Ѽ� (ex: 5000)" << endl;
		cout << "-d				��� Debug ��T" << endl;
		cout << endl;
		cout << "�d�ҡG" << endl;
		cout << "	���]�u�����i�Ϥ��A�i�H��" << endl;
		cout << "<exe��> -i 1.png" << endl;
		cout << "	���]�n�����ɭӥؿ��̭������ɡA�i�H��" << endl;
		cout << "<exe��> -t \"D:/123/\"" << endl;
		exit(0);
	}
	else if (params == "-i")
	{
		tempStr = QString(argv[++i]);
		if (CheckFileExist(tempStr))
		{
			DoInfo *tempDoList = new DoInfo;
			tempDoList->fileName = tempStr;
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
				tempDoList->outDir = dir.absolutePath().split("/").last() + "/";
				DoList.push_back(tempDoList);
			}
		}
	}
	else if (params == "-msize")
		SystemParams::s_min_size_area = QString(argv[++i]);
	else if (params == "-d")
		bool_debug = true;
}

int main(int argc, char *argv[])
{
	for (int i = 1; i < argc; i++)
		if (argv[i][0] == '-')
			ParamsSet(i, argv);

	CartoonTexture_Segment_Library *tempSeg;
	for (int i = 0; i < DoList.size(); i++)
	{
		tempSeg = new CartoonTexture_Segment_Library(DoList[i].fileName);
		tempSeg->ComputeCTSegmentation();
		delete tempSeg;
	}
	return 0;
}
