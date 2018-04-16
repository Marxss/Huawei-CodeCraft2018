#include "Model.h"

void Model::init() {
	int firstDateTrain = requests_[0].date.julianDayNumber();
	for (int i = 0; i < requests_.size(); ++i) {
		int date = requests_[i].date.julianDayNumber()-firstDateTrain;
		while (trainData_.size() <= date) {
			trainData_.push_back(vector<int>(Reader::maxFlavor));
			trainData_[trainData_.size()-1][0] = requests_[i].date.julianDayNumber();
		}
		trainData_[date][requests_[i].flavor]++;
	}
	cout << trainData_.size() << endl;
	for (int i = 0; i < trainData_.size(); ++i) {
	}
}

vector<pair<int, int>> Model::predict(Date start, Date end) {
	vector<pair<int, int>> ret;
	vector<int> res(ECS::flavor2index.size());
	int durationOfDays = end.julianDayNumber() - start.julianDayNumber();
	
	for (int i = trainData_.size()-1; i > trainData_.size()-1-durationOfDays; --i) {
		for (int j = 0; j < trainData_[i].size(); ++j) {
			if (trainData_[i][j] != 0 && ECS::flavor2index.find(j) != ECS::flavor2index.end()) {
				int index = ECS::flavor2index[j];
				res[index] += trainData_[i][j];
			}
		}
	}
	for (int i = 0; i < res.size(); ++i) {
		ret.push_back(make_pair(ECS::index2flavor[i], res[i]));
	}
	return ret;
}

/* 237.188分 方案
res[index] += int(0.5+0.717*static_cast<double>(trainData_[i][j])
+0.3*static_cast<double>(trainData_[i-durationOfDays][j])
+0.24*static_cast<double>(trainData_[i-durationOfDays][j]));
*/
vector<pair<int, int>> Model::predict2(Date start, Date end) {
	vector<pair<int, int>> ret;
	vector<double> res(ECS::flavor2index.size());
	int durationOfDays = end.julianDayNumber() - start.julianDayNumber();
    for (int i = trainData_.size()-1; i > trainData_.size()-1-durationOfDays; --i) {
        for (int j = 0; j < trainData_[i].size(); ++j) {
            if (trainData_[i][j] != 0 && ECS::flavor2index.find(j) != ECS::flavor2index.end()) {
                int index = ECS::flavor2index[j];
                res[index] += int(0.5+0.717*static_cast<double>(trainData_[i][j])
                                  +0.3*static_cast<double>(trainData_[i-durationOfDays][j])
                                  +0.24*static_cast<double>(trainData_[i-durationOfDays][j]));
            }
        }
    }
	for (int i = 0; i < res.size(); ++i) {
		ret.push_back(make_pair(ECS::index2flavor[i], int(res[i])));
	}
	return ret;
}