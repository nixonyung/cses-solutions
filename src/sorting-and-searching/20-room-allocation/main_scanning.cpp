// (ref.) <https://github.com/Jonathan-Uy/CSES-Solutions/blob/main/Sorting%20and%20Searching/Room%20Allocation.cpp>

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

    enum EventType {
        ENTER,
        LEAVE, // can leave on the same day the customer enters
    };
    struct Event {
        unsigned customer_id;
        unsigned day;
        EventType type;
    };
    auto events = std::vector<Event>(N * 2);
    {
        for (unsigned i = 0; i < N; i++) {
            std::cin >> events[i * 2].day >> events[i * 2 + 1].day;
            events[i * 2].customer_id = i;
            events[i * 2].type = EventType::ENTER;
            events[i * 2 + 1].customer_id = i;
            events[i * 2 + 1].type = EventType::LEAVE;
        }
        std::ranges::stable_sort(
            events,
            [](Event const &lhs, Event const &rhs) {
                return (lhs.day != rhs.day)     ? (lhs.day < rhs.day)
                       : (lhs.type != rhs.type) ? (lhs.type < rhs.type)
                                                : (lhs.customer_id > rhs.customer_id);
            }
        );
    }

    auto assigned_rooms = std::vector<unsigned>(N);
    {
        unsigned num_rooms = 0;
        auto available_rooms = std::priority_queue< // following test outputs: prioritize smaller room_id
            unsigned,
            std::vector<unsigned>,
            std::greater<>>();
        for (auto const &[customer_id, _, event_type] : events) {
            switch (event_type) {
            case EventType::ENTER: {
                if (available_rooms.empty()) {
                    assigned_rooms[customer_id] = num_rooms++;
                    break;
                }
                assigned_rooms[customer_id] = available_rooms.top();
                available_rooms.pop();
            } break;
            case EventType::LEAVE: {
                available_rooms.push(assigned_rooms[customer_id]);
            } break;
            }
        }
        std::cout << num_rooms << '\n';
    }
    for (auto const &room_id : assigned_rooms) {
        std::cout << room_id + 1 << ' ';
    }
    std::cout << '\n';
}
