#include "SoundManager.h"
#include "DxLib.h"
#include <string>
#include <vector>
#include <fstream>

SoundManager::SoundManager()
{
	resourceList.clear();
}

void SoundManager::load(const char* soundList)
{
	readLine(soundList);
}

void SoundManager::playBGM(const char* bgmName)
{
	PlaySoundMem(resourceList[bgmName], DX_PLAYTYPE_BACK);
}

void SoundManager::stopBGM()
{
	for (auto itr = resourceList.begin(), end = resourceList.end(); itr != end; ++itr)
	{
		if (CheckSoundMem((*itr).second) != 1) continue;
		StopSoundMem((*itr).second);
	}
}

void SoundManager::playSE(const char* seName)
{
	PlaySoundMem(resourceList[seName], DX_PLAYTYPE_BACK);
}


//////////////////////////////////////////
// 説明　データを分解する。
// 第1引数　1行分のCSVデータ
// 第2引数　データベクター
// 戻り値　データ数　ファイルを開けなかった場合は-1になる
//////////////////////////////////////////
int SoundManager::csvParser(std::string sorce, std::vector<std::string> &data)
{
	char *pSorce;
	std::string buf;
	//ポインタ初期化
	pSorce = &sorce.at(0);
	while (*pSorce != NULL)
	{
		// '#'を含む行は飛ばす
		if (*pSorce == '#') return 1;
		if (*pSorce == ',' || *pSorce == '\n' || *pSorce == '\r')
		{
			data.push_back(buf); //バッファをベクターに入れる

			//*pSorceが改行コードだったら（行の一番後ろまで読み込んだら）分解ループ終了
			if (*pSorce == '\n' || *pSorce == '\r') break;

			buf = "";//バッファを空っぽに
		}
		else buf += *pSorce; //つなぎ合わせる
		pSorce++; //次の文字に移動
	}
	return 0;
}

int SoundManager::readLine(std::string fileName)
{
	//std::ifstream ifs("Sound/soundList.csv");
	std::ifstream ifs(fileName);
	std::string buf;
	std::vector<std::string> data;
	if (!ifs)
		return -1; //ファイルオープンエラー

	while (getline(ifs, buf)) {
		buf += "\n";//改行コードが削除されているので、付け足す

		// '#'が含まれていたら次の行へ
		if (csvParser(buf, data) != 0) continue;
		//for (int i = 0; i < data.size(); i++)
		//{
		//	//読み込んだデータを処理する
		//	//サンプルなので、表示のみ
		//	//cout << data[i] << endl;

		//}
		resourceList.insert(std::pair<std::string, int>(
			data[0], LoadSoundMem(data[1].c_str()))
			);
	}

	return 0;
}