#ifndef GRID_H
#define GRID_H

#include <vector>
#include <memory>
#include "textDisplay.h"
#include "cell.h"

class Level;
class Score;
struct HintInfo;
template <typename InfoType> class Observer;

class Grid {
	std::vector<std::vector<Cell>> theGrid;
	int startLevel;
	Level * theLevel;
	std::unique_ptr<Score> theScore;
	std::vector<Block *> setBlocks;
	Block *currentBlock = nullptr;
	Block * hintBlock;
	Block *nextBlock = nullptr;
	TextDisplay *td = nullptr;
	Observer<Info> *ob;

	bool isRandom;
	void updateDisplays();
	bool isValidMove(Block *, int, int);
	bool isValidMove(int, int);
	void attachGridToBlock(Block *);
	int countCompleteLines();
	bool isFilled(std::vector<Cell>);
	void updateCells(Block *b, BlockType blocktype, StateType state, bool shouldNotify);

	double calculateSmoothness();
	double getAverageHeights(std::vector<int> v);
	double getStandardDeviationHeights(std::vector<int> v);
	std::vector<int> getHeights();
	int countHoles();
	void moveTo(int, int, Block*);
	double calculateDensity();
	double calculatePriority();
	int getBumpiness();
	int countNumCellsOnWall();
	int countNumCellsOnGround();
	std::vector<Cell> getHintCells(Block *b, HintInfo i);

public:
	Grid(int startLevel, int seed, Observer<Info> *, std::string);
	std::vector<std::vector<Cell>> getGridCells();
	Block *getNextBlock();

	~Grid();
	int getLevel();
	void initGrid();
	bool isOver();
	void deleteRow();
	void deleteCurrentBlock();
	void left(int);
	void right(int);
	void down(int);
	void drop(int);
	void restart();
	void rotateCW(int);
	void rotateCCW(int);
	void levelUp(int);
	void levelDown(int);
	void random(bool);
	void hint();
	void replaceBlock(char);
	void dropBlock(Block *, int);
	void heavyMove();
	void setRandomFile(std::string);
	void playBlock(Block *);

	friend std::ostream &operator<<(std::ostream &out, Grid &grid);
};

#endif

