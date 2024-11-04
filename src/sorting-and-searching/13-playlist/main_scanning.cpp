#include <algorithm>
#include <iostream>
#include <map>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    unsigned N;
    {
        std::cin >> N;
    }

    unsigned max_unique_len = 0;
    {
        auto song_id_to_pos = std::map<unsigned, unsigned>();
        decltype(song_id_to_pos)::key_type song_id;
        unsigned unique_start_idx = 0;
        for (unsigned i = 0; i < N; i++) {
            std::cin >> song_id;

            if (song_id_to_pos.contains(song_id)) {
                max_unique_len = std::max(max_unique_len, i - unique_start_idx);
                unique_start_idx = std::max(unique_start_idx, song_id_to_pos[song_id] + 1);
            }
            song_id_to_pos[song_id] = i;
        }
        max_unique_len = std::max(max_unique_len, N - unique_start_idx);
    }
    std::cout << max_unique_len << '\n';
}