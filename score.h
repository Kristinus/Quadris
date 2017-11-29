#ifndef SCORE_H
#define SCORE_H

class Score {
    int currentScore;
    int highScore;
// should we track the level in score or board?? TBD!!!!!!!!!!!!! probably where blocks are generated too
public:
	int getCurrentScore();

	int getHighScore();

	void setHighScore(int);

	void setCurrentScore(int);

	void addToCurrentScore(int);
};

#endif
