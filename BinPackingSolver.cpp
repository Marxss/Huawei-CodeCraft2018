#include "BinPackingSolver.h"

vector<vector<int>> BinPackingSolver::firstFit() {
	int res = 0;
	vector<pair<int, int>> binRemain(items_.size());
	vector<vector<int>> bin(items_.size());
	for (int i = 0; i < items_.size(); ++i) {
		int j;
		for (j = 0; j < res; ++j) {
			if (binRemain[j].first >= items_[i].first && binRemain[j].second >= items_[i].second) {
				binRemain[j].first -= items_[i].first;
				binRemain[j].second -= items_[i].second;
				bin[j].push_back(i);
				break;
			}
		}
		if (j == res) {
			binRemain[res].first = limit_.first - items_[i].first;
			binRemain[res].second = limit_.second - items_[i].second;
			bin[res].push_back(i);
			res++;
		}
	}
	return bin;
}

static vector<int> knapSack(int U, int V, const vector<pair<int, int>>& items) {
	vector<int> ret;
	const int N = items.size();
	vector<vector<vector<int>>> tbl(N+1, vector<vector<int>>(U+1, vector<int>(V+1)));
	for (int i = 0; i <= N; ++i) {
		for (int u = 0; u <= U; ++u) {
			for (int v = 0; v <= V; ++v) {
				if (i == 0 || u == 0 || v == 0) {
					tbl[i][u][v] = 0;
				} else if (items[i-1].first <= u && items[i-1].second <= v) {
					tbl[i][u][v] = max(items[i-1].first+items[i-1].second+tbl[i-1][u-items[i-1].first][v-items[i-1].second], tbl[i-1][u][v]);
				} else {
					tbl[i][u][v] = tbl[i-1][u][v];
				}
			}
		}
	}
	cout << tbl[N][U][V] << endl;
	for (int i = N, u = U, v = V, res = tbl[N][U][V]; i > 0 && res > 0; --i) {
		if (res == tbl[i-1][u][v]) continue;
		else {
			ret.push_back(i-1);
			//res = res - 1;
			//res = res - items[i-1].first;
			//res = res - items[i-1].second;
			res = res - items[i-1].first - items[i-1].second;
			u = u - items[i-1].first;
			v = v - items[i-1].second;
		}
	}
	return ret;
}

vector<vector<int>> BinPackingSolver::knapsack() {
	vector<vector<int>> ret;
    vector<pair<int, int>> itemsRemained(items_);
    vector<int> indexRemained;
    for (int i = 0; i < itemsRemained.size(); ++i) indexRemained.push_back(i);
    cout << indexRemained.size() << endl;
	do {
		vector<int> res = knapSack(limit_.first, limit_.second, itemsRemained);
		vector<int> resIndex;
		cout << res.size() << endl;
		for (int i = 0; i < res.size(); ++i) resIndex.push_back(indexRemained[res[i]]);
		ret.push_back(resIndex);
		int cpu = 0, mem = 0;
		for (int i = 0; i < resIndex.size(); ++i) {
			cpu += items_[resIndex[i]].first;
			mem += items_[resIndex[i]].second;
		}
		cout << "LEFT: " << limit_.first-cpu << ", " << limit_.second-mem << endl;
		set<int> removed(res.begin(), res.end());
		vector<pair<int, int>> itemsbackup;
		vector<int> indexbackup;
		for (int i = 0; i < itemsRemained.size(); ++i) {
			if (removed.find(i) != removed.end()) continue;
			itemsbackup.push_back(itemsRemained[i]);
			indexbackup.push_back(indexRemained[i]);
		}
		removed.clear();
		itemsRemained = itemsbackup;
		indexRemained = indexbackup;
	} while (!itemsRemained.empty());
	return ret;
}


vector<vector<int>> solveKnapsack(int U, int V) {
	vector<vector<int>> retValue(3, vector<int>(5, 0));
	vector<int> ecs;
	
	for (int i = 0; i < Values.size(); ++i) {
		for (int j = 0; j < Values[i].size(); ++j) {
			for (int k = 0; k < Values[i][j]; ++k) {
				ecs.push_back(getFlavorNum(i, j));
			}
		}
	}

	const int N = ecs.size();
	vector<vector<vector<int>>> tbl(N+1, vector<vector<int>>(U+1, vector<int>(V+1)));
	for (int i = 0; i <= N; ++i) {
		for (int u = 0; u <= U; ++u) {
			for (int v = 0; v <= V; ++v) {
				if (i == 0 || u == 0 || v == 0) {
					tbl[i][u][v] = 0;
				} else {
					auto p = getEcsFlavorIndex(ecs[i-1]);
					int cpu = kEcsFlavorInfoTbls[p.first][p.second].first;
					int mem = kEcsFlavorInfoTbls[p.first][p.second].second;
					if (cpu <= u && mem <= v) {
						tbl[i][u][v] = max(cpu+mem+tbl[i-1][u-cpu][v-mem], tbl[i-1][u][v]);
					} else {
						tbl[i][u][v] = tbl[i-1][u][v];
					}
				}
			}
		}
	}
	for (int i = N, u = U, v = V, res = tbl[N][U][V]; i > 0 && res > 0; --i) {
		if (res == tbl[i-1][u][v]) continue;
		else {
			auto p = getEcsFlavorIndex(ecs[i-1]);
			int cpu = kEcsFlavorInfoTbls[p.first][p.second].first;
			int mem = kEcsFlavorInfoTbls[p.first][p.second].second;
			retValue[p.first][p.second]++;
			res = res - cpu - mem;
			u = u - cpu;
			v = v - mem;
		}
	}
	return retValue;
}


vector<vector<vector<int>>> solveBinPacking(int U, int V) {
	vector<vector<vector<int>>> retBins;
	vector<vector<int>> vectorZeros{{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0}};
	while (true) {
		if (Values == vectorZeros) break;
		vector<vector<int>> ecsSelected = solveKnapsack(U, V);

		for (int i = 0; i < 3; ++i) {
			if (Values[i] - ecsSelected[i] == false) {
				cout << "Error: " << endl;
				return retBins;
			}

		Begin:
			int pos = biggestEcs(Values[i]);
			if (pos > smallestEcs(ecsSelected[i])) {
				for (int j = kSwapFirstIndex[pos]; j < kEcsSwapEquationTbls.size(); ++j) {
					if (ecsSelected[i] - kEcsSwapEquationTbls[j]) {
						Values[i] + kEcsSwapEquationTbls[j];
						goto Begin;
					}
				}
			}
		}
		retBins.push_back(ecsSelected);
	}
	return retBins;
}




