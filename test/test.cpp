
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

TEST(OrderBookTest, TestSimpleInsert) {
    order_book* orderBook = new order_book("Rose");
    vector<utils::execution> insertExecutions = orderBook->insert(1, {
            "aa13",
            "Rose",
            2,
            100,
            55.0
    });

    ASSERT_EQ(insertExecutions.size(), 1);
    ASSERT_EQ(insertExecutions[0].order_id, "ord1");
    ASSERT_EQ(insertExecutions[0].client_order_id, "aa13");
    ASSERT_EQ(insertExecutions[0].side, 2);
    ASSERT_EQ(insertExecutions[0].quantity, 100);
    ASSERT_EQ(insertExecutions[0].price, 55.0);
    ASSERT_EQ(insertExecutions[0].status, 0);
    ASSERT_EQ(insertExecutions[0].reason, "");
}
TEST(OrderBookTest, TestSimpleSellBuy) {
    order_book* orderBook = new order_book("Rose");
    vector<utils::execution> insertExecutions = orderBook->insert(1, {
        "aa13",
        "Rose",
        2,
        100,
        55.0
    });

    vector<utils::execution> filled = orderBook->insert(2, {
            "aa14",
            "Rose",
            1,
            100,
            55.0
    });

    ASSERT_EQ(filled.size(), 2);

    ASSERT_EQ(filled[0].order_id, "ord2");
    ASSERT_EQ(filled[0].client_order_id, "aa14");
    ASSERT_EQ(filled[0].side, 1);
    ASSERT_EQ(filled[0].quantity, 100);
    ASSERT_EQ(filled[0].price, 55.0);
    ASSERT_EQ(filled[0].status, 2);
    ASSERT_EQ(filled[0].reason, "");

    ASSERT_EQ(filled[1].order_id, "ord1");
    ASSERT_EQ(filled[1].client_order_id, "aa13");
    ASSERT_EQ(filled[1].side, 2);
    ASSERT_EQ(filled[1].quantity, 100);
    ASSERT_EQ(filled[1].price, 55.0);
    ASSERT_EQ(filled[1].status, 2);
    ASSERT_EQ(filled[1].reason, "");
}

TEST(OrderBookTest, TestSimpleSellBuyPFill) {
    order_book* orderBook = new order_book("Rose");
    vector<utils::execution> insertExecutions = orderBook->insert(1, {
            "aa13",
            "Rose",
            2,
            200,
            55.0
    });

    vector<utils::execution> filled = orderBook->insert(2, {
            "aa14",
            "Rose",
            1,
            100,
            55.0
    });

    ASSERT_EQ(filled.size(), 2);

    ASSERT_EQ(filled[0].order_id, "ord2");
    ASSERT_EQ(filled[0].client_order_id, "aa14");
    ASSERT_EQ(filled[0].side, 1);
    ASSERT_EQ(filled[0].quantity, 100);
    ASSERT_EQ(filled[0].price, 55.0);
    ASSERT_EQ(filled[0].status, 2);
    ASSERT_EQ(filled[0].reason, "");

    ASSERT_EQ(filled[1].order_id, "ord1");
    ASSERT_EQ(filled[1].client_order_id, "aa13");
    ASSERT_EQ(filled[1].side, 2);
    ASSERT_EQ(filled[1].quantity, 100);
    ASSERT_EQ(filled[1].price, 55.0);
    ASSERT_EQ(filled[1].status, 3);
    ASSERT_EQ(filled[1].reason, "");
}

TEST(OrderBookTest, TestSimpleBuySell) {
    order_book* orderBook = new order_book("Rose");
    vector<utils::execution> insertExecutions = orderBook->insert(1, {
            "aa13",
            "Rose",
            1,
            100,
            55.0
    });

    vector<utils::execution> filled = orderBook->insert(2, {
            "aa14",
            "Rose",
            2,
            100,
            55.0
    });

    ASSERT_EQ(filled.size(), 2);

    ASSERT_EQ(filled[0].order_id, "ord2");
    ASSERT_EQ(filled[0].client_order_id, "aa14");
    ASSERT_EQ(filled[0].side, 2);
    ASSERT_EQ(filled[0].quantity, 100);
    ASSERT_EQ(filled[0].price, 55.0);
    ASSERT_EQ(filled[0].status, 2);
    ASSERT_EQ(filled[0].reason, "");

    ASSERT_EQ(filled[1].order_id, "ord1");
    ASSERT_EQ(filled[1].client_order_id, "aa13");
    ASSERT_EQ(filled[1].side, 1);
    ASSERT_EQ(filled[1].quantity, 100);
    ASSERT_EQ(filled[1].price, 55.0);
    ASSERT_EQ(filled[1].status, 2);
    ASSERT_EQ(filled[1].reason, "");
}

TEST(OrderBookTest, TestSimpleBuySellPFill) {
    order_book* orderBook = new order_book("Rose");
    vector<utils::execution> insertExecutions = orderBook->insert(1, {
            "aa13",
            "Rose",
            1,
            200,
            55.0
    });

    vector<utils::execution> filled = orderBook->insert(2, {
            "aa14",
            "Rose",
            2,
            100,
            55.0
    });

    ASSERT_EQ(filled.size(), 2);

    ASSERT_EQ(filled[0].order_id, "ord2");
    ASSERT_EQ(filled[0].client_order_id, "aa14");
    ASSERT_EQ(filled[0].side, 2);
    ASSERT_EQ(filled[0].quantity, 100);
    ASSERT_EQ(filled[0].price, 55.0);
    ASSERT_EQ(filled[0].status, 2);
    ASSERT_EQ(filled[0].reason, "");

    ASSERT_EQ(filled[1].order_id, "ord1");
    ASSERT_EQ(filled[1].client_order_id, "aa13");
    ASSERT_EQ(filled[1].side, 1);
    ASSERT_EQ(filled[1].quantity, 100);
    ASSERT_EQ(filled[1].price, 55.0);
    ASSERT_EQ(filled[1].status, 3);
    ASSERT_EQ(filled[1].reason, "");
}

