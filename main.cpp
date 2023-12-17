#include <iostream>
#include <filesystem>

#include "src/utils.h"
#include "src/exchange_application.h"

using std::string;
using std::vector;
using std::cerr;
using std::endl;

int main(int argc, char** argv) {
    if (argc != 2){
        cerr << "Invalid input. Command format: FlowerExchangeApp <order-csv>"<<endl;
        exit(1);
    }
    vector<utils::order> orders = utils::readOrderFile(argv[1]);
    auto exchange = exchange_application(orders);
    vector<utils::execution> executions = exchange.get_executions();
    utils::writeExecutionReport(executions, std::filesystem::current_path().string() + "/execution-report.csv");
}
