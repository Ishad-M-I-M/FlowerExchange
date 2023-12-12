
#include <fstream>
#include "gtest/gtest.h"

#include "../src/utils.h"

using namespace std;

TEST(UtilsTest, TestReadOrderFile){
    vector<utils::order> orders_1 = {
            {"aa13", "Rose", 1, 50, 55},
            {"aa14", "Rose", 2, 50, 55}
    };

    vector<utils::order> actual = utils::readOrderFile(TEST_RESOURCE_DIR"/orders_1.csv");
    ASSERT_EQ(actual.size(), orders_1.size());

    for(int i = 0; i < orders_1.size(); i++){
        ASSERT_EQ(orders_1[i].client_order_id, actual[i].client_order_id);
        ASSERT_EQ(orders_1[i].instrument, actual[i].instrument);
        ASSERT_EQ(orders_1[i].side, actual[i].side);
        ASSERT_EQ(orders_1[i].price, actual[i].price);
        ASSERT_EQ(orders_1[i].quantity, actual[i].quantity);
    }
}