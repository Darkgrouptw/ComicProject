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
	QString fileName;													// 檔案名稱
	int method;															// 使用的方法
};
vector<DoInfo *>	DoList;												// 要做的圖片 list
QString				outDir;
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
		cout << "-i <圖片>			讀圖片做二值化" << endl;
		cout << "-t <目錄>			對整個目錄做二值化" << endl;
		cout << endl;
		cout << "參考參數(擺在後面)：" << endl;
		cout << "-m < 0 or 1 or 2>		0 只使用 Otsu，1 只使用 Gaussian， 2 是兩個方法都使用" << endl;
		cout << "-op <數字> <數字>		Otsu 的參數" << endl;
		cout << "-gp <數字> <數字> <數字>	Gaussian 參數設定 <平移> <black> <white>" << endl;
		cout << "-d				顯示 Debug 資訊" << endl;
		cout << "-dir				輸出的資料夾" << endl;
		cout << endl;
		cout << "===========================================" << endl;
		cout << "範例：" << endl;
		cout << "===========================================" << endl;
		cout << "‧假設只執行單張圖片，可以打" << endl;
		cout << "<exe檔> -i 1.png -m 2" << endl << endl;
		cout << "‧假設要執行檔個目錄裡面的圖檔，可以打" << endl;
		cout << "<exe檔> -t \"D:/123/\" -m 2" << endl << endl;
		cout << "‧假設要輸出在特定的資料架內，可以打" << endl;
		cout << "<exe檔> -t \"D:/123/\" -m 2 -dir \"abc/\"" << endl << endl;
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
			cout << tempStr.toStdString() << " 檔案不存在" << endl;
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
	else if (params == "-dir")
		outDir = QString(argv[++i]);
	else
	{
		cout << "沒有這個方法喔!!" << endl;
		cout << "請參考說明 -h" << endl;
		exit(0);
	}
}

int main(int argc, char *argv[])
{
	// 計時
	QElapsedTimer timer;
	timer.start();
	for (int i = 1; i < argc; i++)
		if (argv[i][0] == '-')
			ParamsSet(i, argv);

	// 確定有沒有可以用的方法
	if (!UseMethod)
	{
		cout << "沒有指定方法，所以無法執行!!" << endl;
		return -1;
	}

	
	// 寫檔案名稱，給接下來的程序做
	#pragma region 產生目錄
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
			cout << "完成 " << (++doneIndex) << " / " << DoList.size() << endl;
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
	cout << "時間 => " << (float)timer.elapsed() / 1000 << " s" << endl;
	return 0;
}