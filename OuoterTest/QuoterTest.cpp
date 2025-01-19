#include <iostream>
#include <cassert>
#include <unordered_map>
#include <unordered_set>

struct OrderBookSell
{
    uint32_t id;
    uint32_t orderVolume;
    double orderPrice;
};

struct OrderBookBuy
{
    uint32_t id;
    uint32_t orderVolume;
    double orderPrice;
};

std::unordered_map<uint32_t, OrderBookBuy> g_orderBookBuySide;
std::unordered_map<uint32_t, OrderBookSell> g_orderBookSellSide;

std::unordered_set<uint32_t> g_orderBookPendingAddBuySide;
std::unordered_set<uint32_t> g_orderBookPendingAddSellSide;

std::unordered_set<uint32_t> g_orderBookPendingRemoveBuySide;
std::unordered_set<uint32_t> g_orderBookPendingRemoveSellSide;


class Execution
{
public:
    void requestOrderAdd( // Requests an order to be added at the exchange
        uint32_t id, // A caller-selected request identifier for this order
        std::string const& feedcode, // The exchange identifier of the instrument
        char orderSide, // The side of the order ('B' for buy, 'S' for sell)
        double orderPrice, // The price of the order
        uint32_t orderVolume) // The volume of the order
    {
        std::cout << "Add Order: " << feedcode << " " << orderSide << " " << orderPrice << " " << orderVolume << '\n';
    }
    void requestOrderRemove( // Requests an order to be removed at the exchange
        uint32_t id) // The request identifier used in 'requestOrderAdd'
    {
        std::cout << "Remove Order ID: " << id << '\n';
    }
};

class InstrumentQuoter {
public:
    InstrumentQuoter(std::string const& feedcode, double quoteOffset, uint32_t quoteVolume,
        double tickWidth, Execution& execution)
        : feedcode_(feedcode), quoteOffset_(quoteOffset), quoteVolume_(quoteVolume),
        tickWidth_(tickWidth), execution_(execution) {
    }

    void OnTheoreticalPrice(double theoreticalPrice) {
        theoreticalPrice_ = theoreticalPrice;
        UpdateOrders();
    }

    void OnBestBidOffer(double bidPrice, double offerPrice) {
        bestBid_ = bidPrice;
        bestOffer_ = offerPrice;
        UpdateOrders();
    }

    void OnOrderAddConfirm(uint32_t id) {
        const auto& itr = g_orderBookPendingAddBuySide.find(id);
        if (itr != g_orderBookPendingRemoveBuySide.end())
        {
            g_orderBookPendingAddBuySide.erase(itr);
        }
        else
        {
            g_orderBookPendingAddSellSide.erase(id);
        }
    }

    void OnOrderRemoveConfirm(uint32_t id) {

        const auto& itr = g_orderBookPendingRemoveBuySide.find(id);
        if (itr != g_orderBookPendingRemoveBuySide.end())
        {
            g_orderBookPendingRemoveBuySide.erase(itr);
            const auto& order = g_orderBookBuySide.find(id);
            
            uint32_t newid = GenerateOrderID();
            execution_.requestOrderAdd(newid, feedcode_, 'B', currentBuyPrice_, order->second.orderVolume);
            g_orderBookPendingAddBuySide.insert(newid);
            
            g_orderBookBuySide.erase(order);
        }
        else
        {
            g_orderBookPendingRemoveBuySide.erase(id);
            const auto& order = g_orderBookSellSide.find(id);

            uint32_t newid = GenerateOrderID();
            execution_.requestOrderAdd(newid, feedcode_, 'S', currentSellPrice_, order->second.orderVolume);
            g_orderBookPendingAddSellSide.insert(newid);
            
            g_orderBookSellSide.erase(order);
        }
    }

private:
    void UpdateOrders() {
        double buyPrice = std::floor((theoreticalPrice_ - quoteOffset_) / tickWidth_) * tickWidth_;
        double sellPrice = std::ceil((theoreticalPrice_ + quoteOffset_) / tickWidth_) * tickWidth_;

        if (buyPrice >= bestBid_) buyPrice = bestBid_ - tickWidth_;
        if (sellPrice <= bestOffer_) sellPrice = bestOffer_ + tickWidth_;

        if (buyPrice != currentBuyPrice_) {
			currentBuyPrice_ = buyPrice;
            RemoveBuyOrder();
        }

        if (sellPrice != currentSellPrice_) {
            currentSellPrice_ = sellPrice;
            RemoveSellOrder();
        }
    }

    void RemoveBuyOrder() {
        for (const auto& order : g_orderBookBuySide) {
            //if (order.second.orderPrice == price)
            {
                execution_.requestOrderRemove(order.first);
                g_orderBookPendingRemoveBuySide.insert(order.first);
            }
        }
    }

    void RemoveSellOrder() {
        for (const auto& order : g_orderBookSellSide) {
            //if (order.second.orderPrice == price)
            {
                execution_.requestOrderRemove(order.first);
                g_orderBookPendingRemoveSellSide.insert(order.first);
            }
        }
    }

    inline uint32_t GenerateOrderID() {
        static uint32_t id = 3;
        return ++id;
    }

    std::string feedcode_;
    double quoteOffset_;
    uint32_t quoteVolume_;
    double tickWidth_;
    double theoreticalPrice_;
    double bestBid_;
    double bestOffer_;
    double currentBuyPrice_;
    double currentSellPrice_;
    Execution& execution_;
};


// we need order data stored in InstrumentQuoter class
// we need 5 tuple for storing order info
// when price is adjusted, then we first remove the order, on it's confirmation we should add it agian 
// we can have global order stored
// 2 order books for sell side and buy side
// they can be in ascending or descending order
// we can have order book per instrument
void TestInstrumentQuoter() {
    Execution execution;

    // Initialize the quoter
    InstrumentQuoter quoter("XYZ", 0.5, 100, 0.5, execution);

    g_orderBookBuySide[1] = OrderBookBuy{ 1, 100, 9.0 };
    g_orderBookSellSide[2] = OrderBookSell{ 2, 100, 11.0 };

    // Test Case 1: Theoretical price updates and alignment
    quoter.OnTheoreticalPrice(10.0);
    quoter.OnBestBidOffer(9.0, 11.0);
    // Expected: Add Buy order at 9.5, Sell order at 10.5

    // Test Case 2: Crossing orders
    quoter.OnTheoreticalPrice(10.0);
    quoter.OnBestBidOffer(9.0, 9.5);
    // Expected: Add Buy order at 8.5, Sell order at 9.5

    // Test Case 3: Multiple updates
    quoter.OnTheoreticalPrice(10.0);
    quoter.OnBestBidOffer(9.5, 10.5);
    // Expected: Update orders based on new bid/offer and theoretical price

    // Test Case 4: Removing and replacing orders
    quoter.OnTheoreticalPrice(11.0);
    quoter.OnBestBidOffer(9.5, 10.0);
    quoter.OnTheoreticalPrice(11.5);
    // Expected: Remove old orders and add new ones
}

int main() {
    TestInstrumentQuoter();
    return 0;
}