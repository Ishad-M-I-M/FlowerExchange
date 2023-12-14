
#ifndef FLOWEREXCHANGE_EXCHANGE_APPLICATION_H
#define FLOWEREXCHANGE_EXCHANGE_APPLICATION_H

#include "./order_book.h"
#include "./utils.h"
#include <string>
#include <unordered_set>

using namespace std;
class exchange_application {
public:
    static unordered_set<string> flowers;
    vector<utils::order> orders;
    vector<utils::execution> executions;
    explicit exchange_application(vector<utils::order> orders);
    static utils::execution validate_order(int order_id, utils::order order);
};


#endif //FLOWEREXCHANGE_EXCHANGE_APPLICATION_H