TEST(OrderBookTest, TestLowSellHighBuy) {
    order_book* orderBook = new order_book("Rose");
    vector<utils::execution> insertExecutions = orderBook->insert(1, {
            "aa13",
            "Rose",
            2,
            100,
            45.0
    });

    vector<utils::execution> filled = orderBook->insert(2, {
            "aa14",
            "Rose",
            1,
            100,
            55.0
    });

    ASSERT_EQ(filled.size(), 2);

    ASSERT_EQ(filled[0].order_id, "ord2");
    ASSERT_EQ(filled[0].client_order_id, "aa14");
    ASSERT_EQ(filled[0].side, 1);
    ASSERT_EQ(filled[0].quantity, 100);
    ASSERT_EQ(filled[0].price, 45.0);
    ASSERT_EQ(filled[0].status, 2);
    ASSERT_EQ(filled[0].reason, "");

    ASSERT_EQ(filled[1].order_id, "ord1");
    ASSERT_EQ(filled[1].client_order_id, "aa13");
    ASSERT_EQ(filled[1].side, 2);
    ASSERT_EQ(filled[1].quantity, 100);
    ASSERT_EQ(filled[1].price, 45.0);
    ASSERT_EQ(filled[1].status, 2);
    ASSERT_EQ(filled[1].reason, "");
}

TEST(OrderBookTest, TestHighBuyLowSell) {
    order_book* orderBook = new order_book("Rose");
    vector<utils::execution> insertExecutions = orderBook->insert(1, {
            "aa13",
            "Rose",
            1,
            100,
            55.0
    });

    vector<utils::execution> filled = orderBook->insert(2, {
            "aa14",
            "Rose",
            2,
            100,
            45.0
    });

    ASSERT_EQ(filled.size(), 2);

    ASSERT_EQ(filled[0].order_id, "ord2");
    ASSERT_EQ(filled[0].client_order_id, "aa14");
    ASSERT_EQ(filled[0].side, 2);
    ASSERT_EQ(filled[0].quantity, 100);
    ASSERT_EQ(filled[0].price, 55.0);
    ASSERT_EQ(filled[0].status, 2);
    ASSERT_EQ(filled[0].reason, "");

    ASSERT_EQ(filled[1].order_id, "ord1");
    ASSERT_EQ(filled[1].client_order_id, "aa13");
    ASSERT_EQ(filled[1].side, 1);
    ASSERT_EQ(filled[1].quantity, 100);
    ASSERT_EQ(filled[1].price, 55.0);
    ASSERT_EQ(filled[1].status, 2);
    ASSERT_EQ(filled[1].reason, "");
}

TEST(OrderBookTest, CompleteExample){
    vector<utils::order> orders = {
            {
                "aa13",
                "Rose",
                1,
                100,
                55.0
            },
            {
                    "aa14",
                    "Rose",
                    1,
                    100,
                    65.0
            },
            {
                    "aa15",
                    "Rose",
                    2,
                    300,
                    1.0
            },
            {
                    "aa16",
                    "Rose",
                    1,
                    100,
                    2.0
            }
    };

    vector<utils::execution> expected = {
            {
                "ord1",
                "aa13",
                "Rose",
                1,
                0,
                100,
                55.0
            },
            {
                    "ord2",
                    "aa14",
                    "Rose",
                    1,
                    0,
                    100,
                    65.0
            },
            {
                    "ord3",
                    "aa15",
                    "Rose",
                    2,
                    3,
                    100,
                    65.0
            },
            {
                    "ord2",
                    "aa14",
                    "Rose",
                    1,
                    2,
                    100,
                    65.0
            },
            {
                    "ord3",
                    "aa15",
                    "Rose",
                    2,
                    3,
                    100,
                    55.0
            },
            {
                    "ord1",
                    "aa13",
                    "Rose",
                    1,
                    2,
                    100,
                    55.0
            },
            {
                    "ord4",
                    "aa16",
                    "Rose",
                    1,
                    2,
                    100,
                    1.0
            },
            {
                    "ord3",
                    "aa15",
                    "Rose",
                    2,
                    2,
                    100,
                    1.0
            }


    };

    order_book* orderBook = new order_book("Rose");
    vector<utils::execution> executions;
    int i = 1;
    for (utils::order order: orders){
        vector<utils::execution> fills = orderBook->insert( i++, order);
        for(utils::execution exec: fills){
            executions.push_back(exec);
        }
    }

    ASSERT_EQ(executions.size(), expected.size());
    for (int j=0; j < executions.size(); j++){
        ASSERT_EQ(executions[j].order_id, expected[j].order_id);
        ASSERT_EQ(executions[j].client_order_id, expected[j].client_order_id);
        ASSERT_EQ(executions[j].instrument, expected[j].instrument);
        ASSERT_EQ(executions[j].side, expected[j].side);
        ASSERT_EQ(executions[j].quantity, expected[j].quantity);
        ASSERT_EQ(executions[j].price, expected[j].price);
        ASSERT_EQ(executions[j].reason, expected[j].reason);
    }

}
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}