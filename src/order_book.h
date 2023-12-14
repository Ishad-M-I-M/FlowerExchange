
#ifndef FLOWEREXCHANGE_ORDER_BOOK_H
#define FLOWEREXCHANGE_ORDER_BOOK_H

#include <string>
#include <vector>

#include "utils.h"

using namespace std;
class order_book {
public:
    order_book(string name);

    string get_name();
    utils::execution insert(int order_id, utils::order order);
private:
    struct entry {
        string order_id;
        int quantity;
        double price;
    };
    string name;

    vector<utils::execution> remaining;
    vector<entry> left;
    vector<entry> right;
};


#endif //FLOWEREXCHANGE_ORDER_BOOK_H
