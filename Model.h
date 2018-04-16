#ifndef _MODEL_H_
#define _MODEL_H_

#include "Reader.h"

class Model {
public:
	Model(const vector<Request>& request) : requests_(request) {}
	void init();
	void train();
	vector<pair<int, int>> predict(Date start, Date end);
	vector<pair<int, int>> predict2(Date start, Date end);
private:
	const vector<Request>& requests_;
	vector<vector<int>> trainData_;
};

#endif // _MODEL_H_

