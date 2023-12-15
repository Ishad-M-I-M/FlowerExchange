
#ifndef FLOWEREXCHANGE_EXCHANGE_APPLICATION_H
#define FLOWEREXCHANGE_EXCHANGE_APPLICATION_H

#include "./order_book.h"
#include "./utils.h"
#include <string>
#include <unordered_set>
#include <unordered_map>

using namespace std;
class exchange_application {
public:
    static unordered_set<string> flowers;
    explicit exchange_application(vector<utils::order> orders);
    vector<utils::execution> get_executions();
    static utils::execution validate_order(int order_id, utils::order order);
private:
    unordered_map<string, order_book> order_book_map;
    vector<utils::execution> executions;
    void insert_executions(vector<utils::execution> executions);
};


#endif //FLOWEREXCHANGE_EXCHANGE_APPLICATION_H
