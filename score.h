#ifndef SCORE_H
#define SCORE_H

class Score {
    int currentScore = 0;
    int highScore = 0;

public:
	Score();
	int getCurrentScore() const;
	int getHighScore() const;
	void setHighScore(int);
	void setCurrentScore(int);
	void addToCurrentScore(int);
};

#endif
