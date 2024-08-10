#define VERSION_MIN_AVAILABLE_ROOM 1
#define VERSION_MIN_ROOM_ID 2
#define VERSION_BLOCKED_ARRAYS 3

#define VERSION VERSION_MIN_ROOM_ID

#if VERSION == VERSION_MIN_AVAILABLE_ROOM
#include <algorithm>
#include <array>
#include <cstdio>
#include <queue>
#include <vector>

struct Customer {
    size_t id;
    size_t a;
    size_t b;
};

struct Room {
    size_t id;
    size_t available_from;
};

int main() {
    auto constexpr MAX_N = int(2e5);

    auto n = int();
    std::scanf("%d", &n);

    // solve by simulation
    // (ref.) [CSES - Room Allocation](https://usaco.guide/problems/cses-1164-room-allocation/solution)
    // use priority_queue to remember opened room and determine if there exist an opened room that is available

    auto customers = std::array<Customer, MAX_N>();
    for (int i = 0; i < n; i++) {
        std::scanf("%ld %ld", &customers[i].a, &customers[i].b);
        customers[i].id = i;
    }
    std::sort(
        customers.begin(),
        customers.begin() + n,
        [](auto const &lhs, auto const &rhs) {
            return lhs.a < rhs.a;
        }
    );

    auto ans = std::array<size_t, MAX_N>();
    auto rooms = std::priority_queue<
        Room,
        std::vector<Room>,
        decltype([](auto const &lhs, auto const &rhs) { return lhs.available_from > rhs.available_from; })>();
    for (int i = 0; i < n; i++) {
        auto const &customer = customers[i];
        if (rooms.empty() || customer.a < rooms.top().available_from) {
            ans[customer.id] = rooms.size() + 1;
            rooms.push({rooms.size() + 1, customer.b + 1});
        } else {
            ans[customer.id] = rooms.top().id;
            rooms.push({rooms.top().id, customer.b + 1});
            rooms.pop();
        }
    }

    std::printf("%ld\n", rooms.size());
    for (int i = 0; i < n; i++) {
        std::printf("%ld ", ans[i]);
    }
    std::printf("\n");
}
#elif VERSION == VERSION_MIN_ROOM_ID
#include <algorithm>
#include <array>
#include <cstdio>
#include <queue>
#include <vector>

enum class CustomerActionType {
    ENTER,
    LEAVE,
};

struct CustomerAction {
    size_t id;
    int day;
    CustomerActionType type;
};

int main() {
    auto constexpr MAX_N = int(2e5);

    auto n = int();
    std::scanf("%d", &n);

    // solve by simulation
    // (ref.) <https://github.com/Jonathan-Uy/CSES-Solutions/blob/main/Sorting%20and%20Searching/Room%20Allocation.cpp>

    auto customer_actions = std::array<CustomerAction, MAX_N * 2>();
    for (int i = 0; i < n; i++) {
        std::scanf("%d", &customer_actions[i * 2].day);
        customer_actions[i * 2].id = i;
        customer_actions[i * 2].type = CustomerActionType::ENTER;

        std::scanf("%d", &customer_actions[i * 2 + 1].day);
        customer_actions[i * 2 + 1].id = i;
        customer_actions[i * 2 + 1].type = CustomerActionType::LEAVE;
    }
    std::sort(
        customer_actions.begin(),
        customer_actions.begin() + n * 2,
        [](auto const &lhs, auto const &rhs) {
            return (lhs.day != rhs.day)     ? (lhs.day < rhs.day)
                   : (lhs.type != rhs.type) ? (lhs.type < rhs.type) // customers arrive at the start of the day, and leave at the end of the day
                                            : (lhs.id > rhs.id);
        }
    );

    auto available_rooms = std::priority_queue<
        size_t,
        std::vector<size_t>,
        decltype([](auto const &lhs, auto const &rhs) { return lhs > rhs; })>();

    auto ans = std::array<size_t, MAX_N>();
    auto num_rooms = 0;
    for (int i = 0; i < n * 2; i++) {
        auto &action = customer_actions[i];
        switch (action.type) {
        case CustomerActionType::ENTER:
            if (!available_rooms.empty()) {
                ans[action.id] = available_rooms.top();
                available_rooms.pop();
            } else {
                num_rooms++;
                ans[action.id] = num_rooms;
            }
            break;
        case CustomerActionType::LEAVE:
            available_rooms.push(ans[action.id]);
            break;
        }
    }

    std::printf("%d\n", num_rooms);
    for (int i = 0; i < n; i++) {
        std::printf("%ld ", ans[i]);
    }
    std::printf("\n");
}
#elif VERSION == VERSION_BLOCKED_ARRAYS
#include <algorithm>
#include <array>
#include <climits>
#include <cstdio>

