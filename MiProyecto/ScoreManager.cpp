#include "ScoreManager.h"
#include <fstream>
#include <iostream>

ScoreManager::ScoreManager(std::string path) {
	filepath = path;
	scoreCount = 0;
	loadScores();
}

void ScoreManager::loadScores() {
	scoreCount = 0;
	std::ifstream file(filepath);
	if (file.is_open()) {
		std::string name;
		int score;
		std::string replay;
		while (scoreCount < 10 && file >> name >> score >> replay) {
			scores[scoreCount].name = name;
			scores[scoreCount].score = score;
			scores[scoreCount].replayFile  = replay;
			scoreCount++;
		}
		file.close();
	}
}

void ScoreManager::saveScores() {
	std::ofstream file(filepath);
	if (file.is_open()) {
		int limit = (scoreCount > 10) ? 10 : scoreCount;
		for (int i = 0; i < limit; i++) {
			file << scores[i].name << " " << scores[i].score << " " << scores[i].replayFile <<"\n";
		}
		file.close();
	}
}

std::string ScoreManager::registerScore(std::string playerName, int newScore, int sortAlgorithm) {
	for (int i = 0; i < playerName.length(); i++) {
		if (playerName[i] == ' ') playerName[i] = '_';
	}
	if (playerName.empty()) playerName = "Anonimo";
	std::string replayFilename = "replay_" + playerName + "_" + std::to_string(newScore) + ".txt";
	if (scoreCount < 10) {
		scores[scoreCount].name = playerName;
		scores[scoreCount].score = newScore;
		scores[scoreCount].replayFile = replayFilename;
		scoreCount++;
	} else {
		if (newScore > scores[9].score) {
			scores[9].name = playerName;
			scores[9].score = newScore;
			scores[9].replayFile = replayFilename;
		} else {
			return ""; 
		}
	}
	if (sortAlgorithm == 1) {
		bubbleSort();
	} else {
		mergeSort(0, scoreCount - 1);
	}
	saveScores();
	return replayFilename;
}

void ScoreManager::bubbleSort() {
	for (int i = 0; i < scoreCount - 1; i++) {
		for (int j = 0; j < scoreCount - i - 1; j++) {
			if (scores[j].score < scores[j + 1].score) {
				PlayerScore temp = scores[j];
				scores[j] = scores[j + 1];
				scores[j + 1] = temp;
			}
		}
	}
}

void ScoreManager::merge(int left, int mid, int right) {
	int n1 = mid - left + 1;
	int n2 = right - mid;
	PlayerScore* L = new PlayerScore[n1];
	PlayerScore* R = new PlayerScore[n2];
	for (int i = 0; i < n1; i++) L[i] = scores[left + i];
	for (int j = 0; j < n2; j++) R[j] = scores[mid + 1 + j];
	int i = 0, j = 0, k = left;
	while (i < n1 && j < n2) {
		if (L[i].score >= R[j].score) { 
			scores[k] = L[i];
			i++;
		} else {
			scores[k] = R[j];
			j++;
		}
		k++;
	}
	while (i < n1) {
		scores[k] = L[i];
		i++;
		k++;
	}
	while (j < n2) {
		scores[k] = R[j];
		j++;
		k++;
	}
	delete[] L;
	delete[] R;
}

void ScoreManager::mergeSort(int left, int right) {
	if (left >= right) return;
	int mid = left + (right - left) / 2;	
	mergeSort(left, mid);
	mergeSort(mid + 1, right);
	merge(left, mid, right);
}

PlayerScore ScoreManager::getScore(int index) {
	return scores[index]; 
}

int ScoreManager::getScoreCount() { 
	return scoreCount; 
}
