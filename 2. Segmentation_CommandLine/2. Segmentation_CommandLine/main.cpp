#include <iostream>
#include <QFile>
#include <QTextStream>
#include <QDir>
#include <QString>
#include "..\CartoonTexture_Segment_Library\cartoontexture_segment_library.h"

using namespace std;
struct DoInfo{
	QString fileName;
	QString outDir = "";
};
vector<DoInfo *>	DoList;												// �n�����Ϥ� list
QString				outDirTemp;
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
		cout << "";
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
	else if (params == "-last")
	{
		tempStr = QString(argv[++i]);
		QFile file("../Output/FileLog.txt");
		if (file.exists())
			if (file.open(QIODevice::ReadOnly | QIODevice::Text))
			{
				QTextStream ss(&file);
				QString tempLine = ss.readLine();
				
				// Ū�W������F�X���ɮ�
				int n = tempLine.replace("Total File Count: ", "").toInt();
				
				// Ū Status �O�_�O�諸
				tempLine = ss.readLine();
				if (!tempLine.endsWith("Complete Binarization!!"))
				{
					cout << "FileLog �� Status �A��ثe���B�J���X!!" << endl;
					return;
				}
				
				// OutDir
				tempLine = ss.readLine();
				outDirTemp = tempLine.replace("Out Dir: ", "");

				// ���U��Ū�Ҧ����ɮ�
				tempLine = ss.readLine();
				for (int i = 0; i < n; i ++)
				{
					tempLine = ss.readLine();
					DoInfo *doTemp = new DoInfo;
					doTemp->fileName = tempLine;
					doTemp->outDir = outDirTemp;
					DoList.push_back(doTemp);
				}
			}
		
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
		SystemParams::s_min_size_area = QString::fromStdString(argv[++i]).toDouble();
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
		cout << "���b���� " << (i + 1) << " / " << DoList.size() << endl;
		tempSeg = new CartoonTexture_Segment_Library(DoList[i]->fileName.toStdString(), DoList[i]->outDir.toStdString());
		tempSeg->ComputeCTSegmentation();
		delete tempSeg;
		cout << "���� " << (i + 1) << " / " << DoList.size() << endl;
	}
	return 0;
}