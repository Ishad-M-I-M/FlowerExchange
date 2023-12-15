#include <iostream>
#include <filesystem>

#include "src/utils.h"
#include "src/exchange_application.h"

using namespace std;
int main(int argc, char** argv) {
    if (argc != 2){
        cerr << "Invalid input. Command format: FlowerExchangeApp <order-csv>"<<endl;
        exit(1);
    }
    vector<utils::order> orders = utils::readOrderFile(argv[1]);
    exchange_application exchange = exchange_application(orders);
    vector<utils::execution> executions = exchange.get_executions();
    utils::writeExecutionReport(executions, filesystem::current_path().string() + "/execution-report.csv");
}
