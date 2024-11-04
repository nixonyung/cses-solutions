// (ref.) [CSES - Room Allocation](https://usaco.guide/problems/cses-1164-room-allocation/solution)
// correct implementation but outputs are different from tests

#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    unsigned N;
    {
        std::cin >> N;
    }

    struct Customer {
        unsigned id;
        unsigned enter_at;
        unsigned leave_at;
    };
    auto customers = std::vector<Customer>(N);
    {
        for (unsigned i = 0; i < N; i++) {
            std::cin >> customers[i].enter_at >> customers[i].leave_at;
            customers[i].id = i;
        }
        std::ranges::stable_sort(
            customers,
            {},
            [](Customer const &customer) { return customer.enter_at; }
        );
    }

    auto assigned_rooms = std::vector<unsigned>(N);
    {
        struct Room {
            unsigned id;
            unsigned available_since; // customer leaves at night, so the room is available on the day after
        };
        auto rooms = std::priority_queue<
            Room,
            std::vector<Room>,
            decltype([](Room const &lhs, Room const &rhs) { return lhs.available_since > rhs.available_since; })>();
        for (auto const &[id, enter_at, leave_at] : customers) {
            if (rooms.empty() || enter_at < rooms.top().available_since) {
                assigned_rooms[id] = (unsigned)rooms.size();
                rooms.push({(unsigned)rooms.size(), leave_at + 1});
            } else {
                assigned_rooms[id] = rooms.top().id;
                rooms.push({rooms.top().id, leave_at + 1});
                rooms.pop();
            }
        }
        std::cout << rooms.size() << '\n';
    }
    for (auto const &room_id : assigned_rooms) {
        std::cout << room_id + 1 << ' ';
    }
    std::cout << '\n';
}
