#ifndef GRID_H
#define GRID_H

#include <vector>
#include <memory>
#include "textDisplay.h"
#include "cell.h"
#include "level.h"
#include "score.h"
#include "block.h"

struct HintInfo;
template <typename InfoType> class Observer;

class Grid {
	std::vector<std::vector<Cell>> theGrid;
	int startLevel;
	Level * theLevel;
	std::unique_ptr<Score> theScore;
	std::vector<std::shared_ptr<Block>> setBlocks;
	std::shared_ptr<Block> currentBlock;
	std::shared_ptr<Block> nextBlock;
	std::shared_ptr<Block> hintBlock;
	std::shared_ptr<TextDisplay> td;
	Observer<Info> *ob;

	bool isRandom;
	void updateDisplays();
	bool isValidMove(std::shared_ptr<Block>& , int, int);
	bool isValidMove(int, int);
	void attachGridToBlock(std::shared_ptr<Block> &);
	int countCompleteLines();
	bool isFilled(std::vector<Cell>);
	void updateCells(std::shared_ptr<Block> &b, BlockType blocktype, StateType state, bool shouldNotify);

	double calculateSmoothness();
	double getAverageHeights(std::vector<int> v);
	double getStandardDeviationHeights(std::vector<int> v);
	std::vector<int> getHeights();
	int countHoles();
	void moveTo(int, int, std::shared_ptr<Block> &);
	double calculateDensity();
	double calculatePriority();
	int getBumpiness();
	int countNumCellsOnWall();
	int countNumCellsOnGround();
	std::vector<Cell> getHintCells(std::shared_ptr<Block> &b, HintInfo i);

public:
	Grid(int startLevel, int seed, Observer<Info> *, std::string);
	std::vector<std::vector<Cell>> getGridCells();
	std::shared_ptr<Block> getNextBlock();
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
	void dropBlock(std::shared_ptr<Block>, int);
	void heavyMove();
	void setRandomFile(std::string);
	void playBlock(std::shared_ptr<Block> &);

	friend std::ostream &operator<<(std::ostream &out, Grid &grid);
};

#endif

