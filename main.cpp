#include <iostream>

#include "src/utils.h"
int main(int argc, char** argv) {
    vector<utils::order> orders = utils::readOrderFile(argv[1]);
    cout << "Hello" <<endl;
}
