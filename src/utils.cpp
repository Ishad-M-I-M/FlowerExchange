
#include "utils.h"

#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>

using namespace std;
vector<utils::order> utils::readOrderFile(string path) {
    ifstream file(path);
    if (!file.is_open()){
        cerr << "Cannot open file: " << path << endl;
    }

    vector<order> orders;

    string line;
    getline(file, line);
    while (getline(file, line)) {
        istringstream ss(line);
        string token;

        order currentOrder;

        getline(ss, currentOrder.client_order_id, ',');
        getline(ss, currentOrder.instrument, ',');

        getline(ss, token, ',');
        currentOrder.side = stoi(token);

        getline(ss, token, ',');
        currentOrder.price = stod(token);

        ss >> currentOrder.quantity;

        orders.push_back(currentOrder);
    }

    file.close();

    return orders;
}
