#ifndef _SOUND_MANAGER_
#define _SOUND_MANAGER_

#include <map>
#include <vector>

class SoundManager
{
public:
	SoundManager();
	void load(const char* soundList);
	void playBGM(const char* bgmName);
	void stopBGM();
	void playSE(const char* seName);
private:
	std::map<std::string, int> resourceList;
	int csvParser(std::string sorce, std::vector<std::string> &data);
	int readLine(std::string fileName);
};

#endif