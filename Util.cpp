#include "Util.h"

const vector<vector<int>> kEcsSwapEquationTbls = {
    //1  2  4  8  16
	{16, 0, 0, 0, -1},
	{14, 1, 0, 0, -1},
	{12, 2, 0, 0, -1},
	{12, 0, 1, 0, -1},
	{10, 3, 0, 0, -1},
	{10, 1, 1, 0, -1},
	{ 8, 4, 0, 0, -1},
	{ 8, 2, 1, 0, -1},
	{ 8, 0, 2, 0, -1},
	{ 8, 0, 0, 1, -1},
	{ 6, 5, 0, 0, -1},
	{ 6, 3, 1, 0, -1},
	{ 6, 1, 2, 0, -1},
	{ 6, 1, 0, 1, -1},
	{ 4, 6, 0, 0, -1},
	{ 4, 4, 1, 0, -1},
	{ 4, 2, 2, 0, -1},
	{ 4, 2, 0, 1, -1},
	{ 4, 0, 3, 0, -1},
	{ 4, 0, 1, 1, -1},
	{ 2, 7, 0, 0, -1},
	{ 2, 5, 1, 0, -1},
	{ 2, 3, 2, 0, -1},
	{ 2, 3, 0, 1, -1},
	{ 2, 1, 3, 0, -1},
	{ 2, 1, 1, 1, -1},
	{ 0, 8, 0, 0, -1},
	{ 0, 6, 1, 0, -1},
	{ 0, 4, 2, 0, -1},
	{ 0, 4, 0, 1, -1},
	{ 0, 2, 3, 0, -1},
	{ 0, 2, 1, 1, -1},
	{ 0, 0, 4, 0, -1},
	{ 0, 0, 2, 1, -1},
	{ 0, 0, 0, 2, -1},
	{ 8, 0, 0, -1, 0},
	{ 6, 1, 0, -1, 0},
	{ 4, 2, 0, -1, 0},
	{ 4, 0, 1, -1, 0},
	{ 2, 3, 0, -1, 0},
	{ 2, 1, 1, -1, 0},
	{ 0, 4, 0, -1, 0},
	{ 0, 2, 1, -1, 0},
	{ 0, 0, 2, -1, 0},
	{ 4, 0, -1, 0, 0},
	{ 2, 1, -1, 0, 0},
	{ 0, 2, -1, 0, 0},
	{ 2, -1, 0, 0, 0}	
};

const vector<vector<pair<int, int>>> kEcsFlavorInfoTbls = {
	{ {1,1}, {2,2}, {4, 4}, {8, 8}, {16,16} }, 
	{ {1,2}, {2,4}, {4, 8}, {8,16}, {16,32} },
	{ {1,4}, {2,8}, {4,16}, {8,32}, {16,64} }
};

const vector<int> kSwapFirstIndex = {-1, 47, 44, 35, 0};

vector<vector<int>> Values(3, vector<int>(5, 0));

unordered_map<int, int> ECS::flavor2index;
unordered_map<int, int> ECS::index2flavor;

ostream& operator<<(ostream& os, const Request& r) {
	os << "FLAVOR: " << r.flavor << ", DATE: " << r.date.year() << '-' << r.date.month() << '-' << r.date.day();
	return os;
}

ostream& operator<<(ostream& os, const ECS& e) {
	os << "FLAVOR: " << e.flavor << ", CPU: " << e.cpu << ", MEM: " << e.mem;
	return os;
}

bool operator-(vector<int>& v1, const vector<int>& v2) {
	vector<int> res(v2.size(), 0);
	for (int i = 0; i < v2.size(); ++i) {
		res[i] = v1[i] - v2[i];
		if (res[i] < 0) return false;
	}
	v1 = res;
	return true;
}

bool operator+(vector<int>& v1, const vector<int>& v2) {
	vector<int> res(v2.size(), 0);
	for (int i = 0; i < v2.size(); ++i) {
		res[i] = v1[i] + v2[i];
		if (res[i] < 0) return false;
	}
	v1 = res;
	return true;
}

