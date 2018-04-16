#ifndef _ECS_UTIL_H_
#define _ECS_UTIL_H_

#include <bits/stdc++.h>
#include <ctime>
#include "Date.h"

using namespace std;

struct Time {
	int hour;
	int min;
	int sec;
	Time(int h, int m, int s) : hour(h), min(m), sec(s) {}
};

struct Request {
	Request(int f, int y, int m, int d)
		: flavor(f), date(y, m, d) {}
	int flavor;
	Date date;
};

struct ECS {
	int flavor;
	int cpu;
	int mem;
	static unordered_map<int, int> flavor2index;
	static unordered_map<int, int> index2flavor;
	ECS(int f, int c, int m) : flavor(f), cpu(c), mem(m) {}
};

struct Server {
	int cpu;
	int mem;
	int disk;
	Server() {}
	Server(int c, int m, int d) : cpu(c), mem(m), disk(d) {}
};

class TimeUtil {
public:
	static int getCurrentTimeMs() {
		return static_cast<int>(clock()) / (CLOCKS_PER_SEC / kMillisecondPerSecond);
	} 
protected:
	static const int kMillisecondPerSecond = 1000;
};

template <typename T>
ostream& operator<<(ostream& os, const vector<T>& v) {
	for (int i = 0; i < v.size(); ++i) {
		i == 0 ? os << v[i] : os << ' ' << v[i];
	}
	return os;
}

template <typename T1, typename T2>
ostream& operator<<(ostream& os, const pair<T1, T2>& p) {
	os << "[" << p.first << ":" << p.second << "] "; 
	return os;
}

ostream& operator<<(ostream& os, const Request& r);
ostream& operator<<(ostream& os, const ECS& e);

extern const vector<vector<int>> kEcsSwapEquationTbls;
extern const vector<vector<pair<int, int>>> kEcsFlavorInfoTbls;
extern const vector<int> kSwapFirstIndex;
bool operator-(vector<int>& v1, const vector<int>& v2);
bool operator+(vector<int>& v1, const vector<int>& v2);

extern vector<vector<int>> Values;

inline pair<int, int> getEcsFlavorIndex(int flavor) { return pair<int, int>((flavor-1)%3, (flavor-1)/3); }

inline int getFlavorNum(int i, int j) { return j * 3 + i + 1; }

inline int biggestEcs(const vector<int>& v) {
	for (int i = v.size()-1; i >= 0; --i) {
		if (v[i] != 0) return i;
	}
	return -1;
}

inline int smallestEcs(const vector<int>& v) {
	for (int i = 0; i < v.size(); ++i) {
		if (v[i] != 0) return i;
	}
	return -1;
}

#endif // _ECS_UTIL_H_

