#include <iostream>
#include <QFile>
#include <QDir>
#include <QString>
#include "..\CartoonTexture_Segment_Library\cartoontexture_segment_library.h"

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
