
#include "order_book.h"

#include <utility>
#include <algorithm>


order_book::order_book() = default;

order_book::order_book(string name) {
    this->name = std::move(name);
}

string order_book::get_name() {
    return this->name;
}

vector<utils::execution> order_book::insert(int order_id, utils::order order) {
    entry e = {
            "ord" + std::to_string(order_id),
            order.client_order_id,
            order.quantity,
            order.price
    };

    return execute(e, order.side);
}

void order_book::insert_buy_order(entry e) {
    auto index = upper_bound(buy_orders.begin(), buy_orders.end(), e, compare_buy_orders);
    buy_orders.insert(index, e);
}

void order_book::insert_sell_order(entry e) {
    auto index = upper_bound(sell_orders.begin(), sell_orders.end(), e, compare_sell_orders);
    sell_orders.insert(index, e);
}

bool order_book::compare_buy_orders(const entry a, const entry b) {
    return a.price > b.price;
}

bool order_book::compare_sell_orders(const entry a, const entry b) {
    return a.price < b.price;
}

vector<utils::execution> order_book::execute(order_book::entry e, int side) {
    vector<utils::execution> executions;
    int initial_quantity = e.quantity;
    if (side == 1) {
        for (int i = 0; i < sell_orders.size(); i++) {
            if (sell_orders[i].price > e.price) {
                break;
            }
            if (sell_orders[i].quantity >= e.quantity) {
                // execution entry for the order received
                executions.push_back({
                                             e.order_id,
                                             e.client_order_id,
                                             this->name,
                                             side,
                                             2, // refers to FILL
                                             e.quantity,
                                             sell_orders[i].price,
                                             ""
                                     });

                // execution entry for matching order book entry
                int status;
                if (sell_orders[i].quantity == e.quantity) status = 2;
                else status = 3;

                executions.push_back({
                                             sell_orders[i].order_id,
                                             sell_orders[i].client_order_id,
                                             this->name,
                                             2,
                                             status,
                                             e.quantity,
                                             sell_orders[i].price,
                                             ""
                                     });
                e.quantity = 0;
                if (sell_orders[i].quantity == e.quantity) sell_orders.erase(sell_orders.begin() + i);
                else sell_orders[i].quantity -= e.quantity;
            } else {
                // execution entry for the order received
                executions.push_back({
                                             e.order_id,
                                             e.client_order_id,
                                             this->name,
                                             side,
                                             3, // refers to PFILL
                                             sell_orders[i].quantity,
                                             sell_orders[i].price,
                                             ""
                                     });

                e.quantity -= sell_orders[i].quantity;
                // execution entry for matching order book entry
                executions.push_back({
                                             sell_orders[i].order_id,
                                             sell_orders[i].client_order_id,
                                             this->name,
                                             2,
                                             2,
                                             sell_orders[i].quantity,
                                             sell_orders[i].price,
                                             ""
                                     });
            }
        }
        // enter the entry to the order book
        if (e.quantity != 0) insert_buy_order(e);
    } else {
        for (int i = 0; i < buy_orders.size(); i++) {
            if (buy_orders[i].price < e.price) {
                break;
            }
            if (buy_orders[i].quantity >= e.quantity) {
                // execution entry for the order received
                executions.push_back({
                                             e.order_id,
                                             e.client_order_id,
                                             this->name,
                                             side,
                                             2, // refers to FILL
                                             e.quantity,
                                             buy_orders[i].price,
                                             ""
                                     });

                // execution entry for matching order book entry
                int status;
                if (buy_orders[i].quantity == e.quantity) status = 2;
                else status = 3;

                executions.push_back({
                                             buy_orders[i].order_id,
                                             buy_orders[i].client_order_id,
                                             this->name,
                                             1,
                                             status,
                                             e.quantity,
                                             buy_orders[i].price,
                                             ""
                                     });

                e.quantity = 0;
                if (buy_orders[i].quantity == e.quantity) buy_orders.erase(buy_orders.begin() + i);
                else buy_orders[i].quantity -= e.quantity;
            } else {
                // execution entry for the order received
                executions.push_back({
                                             e.order_id,
                                             e.client_order_id,
                                             this->name,
                                             side,
                                             3, // refers to PFILL
                                             buy_orders[i].quantity,
                                             buy_orders[i].price,
                                             ""
                                     });

                e.quantity -= buy_orders[i].quantity;
                // execution entry for matching order book entry
                executions.push_back({
                                             buy_orders[i].order_id,
                                             buy_orders[i].client_order_id,
                                             this->name,
                                             1,
                                             2,
                                             buy_orders[i].quantity,
                                             buy_orders[i].price,
                                             ""
                                     });
            }
        }
        // enter the entry to the order book
        if (e.quantity != 0) insert_sell_order(e);
    }

    if (initial_quantity == e.quantity) {
        utils::execution new_order_exec = {
                e.order_id,
                e.client_order_id,
                this->name,
                side,
                0, // refers to new status
                e.quantity,
                e.price,
                ""
        };
        executions.push_back(new_order_exec);
    }
    return executions;
}
