#ifndef _BIN_PACKING_SOLVER_
#define _BIN_PACKING_SOLVER_

#include "Util.h"

class BinPackingSolver {
public:
	BinPackingSolver(const vector<pair<int, int>>& items, const pair<int, int>& limit)
		: items_(items), limit_(limit) {}
	
	vector<vector<int>> firstFit();
	vector<vector<int>> knapsack();
	
private:
	const vector<pair<int, int>>& items_;
	const pair<int, int>& limit_;
};

extern vector<vector<vector<int>>> solveBinPacking(int U, int V);
extern vector<vector<int>> solveKnapsack(int U, int V);

#endif // _BIN_PACKING_SOLVER_

