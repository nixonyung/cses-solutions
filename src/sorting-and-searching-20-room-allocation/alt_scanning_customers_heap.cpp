#include "heap.hpp"
#include "utils.hpp"

namespace {
struct Customer {
    uint id;
    uint start; // inclusive
    uint end;   // inclusive
};

struct Room {
    uint id;
    uint available_from;
};
} // namespace

int main() {
    enable_fast_io();

    auto n = read<uint>();

    // solve by simulation
    // (ref.) [CSES - Room Allocation](https://usaco.guide/problems/cses-1164-room-allocation/solution)
    // use priority_queue to remember opened room and determine if there exist an opened room that is available

    auto customers = std::vector<Customer>(n);
    {
        for (uint i = 0; auto &customer : customers) {
            customer = {i++, read<uint>(), read<uint>()};
        }
        radix_sort(
            customers,
            [](auto const &customer) { return customer.start; }
        );
    }

    auto anss = std::vector<uint>(n);
    {
        auto rooms = heap<Room>(
            [](auto const &lhs, auto const &rhs) { return lhs.available_from > rhs.available_from; }
        );
        for (auto const &customer : customers) {
            if (rooms.empty() || customer.start < rooms.top().available_from) {
                anss[customer.id] = (uint)rooms.size() + 1;
                rooms.push({(uint)rooms.size() + 1, customer.end + 1});
            } else {
                anss[customer.id] = rooms.top().id;
                rooms.push({rooms.top().id, customer.end + 1});
                rooms.pop();
            }
        }
        std::cout << rooms.size() << '\n';
    }
    for (auto const &ans : anss) {
        std::cout << ans << ' ';
    }
    std::cout << '\n';
}
