
#include "utils.h"

#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
#include <iomanip>


vector<utils::order> utils::readOrderFile(string path) {
    std::ifstream file(path);
    if (!file.is_open()){
        std::cerr << "Cannot open file: " << path << std::endl;
        throw std::runtime_error("File open failed");
    }

    vector<order> orders;

    string line;
    getline(file, line);
    while (getline(file, line)) {
        std::istringstream ss(line);
        string token;

        order currentOrder;

        getline(ss, currentOrder.client_order_id, ',');
        getline(ss, currentOrder.instrument, ',');

        getline(ss, token, ',');
        currentOrder.side = stoi(token);

        getline(ss, token, ',');
        currentOrder.quantity = stoi(token);

        ss >> currentOrder.price;
        orders.push_back(currentOrder);
    }

    file.close();

    return orders;
}

void utils::writeExecutionReport(vector<execution> executions, string path) {
    std::ofstream file(path);
    if (!file.is_open()){
        std::cerr << "Cannot open file: " << path << std::endl;
        throw std::runtime_error("File open failed");
    }
    int row = 0;

    file << "Order ID,Client Order ID,Instrument,Side,Exec Status,Quantity,Price,Reason" << std::endl;
    for (execution exec: executions){
        row++;
        file << exec.order_id << ","
            << exec.client_order_id << ","
            << exec.instrument << ","
            << exec.side << ","
            << get_status(exec.status) << ","
            << exec.quantity << ","
            << std::fixed << std::setprecision(2) << exec.price << ","
            << exec.reason;
        if (row != executions.size()){
            file << std::endl;
        }
    }

    file.close();
}

string utils::get_status(int status) {
    switch (status) {
        case 0: return "New";
        case 1: return "Rejected";
        case 2: return "Fill";
        case 3: return "Pfill";
        default: return "Error";
    }
}
