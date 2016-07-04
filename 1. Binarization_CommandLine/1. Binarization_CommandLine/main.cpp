#include <iostream>
#include <QFile>
#include <QDir>
#include <QStringList>
#include "..\OtsuGaussion_Library\otsugaussion_library.h"

using namespace std;
struct DoInfo{
	QString fileName;													// 郎嘿
	int *Ostu_params = NULL;											// Ostu 把计 (<计> <计>)
	int *Gaussain_params =  NULL;										// Gaussain 把计 (<计> <计> <计>)
	int method = -1;													// ㄏノよ猭
	QString outDir;														// 块玡穦硂嘿
};
vector<DoInfo *>	DoList;												// 璶暗瓜 list
bool				UseMethod = false;									// ゲ斗璶琌 true

//////////////////////////////////////////////////////////////////////////
// 耞郎ぃ
//////////////////////////////////////////////////////////////////////////
bool CheckFileExist(QString fileName)
{
	QFile file(fileName);
	if (file.exists())
		return true;
	return false;
}

//////////////////////////////////////////////////////////////////////////
// 耞 "/" 把计
//////////////////////////////////////////////////////////////////////////
void Slash(QString str)
{
	if (str == "/help")
	{
		cout << "===== 把计砞﹚ =====" << endl;
		cout << "ゲ璶把计(耚玡)" << endl;
		cout << "-i <瓜>			弄瓜" << endl;
		cout << "-t <ヘ魁>			癸俱ヘ魁暗て" << endl;
		cout << endl;
		cout << "把σ把计(耚)" << endl;
		cout << "-m < 0 or 1 or 2>		0 ㄏノ Otsu1 ㄏノ Gaussian 2 琌ㄢよ猭常ㄏノ" << endl;
		cout << "-op <计> <计>		Otsu 把计" << endl;
		cout << "-gp <计> <计> <计>	Gaussian 把计砞﹚" << endl;
		cout << "-d				陪ボ Debug 戈癟" << endl;
		cout << endl;
		cout << "絛ㄒ" << endl;
		cout << "	安砞磅︽虫眎瓜ゴ" << endl;
		cout << "<exe郎> -i 1.png -m 2" << endl;
		cout << "	安砞璶磅︽郎ヘ魁柑瓜郎ゴ" << endl;
		cout << "<exe郎> -t \"D:/123/\" -m 2" << endl;
		UseMethod = true;
	}
}

//////////////////////////////////////////////////////////////////////////
// 耞 "-" 把计
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
			cout << tempStr.toStdString() << "	郎ぃ" << endl;
		//DoInfo *temp = new DoInfo;
	}
	else if (params == "-t")
	{
		QDir dir(argv[++i]);
		QStringList temp1 = dir.entryList();
		// 奔玡ㄢ . 蛤 ..
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

	// 絋﹚Τ⊿Τノよ猭
	if (!UseMethod)
	{
		cout << "⊿Τ﹚よ猭┮礚猭磅︽!!" << endl;
		return -1;
	}

	// 耞郎ぃ
	/*strFileName = QString(argv[1]);
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
	tempImage->ComputeOtsuGaussian();*/
	return 0;
}