#include "score.h"

Score::Score() {}

int Score::getCurrentScore() {
	return currentScore;
}

int Score::getHighScore() {
	return highScore;
}

void Score::setHighScore(int x) {
	highScore = x;
}

void Score::setCurrentScore(int x) {
	currentScore = x;
}

void Score::addToCurrentScore(int x) {
	currentScore += x;
	if(currentScore>highScore) highScore = currentScore;
}
