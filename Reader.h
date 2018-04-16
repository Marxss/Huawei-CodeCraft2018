#ifndef _ECS_READER_H_
#define _ECS_READER_H_

#include "Util.h"


class Reader {
public:
	Reader() {}
	vector<Request> readTrainData(char* info[], int dataNum);
	vector<ECS> readInputData(char* data[], Server& server, Date& start, Date& end);
	static int maxFlavor;
};



#endif // _ECS_READER_H_
