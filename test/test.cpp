
#include <fstream>
#include "gtest/gtest.h"

#include "../src/utils.h"
#include "../src/order_book.h"

using namespace std;

TEST(UtilsTest, TestReadOrderFile){
    vector<utils::order> orders_1 = {
            {"aa13", "Rose", 2, 100, 55.00}
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

TEST(UtilsTest, TestWriteExcutionReport) {
    vector<utils::execution> executions_1 = {
            {"ord1", "aa13", "Rose", 2, 0, 100, 55.00}
    };

    utils::writeExecutionReport(executions_1, TEST_RESOURCE_DIR"/temp/execution_rep_1.csv");

    ifstream actual(TEST_RESOURCE_DIR"/temp/execution_rep_1.csv");
    ifstream expected(TEST_RESOURCE_DIR"/execution_rep_1.csv");

    ASSERT_TRUE(actual.is_open());

    stringstream buffer1;
    buffer1 << actual.rdbuf();
    string actualContent = buffer1.str();

    stringstream buffer2;
    buffer2 << expected.rdbuf();
    string expectedContent = buffer2.str();

    actual.close();
    expected.close();

    ASSERT_EQ(actualContent, expectedContent);
}
TEST(OrderBookTest, TestConstructor) {
    order_book* orderBook = new order_book("Rose");
    ASSERT_EQ(orderBook->get_name(), "Rose");
}

TEST(OrderBookTest, TestInsert) {
    order_book* orderBook = new order_book("Rose");
    utils::execution insertExecution = orderBook->insert(1, {
        "aa13",
        "Rose",
        2,
        100,
        55.0
    });

    ASSERT_EQ(insertExecution.order_id, "ord1");
    ASSERT_EQ(insertExecution.client_order_id, "aa13");
    ASSERT_EQ(insertExecution.side, 2);
    ASSERT_EQ(insertExecution.quantity, 100);
    ASSERT_EQ(insertExecution.price, 55.0);
    ASSERT_EQ(insertExecution.status, 0);
    ASSERT_EQ(insertExecution.reason, "");
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}