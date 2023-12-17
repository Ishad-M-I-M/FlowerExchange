
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
        int side;
        int quantity;
        double price;
    };

    struct execution {
        string order_id;
        string client_order_id;
        string instrument;
        int side;
        int status;
        int quantity;
        double price;
        string reason;
    };

    static vector<order> readOrderFile(const string& path);
    static void writeExecutionReport(const vector<execution>& executions, const string& path);

private:
    static string get_status(int status);
};


#endif //FLOWEREXCHANGE_UTILS_H
