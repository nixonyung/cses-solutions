#include "heap.hpp"
#include "utils.hpp"

namespace {
enum class CustomerActionType {
    ENTER,
    LEAVE,
};

struct CustomerAction {
    uint id;
    uint day;
    CustomerActionType type;
};
} // namespace

int main() {
    enable_fast_io();

    auto n = read<uint>();

    // solve by simulation
    // (ref.) <https://github.com/Jonathan-Uy/CSES-Solutions/blob/main/Sorting%20and%20Searching/Room%20Allocation.cpp>

    auto customer_actions = std::vector<CustomerAction>(n * 2);
    {
        for (auto i : iota(0U, n)) {
            customer_actions[i * 2] = {i, read<uint>(), CustomerActionType::ENTER};
            customer_actions[i * 2 + 1] = {i, read<uint>(), CustomerActionType::LEAVE};
        }
        std::ranges::sort(
            customer_actions,
            [](auto const &lhs, auto const &rhs) {
                return (lhs.day != rhs.day)     ? (lhs.day < rhs.day)
                       : (lhs.type != rhs.type) ? (lhs.type < rhs.type) // customers arrive at the start of the day, and leave at the end of the day
                                                : (lhs.id > rhs.id);
            }
        );
    }

    auto anss = std::vector<uint>(n);
    {
        auto available_rooms = heap<uint>();
        uint num_rooms = 0;
        for (auto const &action : customer_actions) {
            switch (action.type) {
            case CustomerActionType::ENTER:
                if (!available_rooms.empty()) {
                    anss[action.id] = available_rooms.top();
                    available_rooms.pop();
                } else {
                    num_rooms++;
                    anss[action.id] = num_rooms;
                }
                break;
            case CustomerActionType::LEAVE:
                available_rooms.push(anss[action.id]);
                break;
            }
        }
        std::cout << num_rooms << '\n';
    }
    for (auto const &ans : anss) {
        std::cout << ans << ' ';
    }
    std::cout << '\n';
}
