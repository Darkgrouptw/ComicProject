#include <iostream>
#include <QFile>
#include <QDir>
#include <QStringList>
#include "..\OtsuGaussion_Library\otsugaussion_library.h"

using namespace std;
struct DoInfo{
	QString fileName;													// 檔案名稱
	int method;															// 使用的方法
	QString outDir;														// 輸出時前面會多加這個名稱
};
vector<DoInfo *>	DoList;												// 要做的圖片 list
bool				UseMethod = false;									// 必須要是 true
bool				bool_debug = false;
int					g_sigma = 0;
int					bs_sigma = 0;
int					ws_sigma = 0;

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

//////////////////////////////////////////////////////////////////////////
// 判斷 "-" 的參數
//////////////////////////////////////////////////////////////////////////
void ParamsSet(int &i, char **argv)
{
	QString params(argv[i]);
	QString tempStr;
	if (params == "-h")
	{
		cout << "===== 參數設定 =====" << endl;
		cout << "必要的參數(擺在前面)：" << endl;
		cout << "-i <圖片>			讀圖片" << endl;
		cout << "-t <目錄>			對整個目錄做二值化" << endl;
		cout << endl;
		cout << "參考參數(擺在後面)：" << endl;
		cout << "-m < 0 or 1 or 2>		0 只使用 Otsu，1 只使用 Gaussian， 2 是兩個方法都使用" << endl;
		cout << "-op <數字> <數字>		Otsu 的參數" << endl;
		cout << "-gp <數字> <數字> <數字>	Gaussian 參數設定 <平移> <black> <white>" << endl;
		cout << "-d				顯示 Debug 資訊" << endl;
		cout << endl;
		cout << "範例：" << endl;
		cout << "	假設只執行單張圖片，可以打" << endl;
		cout << "<exe檔> -i 1.png -m 2" << endl;
		cout << "	假設要執行檔個目錄裡面的圖檔，可以打" << endl;
		cout << "<exe檔> -t \"D:/123/\" -m 2" << endl;
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
			cout << "沒有這個方法" << endl;
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
		cout << "沒有這個方法喔!!" << endl;
		cout << "請參考說明 -h" << endl;
		exit(0);
	}
}

int main(int argc, char *argv[])
{
	for (int i = 1; i < argc; i++)
		if (argv[i][0] == '-')
			ParamsSet(i, argv);

	// 確定有沒有可以用的方法
	if (!UseMethod)
	{
		cout << "沒有指定方法，所以無法執行!!" << endl;
		return -1;
	}

	OtsuGaussion_Library *tempImage;
	for (int i = 0; i < DoList.size(); i++)
	{
		cout << "正在執行 " << (i + 1) << " / " << DoList.size() << endl;
		tempImage = new OtsuGaussion_Library(DoList[i]->fileName.toStdString(), g_sigma, bs_sigma, ws_sigma, bool_debug ,DoList[i]->outDir.toStdString());
		tempImage->ComputeOtsuGaussian();
		delete tempImage;
		cout << "完成 " << (i + 1) << " / " << DoList.size() << endl;
	}
	return 0;
}