
#include "exchange_application.h"
unordered_set<string> exchange_application::flowers = {"Rose", "Lavender", "Lotus", "Tulip", "Orchid"};
exchange_application::exchange_application(vector<utils::order> orders) {
    this->orders = orders;
}

utils::execution exchange_application::validate_order(int order_id, utils::order order) {
    string reason;
    if (order.client_order_id == "") reason="Empty client order id";
    else if (flowers.find(order.instrument) == flowers.end() ) reason = "Invalid instrument";
    else if (order.side != 1 && order.side != 2) reason = "Invalid side";
    else if (order.price <= 0) reason = "Invalid price";
    else if (order.quantity % 10 != 0 || order.quantity < 10 || order.quantity > 1000) reason = "Invalid quantity";
    else reason = "";
    return {
        "ord"+ to_string(order_id),
        order.client_order_id,
        order.instrument,
        order.side,
        1,
        order.quantity,
        order.price,
        reason
    };
}
