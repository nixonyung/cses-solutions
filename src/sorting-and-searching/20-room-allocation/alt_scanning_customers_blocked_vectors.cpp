#include "utils.hpp"
#include <limits>

namespace {
struct Customer {
    uint id;
    uint start; // inclusive
    uint end;   // inclusive
};

template <uint BLOCK_SIZE>
struct RoomsBlock {
    std::vector<uint> room_available_froms;
    uint min_room_available_from;

    RoomsBlock()
        : room_available_froms(),
          min_room_available_from(std::numeric_limits<uint>::max()) {
        room_available_froms.reserve(BLOCK_SIZE);
    }

    auto const num_rooms() const { return room_available_froms.size(); }

    void add_room(uint val) {
        room_available_froms.push_back(val);
        min_room_available_from = std::min(min_room_available_from, val);
    }

    void regen_min_room_val() {
        min_room_available_from = std::numeric_limits<uint>::max();
        for (auto const &room_available_from : room_available_froms) {
            min_room_available_from = std::min(min_room_available_from, room_available_from);
        }
    }
};
} // namespace

int main() {
    const uint BLOCK_SIZE = 256;

    auto n = read<uint>();

    auto customers = std::vector<Customer>(n);
    {
        for (uint i = 0; auto &customer : customers) {
            customer = {i++, read<uint>(), read<uint>()};
        }
        std::ranges::sort(
            customers,
            [](auto const &lhs, auto const &rhs) {
                return (lhs.start != rhs.start) ? (lhs.start < rhs.start)
                                                : (lhs.id > rhs.id);
            }
        );
    }

    auto anss = std::vector<uint>(n);
    {
        auto blocks = std::vector<RoomsBlock<BLOCK_SIZE>>();
        {
            blocks.reserve(n / BLOCK_SIZE + 1);
        }
        uint total_num_rooms = 0;
        for (auto const &customer : customers) {
            bool found = false;
            for (uint block_idx = 0; auto &block : blocks) {
                if (customer.start >= block.min_room_available_from) {
                    for (uint room_idx = 0; auto &room_available_from : block.room_available_froms) {
                        if (customer.start >= room_available_from) {
                            room_available_from = customer.end + 1;
                            anss[customer.id] = BLOCK_SIZE * block_idx + room_idx + 1;
                            break;
                        }
                        room_idx++;
                    }
                    block.regen_min_room_val();
                    found = true;
                    break;
                }
                block_idx++;
            }
            if (!found) {
                if (blocks.empty() || blocks.back().num_rooms() >= BLOCK_SIZE) {
                    blocks.push_back({});
                }
                // add a new room in the last block
                blocks.back().add_room(customer.end + 1);
                total_num_rooms++;
                anss[customer.id] = total_num_rooms;
            }
        }
        std::cout << total_num_rooms << '\n';
    }
    for (auto const &ans : anss) {
        std::cout << ans << ' ';
    }
    std::cout << '\n';
}