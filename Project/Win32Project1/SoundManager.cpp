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
//BGMの再生と連続再生されてもよいSEで使用する
void SoundManager::play(const char* seName)
{
	PlaySoundMem(resourceList[seName], DX_PLAYTYPE_BACK);
}
void SoundManager::playBGM(const char* bgmName)
{
	PlaySoundMem(resourceList[bgmName], DX_PLAYTYPE_LOOP);
}

//再生中のサウンド単体の停止メソッド
void SoundManager::stop(const char* Name)
{
	if (CheckSoundMem(resourceList[Name]) == 1)
	{
		StopSoundMem(resourceList[Name]);
	}
}
//連続再生を回避できる再生メソッド、主に連続再生されると困るSE再生に使う
void SoundManager::playSE(const char* seName)
{
	if (CheckSoundMem(resourceList[seName]) == 0)
	{
		PlaySoundMem(resourceList[seName], DX_PLAYTYPE_BACK);
	}
	//PlaySoundMem(resourceList[seName], DX_PLAYTYPE_BACK);
}
//再生中の全サウンドの停止メソッド
void SoundManager::Allstop()
{
	for (auto itr = resourceList.begin(), end = resourceList.end(); itr != end; ++itr)
	{
		if (CheckSoundMem((*itr).second) != 1) continue;
		StopSoundMem((*itr).second);
	}
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
			// カレントディレクトリが含まれていなければ追記する
			std::string pass = data.size() % 2 == 0 ? buf :
				buf.find(currentDir) == 0 ? buf :
				currentDir + buf;
			data.push_back(pass); //バッファをベクターに入れる

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
			data[i], LoadSoundMem(data[i + 1].c_str()))
			);
		i += 2;
	}

	return 0;
}