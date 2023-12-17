
#include "exchange_application.h"
unordered_set<string> exchange_application::flowers = {"Rose", "Lavender", "Lotus", "Tulip", "Orchid"};
exchange_application::exchange_application(const vector<utils::order>& orders) {
    for (const string& flower: flowers){
        order_book_map[flower] = order_book(flower);
    }

    int order_num = 1;
    for (const utils::order& order : orders){
        utils::execution validation = validate_order(order_num, order);
        if (validation.reason.empty()){
            insert_executions(order_book_map[order.instrument].insert(order_num,order));
        } else {
            this->executions.push_back(validation);
        }
        order_num++;
    }
}

utils::execution exchange_application::validate_order(int order_id, const utils::order& order) {
    const char *reason;
    if (order.client_order_id.empty()) reason="Empty client order id";
    else if (flowers.find(order.instrument) == flowers.end() ) reason = "Invalid instrument";
    else if (order.side != 1 && order.side != 2) reason = "Invalid side";
    else if (order.price <= 0) reason = "Invalid price";
    else if (order.quantity % 10 != 0 || order.quantity < 10 || order.quantity > 1000) reason = "Invalid quantity";
    else reason = "";
    return utils::execution(
        "ord"+ std::to_string(order_id),
        order.client_order_id,
        order.instrument,
        order.side,
        1,
        order.quantity,
        order.price,
        reason
    );
}

void exchange_application::insert_executions(const vector<utils::execution>& execution_list) {
    for (const utils::execution& execution: execution_list){
        this->executions.push_back(execution);
    }
}

vector<utils::execution> exchange_application::get_executions() {
    return this->executions;
}
