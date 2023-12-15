
#ifndef FLOWEREXCHANGE_ORDER_BOOK_H
#define FLOWEREXCHANGE_ORDER_BOOK_H

#include <string>
#include <vector>

#include "utils.h"

using namespace std;
class order_book {
public:
    order_book();

    order_book(string name);

    string get_name();
    vector<utils::execution> insert(int order_id, utils::order order);

private:
    struct entry {
        string order_id;
        string client_order_id;
        int quantity;
        double price;
    };
    string name;

    vector<entry> buy_orders;
    vector<entry> sell_orders;

    void insert_buy_order(entry e);
    void insert_sell_order(entry e);

    static bool compare_buy_orders(const entry a, const entry b);
    static bool compare_sell_orders(const entry a, const entry b);

    vector<utils::execution> execute(entry e, int side);
};


#endif //FLOWEREXCHANGE_ORDER_BOOK_H
