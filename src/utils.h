
#ifndef FLOWEREXCHANGE_UTILS_H
#define FLOWEREXCHANGE_UTILS_H

#include <string>
#include <utility>
#include <vector>

using std::string;
using std::vector;

class utils {
public:
    struct order {
        string client_order_id;
        string instrument;
        int side{};
        int quantity{};
        double price{};
        order(string client_order_id, string instrument, int side, int quantity, double price):
        client_order_id(std::move(client_order_id)),
        instrument(std::move(instrument)),
        side(side),
        quantity(quantity),
        price(price)
        {}
    };

    struct execution {
        string order_id;
        string client_order_id;
        string instrument;
        int side{};
        int status{};
        int quantity{};
        double price{};
        string reason;
        execution(string order_id, string client_order_id, string instrument,
                  int side, int status, int quantity, double price, string reason):
                  order_id(std::move(order_id)),
                  client_order_id(std::move(client_order_id)),
                  instrument(std::move(instrument)),
                  side(side),
                  status(status),
                  quantity(quantity),
                  price(price),
                  reason(std::move(reason)){}
    };

    static vector<order> readOrderFile(const string& path);
    static void writeExecutionReport(const vector<execution>& executions, const string& path);

private:
    static string get_status(int status);
};


#endif //FLOWEREXCHANGE_UTILS_H
