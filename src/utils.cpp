
#include "utils.h"

#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
#include <iomanip>


vector<utils::order> utils::readOrderFile(const string& path) {
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

        string client_order_id;
        string instrument;
        int side;
        int quantity;
        double price;

        getline(ss, client_order_id, ',');
        getline(ss, instrument, ',');

        getline(ss, token, ',');
        side = stoi(token);

        getline(ss, token, ',');
        quantity = stoi(token);

        ss >> price;
        orders.emplace_back(client_order_id, instrument, side, quantity, price);
    }

    file.close();

    return orders;
}

void utils::writeExecutionReport(const vector<execution>& executions, const string& path) {
    std::ofstream file(path);
    if (!file.is_open()){
        std::cerr << "Cannot open file: " << path << std::endl;
        throw std::runtime_error("File open failed");
    }
    int row = 0;

    file << "Order ID,Client Order ID,Instrument,Side,Exec Status,Quantity,Price,Reason" << std::endl;
    for (const execution exec: executions){
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
