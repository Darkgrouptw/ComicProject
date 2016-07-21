#include <iostream>
#include <QFile>
#include <QDir>
#include <QString>
#include "..\CartoonTexture_Segment_Library\cartoontexture_segment_library.h"

vector<DoInfo *>	DoList;												// 要做的圖片 list
struct DoInfo{
	QString fileName;
	QString outDir = "";
};
bool bool_debug = false;

//////////////////////////////////////////////////////////////////////////
// 判斷檔案存不存在
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
		cout << "===== 參數設定 =====" << endl;
		cout << "必要的參數(擺在前面)：" << endl;
		cout << "-i <圖片>			讀圖片做 Screentone Detection" << endl;
		cout << "-t <目錄>			對整個目錄做 Screentone Detection" << endl;
		cout << "-last				根據記錄檔的結果，繼續往下做" << endl;
		cout << endl;
		cout << "參考參數(擺在後面)：" << endl;
		cout << "-msize <數字>			最小區塊的參數 (ex: 5000)" << endl;
		cout << "-d				顯示 Debug 資訊" << endl;
		cout << endl;
		cout << "範例：" << endl;
		cout << "	假設只執行單張圖片，可以打" << endl;
		cout << "<exe檔> -i 1.png" << endl;
		cout << "	假設要執行檔個目錄裡面的圖檔，可以打" << endl;
		cout << "<exe檔> -t \"D:/123/\"" << endl;
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
			cout << tempStr.toStdString() << "	檔案不存在" << endl;
	}
	else if (params == "-t")
	{
		QDir dir(argv[++i]);
		QStringList temp1 = dir.entryList();

		// 去掉前面兩個 . 跟 ..
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
