/*
 * Question 2
 * Given 2 UDP streams, A and B, we would like to implement a consumer who
 *   receives all messages in order of sequence number.
 * Streams A and B are redundant, meaning both streams will be sent all of the
 *   same messages.
 * Please implement the below class, adding any members or helper functions
 *   necessary.
 * The passMessageToConsumer method should be called by onMessage every time
 *   it has the next message available.
 * For simplification, you can assume you will always receive at least one copy
 *   of each message
 * You should focus on performance
 * You may use the std libraries or STL, as well as any features through C++20
 */
#include <iostream>
#include <array>
#include <cstring>
#include <cstdint>
#include <unordered_set>
#include <string_view>
#include <algorithm>

constexpr std::size_t MessageSize = 5;  // Fixed size of each message
constexpr std::size_t ArrayCapacity = 4; // Array size for sequence numbers
static constexpr std::size_t ArrayCapacityMinusOne = ArrayCapacity - 1;  // Precompute ArrayCapacity - 1
const size_t maxByteCount = 10;

class StreamHandler {
    struct Message {

        Message() = default;

        Message(uint64_t _seqnum, const char* _bytes, const std::size_t _byteCount) : byteCount(_byteCount), seqnum(seqnum)
        {
            memcpy(&data, _bytes, _byteCount);
        }

        Message(const Message&) = delete;
        Message& operator = (const Message&) = delete;

        char data[maxByteCount] = { 0 };
        int byteCount = 0;
        uint64_t seqnum = 0;
    };

    // we cannot keep growing the messages buffer, we need to process asap, if somehow 
    // one of the sequence numebr is missed and never received then we might not also send the received messages also, 
    // in that case we have to discard the messages porior to not received 
    std::array<Message, ArrayCapacity> messages; // Fixed-size array for storing messages

    std::array<uint64_t, ArrayCapacity> seqnums = {0}; // Fixed-size array for faster lookup of seq numbers

    uint64_t nextExpectedSeqIndex = 1; // The next expected sequence number to be processed

    void passMessageToConsumer(int startIndex, int endIndex) {
        // we can send these in bulk copy also
        int diff = std::abs(startIndex - endIndex);
        int cnt = 0;
        do
        {
            std::cout << "Consumer received message: " << messages[startIndex].data << "\n";
            ++cnt;
            startIndex = (startIndex + 1) & ArrayCapacityMinusOne;
        }while (diff >= cnt);
    }

    // Function to calculate the position in the array based on the sequence number
    inline std::size_t getIndex(uint64_t seqnum) const noexcept {
        return seqnum & ArrayCapacityMinusOne;
    }

public:
    StreamHandler() {

    }

    void onMessage(char stream, uint64_t seqnum, const char* bytes, const std::size_t byteCount) noexcept {
        // Calculate the index based on the sequence number
        std::size_t index = getIndex(seqnum);

        // If the message has already been processed (seqnum == 0 or duplicate), return
        if (seqnums[index] == seqnum) {
            return; // Skip duplicate messages
        }

        // Store the message in the appropriate position in the array
        new (&messages[index]) Message(seqnum, bytes, byteCount);
        seqnums[index] = seqnum;

        // Process messages in sequence order
        if (nextExpectedSeqIndex == index) // we found missing sequence numebr
        {
            uint64_t endSeqnum = nextExpectedSeqIndex;

            while (seqnums[endSeqnum] < seqnums[(endSeqnum + 1) & ArrayCapacityMinusOne])
            {
                endSeqnum = (endSeqnum + 1) & ArrayCapacityMinusOne;
            }
            // now search for next end of range where we have received messages;

            passMessageToConsumer(nextExpectedSeqIndex, endSeqnum);
            nextExpectedSeqIndex = (endSeqnum + 1) & ArrayCapacityMinusOne;
        }
    }
};

int main() {
    StreamHandler handler;
    handler.onMessage('A', 1, "Msg 1", 5);
    handler.onMessage('B', 1, "Msg 1", 5);
    handler.onMessage('B', 2, "Msg 2", 5);
    handler.onMessage('A', 2, "Msg 2", 5);
    handler.onMessage('B', 5, "Msg 5", 5);
    handler.onMessage('A', 4, "Msg 4", 5);
    handler.onMessage('A', 3, "Msg 3", 5);
    handler.onMessage('A', 5, "Msg 5", 5);
    handler.onMessage('B', 3, "Msg 3", 5);
    handler.onMessage('B', 4, "Msg 4", 5);

    handler.onMessage('A', 5, "Msg 5", 5);
    handler.onMessage('B', 7, "Msg 7", 5);
    handler.onMessage('B', 5, "Msg 5", 5);
    handler.onMessage('A', 5, "Msg 5", 5);
    handler.onMessage('B', 6, "Msg 6", 5);
    handler.onMessage('A', 6, "Msg 6", 5);
    handler.onMessage('A', 10, "Msg 10", 6);
    handler.onMessage('A', 8, "Msg 8", 5);
    handler.onMessage('B', 9, "Msg 9", 5);
    handler.onMessage('B', 10, "Msg 10", 6);

    handler.onMessage('A', 14, "Msg 14", 6);
    handler.onMessage('A', 12, "Msg 12", 6);
    handler.onMessage('B', 13, "Msg 13", 6);
    handler.onMessage('B', 11, "Msg 11", 6);

    return 0;
}

