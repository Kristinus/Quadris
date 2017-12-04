#include "score.h"

Score::Score() {}


int Score::getCurrentScore() const {
	return currentScore;
}


int Score::getHighScore() const {
	return highScore;
}


void Score::setHighScore(int x) {
	highScore = x;
}


void Score::setCurrentScore(int x) {
	currentScore = x;
}


// Updates scores when block/lines are cleared
void Score::addToCurrentScore(int x) {
	currentScore += x;
	if(currentScore>highScore) highScore = currentScore;
}

