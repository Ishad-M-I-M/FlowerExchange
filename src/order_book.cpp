
#include "order_book.h"

#include <utility>

using namespace std;
order_book::order_book(string name) {
    this->name = std::move(name);
}

string order_book::get_name() {
    return this->name;
}

utils::execution order_book::insert(int order_id, utils::order order) {
    utils::execution new_order_exec = {
            "ord"+ to_string(order_id),
            order.client_order_id,
            order.instrument,
            order.side,
            0, // refers to new status
            order.quantity,
            order.price,
            ""
    };
    remaining.push_back(new_order_exec);
    if (order.side == 1) {
        this->left.push_back({
           new_order_exec.order_id,
           new_order_exec.quantity,
           new_order_exec.price
        });
    } else {
        this->right.push_back({
            new_order_exec.order_id,
            new_order_exec.quantity,
            new_order_exec.price
        });
    }
    return new_order_exec;
}