struct Customer {
    size_t id;
    size_t a;
    size_t b;
};

template <size_t BLOCK_SIZE>
struct RoomsBlock {
    std::array<size_t, BLOCK_SIZE> rooms;
    size_t num_rooms;
    size_t min_room_val;

    RoomsBlock() {
        num_rooms = 0;
        min_room_val = INT_MAX;
    }

    void add_room(size_t val) {
        rooms[num_rooms] = val;
        num_rooms++;
        min_room_val = std::min(min_room_val, val);
    }

    void regen_min_room_val() {
        min_room_val = INT_MAX;
        for (size_t i = 0; i < num_rooms; i++) {
            min_room_val = std::min(min_room_val, rooms[i]);
        }
    }
};

int main() {
    auto constexpr MAX_N = int(2e5);
    auto constexpr BLOCK_SIZE = 256;
    auto constexpr MAX_NUM_BLOCKS = MAX_N / BLOCK_SIZE + 1;

    auto n = int();
    std::scanf("%d", &n);

    auto customers = std::array<Customer, MAX_N>();
    for (int i = 0; i < n; i++) {
        std::scanf("%ld %ld", &customers[i].a, &customers[i].b);
        customers[i].id = i;
    }
    std::sort(
        customers.begin(),
        customers.begin() + n,
        [](auto const &lhs, auto const &rhs) {
            return (lhs.a != rhs.a) ? (lhs.a < rhs.a)
                                    : (lhs.id > rhs.id);
        }
    );

    auto ans = std::array<size_t, MAX_N>();
    auto blocks = std::array<RoomsBlock<BLOCK_SIZE>, MAX_NUM_BLOCKS>();
    auto num_blocks = 0;
    auto total_num_rooms = 0;
    for (int i = 0; i < n; i++) {
        auto &customer = customers[i];

        auto block_idx = 0;
        while (block_idx < num_blocks && customer.a < blocks[block_idx].min_room_val) {
            block_idx++;
        }

        if (block_idx < num_blocks) {
            // find and update the available room in the block
            auto &block = blocks[block_idx];
            block.min_room_val = INT_MAX;
            for (size_t room_idx = 0; room_idx < block.num_rooms; room_idx++) {
                if (customer.a >= block.rooms[room_idx]) {
                    block.rooms[room_idx] = customer.b + 1;
                    ans[customer.id] = BLOCK_SIZE * block_idx + room_idx + 1;
                    break;
                }
            }
            block.regen_min_room_val();
        } else if (num_blocks > 0 && blocks[num_blocks - 1].num_rooms < BLOCK_SIZE) {
            // add a new room in the last block
            blocks[num_blocks - 1].add_room(customer.b + 1);
            total_num_rooms++;
            ans[customer.id] = total_num_rooms;
        } else {
            // add a new room in a new block
            num_blocks++;
            blocks[num_blocks - 1].add_room(customer.b + 1);
            total_num_rooms++;
            ans[customer.id] = total_num_rooms;
        }
    }

    std::printf("%d\n", total_num_rooms);
    for (int i = 0; i < n; i++) {
        std::printf("%ld ", ans[i]);
    }
    std::printf("\n");
}
#endif