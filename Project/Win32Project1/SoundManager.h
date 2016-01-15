#ifndef _SOUND_MANAGER_
#define _SOUND_MANAGER_

#include <map>
#include <vector>

class SoundManager
{
public:
	SoundManager();
	void load(const char* soundList);
	void play(const char* bgmName);
	void stop(const char* Name);
	void playSE(const char* seName);
	void Allstop();
private:
	std::map<std::string, int> resourceList;
	int csvParser(std::string sorce, std::vector<std::string> &data);
	int readLine(std::string fileName);
	int i = 0;
	const std::string currentDir = "Sound/";
};

#endif