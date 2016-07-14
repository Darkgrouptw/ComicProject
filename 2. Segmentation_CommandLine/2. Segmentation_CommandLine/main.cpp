#include <iostream>
#include <QFile>
#include <QDir>
#include <QString>
#include "..\CartoonTexture_Segment_Library\cartoontexture_segment_library.h"

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
	}
}

int main(int argc, char *argv[])
{
	for (int i = 1; i < argc; i++)
	{
		if (argv[i][0] == '/')
			Slash(QString(argv[i]));
		//else if (argv[i][0] == '-')
			//ParamsSet(i, argv);
	}
	CartoonTexture_Segment_Library tempSeg("../../Output/Binarization/Cat001_Bin_1200_B.png");
	tempSeg.ComputeCTSegmentation();

	return 0;
}
