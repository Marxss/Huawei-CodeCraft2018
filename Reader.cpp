#include "Reader.h"

vector<Request> Reader::readTrainData(char* data[], int dataNum) {
	vector<Request> requests;
	for (int i = 0; i < dataNum; ++i) {
		char strId[32], strFlavor[32], strDate[32], strTime[32];
		sscanf(data[i], "%s\t%s\t%s\t%s\n", strId, strFlavor, strDate, strTime);
		int flavor, year, month, day;
		sscanf(strFlavor+6, "%d", &flavor);
		maxFlavor = max(flavor, maxFlavor);
		sscanf(strDate, "%d-%d-%d", &year, &month, &day);
		requests.push_back(Request(flavor, year, month, day));
	}
	return requests;
}

vector<ECS> Reader::readInputData(char* data[], Server& server, Date& start, Date& end) {
	vector<ECS> ecs;
	int lineCounter = 0;
	sscanf(data[lineCounter++], "%d %d %d\n", &server.cpu, &server.mem, &server.disk);
	lineCounter++;
	int n;
	sscanf(data[lineCounter++], "%d\n", &n);
	for (int i = 0; i < n; ++i) {
		char strFlavor[32];
		int flavor, cpu, mem;
		sscanf(data[lineCounter++], "%s %d %d\n", strFlavor, &cpu, &mem);
		sscanf(strFlavor+6, "%d", &flavor);
		ecs.push_back(ECS(flavor, cpu, mem/1024));
		ECS::flavor2index[flavor] = i;
		ECS::index2flavor[i] = flavor;
	}
	lineCounter++;
	lineCounter++;
	lineCounter++;
	char startDate[32], startTime[32], endDate[32], endTime[32];
	sscanf(data[lineCounter++], "%s %s\n", startDate, startTime);
	sscanf(data[lineCounter++], "%s %s\n", endDate, endTime);
	int year, month, day;
	sscanf(startDate, "%d-%d-%d", &year, &month, &day);
	start = Date(year, month, day);
	sscanf(endDate, "%d-%d-%d", &year, &month, &day);
	end = Date(year, month, day);
	return ecs;
}

int Reader::maxFlavor = INT_MIN;


