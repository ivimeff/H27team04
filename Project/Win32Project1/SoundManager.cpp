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
//BGM�̍Đ��ƘA���Đ�����Ă��悢SE�Ŏg�p����
void SoundManager::play(const char* seName)
{
	PlaySoundMem(resourceList[seName], DX_PLAYTYPE_BACK);
}
void SoundManager::playBGM(const char* bgmName)
{
	PlaySoundMem(resourceList[bgmName], DX_PLAYTYPE_LOOP);
}

//�Đ����̃T�E���h�P�̂̒�~���\�b�h
void SoundManager::stop(const char* Name)
{
	if (CheckSoundMem(resourceList[Name]) == 1)
	{
		StopSoundMem(resourceList[Name]);
	}
}
//�A���Đ�������ł���Đ����\�b�h�A��ɘA���Đ������ƍ���SE�Đ��Ɏg��
void SoundManager::playSE(const char* seName)
{
	if (CheckSoundMem(resourceList[seName]) == 0)
	{
		PlaySoundMem(resourceList[seName], DX_PLAYTYPE_BACK);
	}
	//PlaySoundMem(resourceList[seName], DX_PLAYTYPE_BACK);
}
//�Đ����̑S�T�E���h�̒�~���\�b�h
void SoundManager::Allstop()
{
	for (auto itr = resourceList.begin(), end = resourceList.end(); itr != end; ++itr)
	{
		if (CheckSoundMem((*itr).second) != 1) continue;
		StopSoundMem((*itr).second);
	}
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
			// �J�����g�f�B���N�g�����܂܂�Ă��Ȃ���ΒǋL����
			std::string pass = data.size() % 2 == 0 ? buf :
				buf.find(currentDir) == 0 ? buf :
				currentDir + buf;
			data.push_back(pass); //�o�b�t�@���x�N�^�[�ɓ����

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
			data[i], LoadSoundMem(data[i + 1].c_str()))
			);
		i += 2;
	}

	return 0;
}