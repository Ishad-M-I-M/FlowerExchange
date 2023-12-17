
#ifndef FLOWEREXCHANGE_EXCHANGE_APPLICATION_H
#define FLOWEREXCHANGE_EXCHANGE_APPLICATION_H

#include "./order_book.h"
#include "./utils.h"
#include <string>
#include <unordered_set>
#include <unordered_map>

using std::string;
using std::vector;
using std::unordered_set;
using std::unordered_map;

class exchange_application {
public:
    static unordered_set<string> flowers;
    explicit exchange_application(const vector<utils::order>& orders);
    vector<utils::execution> get_executions();
    static utils::execution validate_order(int order_id, const utils::order& order);
private:
    unordered_map<string, order_book> order_book_map;
    vector<utils::execution> executions;
    void insert_executions(const vector<utils::execution>& execution_list);
};


#endif //FLOWEREXCHANGE_EXCHANGE_APPLICATION_H
