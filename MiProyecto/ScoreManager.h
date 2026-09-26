#ifndef SCOREMANAGER_H
#define SCOREMANAGER_H

#include <string>

struct PlayerScore {
	std::string name;
	int score;
	std::string replayFile; 
};

class ScoreManager {
private:
	PlayerScore scores[10]; 
	int scoreCount;
	std::string filepath;
	
public:
	ScoreManager(std::string path);
	void loadScores();
	void saveScores();
	std::string registerScore(std::string playerName, int newScore, int sortAlgorithm);
	void bubbleSort();
	void mergeSort(int left, int right);
	void merge(int left, int mid, int right);
	PlayerScore getScore(int index);
	int getScoreCount();
};

#endif
