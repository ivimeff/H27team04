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
// �����@�f�[�^�𕪉�����B
// ��1�����@1�s����CSV�f�[�^
// ��2�����@�f�[�^�x�N�^�[
// �߂�l�@�f�[�^���@�t�@�C�����J���Ȃ������ꍇ��-1�ɂȂ�
//////////////////////////////////////////
int SoundManager::csvParser(std::string sorce, std::vector<std::string> &data)
{
	char *pSorce;
	std::string buf;
	//�|�C���^������
	pSorce = &sorce.at(0);
	while (*pSorce != NULL)
	{
		// '#'���܂ލs�͔�΂�
		if (*pSorce == '#') return 1;
		if (*pSorce == ',' || *pSorce == '\n' || *pSorce == '\r')
		{
			data.push_back(buf); //�o�b�t�@���x�N�^�[�ɓ����

			//*pSorce�����s�R�[�h��������i�s�̈�Ԍ��܂œǂݍ��񂾂�j�������[�v�I��
			if (*pSorce == '\n' || *pSorce == '\r') break;

			buf = "";//�o�b�t�@������ۂ�
		}
		else buf += *pSorce; //�Ȃ����킹��
		pSorce++; //���̕����Ɉړ�
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
		return -1; //�t�@�C���I�[�v���G���[

	while (getline(ifs, buf)) {
		buf += "\n";//���s�R�[�h���폜����Ă���̂ŁA�t������

		// '#'���܂܂�Ă����玟�̍s��
		if (csvParser(buf, data) != 0) continue;
		//for (int i = 0; i < data.size(); i++)
		//{
		//	//�ǂݍ��񂾃f�[�^����������
		//	//�T���v���Ȃ̂ŁA�\���̂�
		//	//cout << data[i] << endl;

		//}
		resourceList.insert(std::pair<std::string, int>(
			data[0], LoadSoundMem(data[1].c_str()))
			);
	}

	return 0;
}