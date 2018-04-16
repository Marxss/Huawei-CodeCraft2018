#include "predict.h"
#include "Reader.h"
#include "Model.h"
#include "BinPackingSolver.h"
#include "Util.h"

void predict_server(char * info[MAX_INFO_NUM], char * data[MAX_DATA_NUM], int data_num, char * filename)
{
    Reader reader;

    // Read info
    vector<ECS> ecs;
    Server server;
    Date startDate, endDate;
    ecs = reader.readInputData(info, server, startDate, endDate);
    for (const auto& e : ecs) cout << e << endl;

    // Read train data.
    vector<Request> requests = reader.readTrainData(data, data_num);
    //for (const auto& r : requests) cout << r << endl;

    // for (auto it = ECS::flavor2index.begin(); it != ECS::flavor2index.end(); ++it) {
    // 	cout << it->first << " : " << it->second << endl;
    // }

    Model model(requests);
    model.init();
//	vector<pair<int, int>> predictECS = model.predict(startDate, endDate);
    vector<pair<int, int>> predictECS = model.predict2(startDate, endDate);
    //cout << predictECS << endl;
//
//    for (int i = 0; i<predictECS.size(); ++i) {
//        predictECS[i].second += 1;
//    } 
    
    vector<pair<int, int>> items;
    vector<int> flavors;
    for (const auto& e : predictECS) {
        for (int i = 0; i < e.second; ++i) {
            int flavor = e.first;
            int index = ECS::flavor2index[flavor];
            items.push_back(make_pair(ecs[index].cpu, ecs[index].mem));
            flavors.push_back(flavor);
        }
    }
    for (int i = 0; i < flavors.size(); ++i) {
        auto p = getEcsFlavorIndex(flavors[i]);
        Values[p.first][p.second]++;
    }

    const int U = server.cpu, V = server.mem;
    vector<vector<vector<int>>> bins = solveBinPacking(U, V);


    const int kBufferSize = 4096;
    char buffer[kBufferSize];
    int pos = snprintf(buffer, kBufferSize, "%d\n", flavors.size());
    for (int i = 0; i < predictECS.size(); ++i) {
        pos += snprintf(buffer+pos, kBufferSize-pos, "flavor%d %d\n", predictECS[i].first, predictECS[i].second);
    }
    pos += snprintf(buffer+pos, kBufferSize-pos, "\n");

    int serverNum = 0;
    for (int i = 0; i < bins.size(); ++i) {
        if (!bins[i].empty()) serverNum++;
    }
    pos += snprintf(buffer+pos, kBufferSize-pos, "%d\n", serverNum);

    for (int i = 0; i < bins.size(); ++i) {
        pos += snprintf(buffer+pos, kBufferSize-pos, "%d", i+1);
        for (int j = 0; j < bins[i].size(); ++j) {
            for (int k = 0; k < bins[i][j].size(); ++k) {
                if (bins[i][j][k] != 0) {
                    int flavor = getFlavorNum(j, k);
                    pos += snprintf(buffer+pos, kBufferSize-pos, " flavor%d %d", flavor, bins[i][j][k]);
                }
            }
        }
        pos += snprintf(buffer+pos, kBufferSize-pos, "\n");
    }
    cout << buffer << endl;
    //char * result_file = (char *)"17\n\n0 8 0 20";
    char*result_file = buffer;
    write_result(result_file, filename);
}
