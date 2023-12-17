
#ifndef FLOWEREXCHANGE_UTILS_H
#define FLOWEREXCHANGE_UTILS_H

#include <string>
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
        order(const string& client_order_id, const string& instrument, int side, int quantity, double price){
            this->client_order_id = client_order_id;
            this->instrument = instrument;
            this->side = side;
            this->quantity = quantity;
            this->price = price;
        }
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
        execution(const string& order_id, const string& client_order_id, const string& instrument,
                  int side, int status, int quantity, double price, const string& reason) {
            this->order_id = order_id;
            this->client_order_id = client_order_id;
            this->instrument = instrument;
            this->status = status;
            this->side = side;
            this->quantity = quantity;
            this->price = price;
            this->reason = reason;
        };
    };

    static vector<order> readOrderFile(const string& path);
    static void writeExecutionReport(const vector<execution>& executions, const string& path);

private:
    static string get_status(int status);
};


#endif //FLOWEREXCHANGE_UTILS_H
