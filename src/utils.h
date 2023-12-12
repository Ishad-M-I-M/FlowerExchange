
#ifndef FLOWEREXCHANGE_UTILS_H
#define FLOWEREXCHANGE_UTILS_H

#include <string>
#include <vector>

using namespace std;

class utils {
public:
    struct order {
        string client_order_id;
        string instrument;
        int side;
        double price;
        int quantity;
    };

    static vector<order> readOrderFile(string path);
};


#endif //FLOWEREXCHANGE_UTILS_H
