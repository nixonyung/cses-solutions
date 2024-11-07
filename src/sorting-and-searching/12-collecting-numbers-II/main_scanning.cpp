#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    unsigned N;
    unsigned NUM_TESTS;
    {
        std::cin >> N >> NUM_TESTS;
    }
    /*
    note that:
        - inputs[poss[x]] = x
        - poss[inputs[i]] = i
    */
    auto numbers = std::vector<unsigned>(N);  // inputs[1] is the first (i.e. pos=1) input
    auto poss = std::vector<unsigned>(N + 2); // poss[x] is the position of x (so the first input x has poss[x] = 1)
    {
        // dummy values to handle index-out-of-bound
        poss[0] = 0;
        poss[N + 1] = N + 1;

        for (unsigned i = 1; i <= N; i++) {
            std::cin >> numbers[i];
            poss[numbers[i]] = i;
        }
    }

    unsigned num_rounds = 1;
    {
        for (unsigned i = 2; i <= N; i++) {
            if (poss[i] < poss[i - 1]) num_rounds++;
        }
    }
    {
        auto delta_num_rounds = [&numbers, &poss](unsigned pos1, unsigned pos2) -> unsigned {
            // when swapping two consecutive increasing numbers, e.g. 1 2
            if (numbers[pos1] + 1 == numbers[pos2]) {
                return (poss[numbers[pos1] - 1] > pos1)
                       + (pos1 > pos2)
                       + (pos2 > poss[numbers[pos2] + 1]);
            }
            // when swapping two consecutive decreasing numbers, e.g. 2 1
            if (numbers[pos2] + 1 == numbers[pos1]) {
                return (poss[numbers[pos2] - 1] > pos2)
                       + (pos2 > pos1)
                       + (pos1 > poss[numbers[pos1] + 1]);
            }
            // swaaping anything else, e.g. 1 3 or 3 1
            return (poss[numbers[pos1] - 1] > pos1)
                   + (pos1 > poss[numbers[pos1] + 1])
                   + (poss[numbers[pos2] - 1] > pos2)
                   + (pos2 > poss[numbers[pos2] + 1]);
        };

        unsigned pos1;
        unsigned pos2;
        while (NUM_TESTS--) {
            std::cin >> pos1 >> pos2;

            num_rounds -= delta_num_rounds(pos1, pos2);
            std::swap(poss[numbers[pos1]], poss[numbers[pos2]]);
            std::swap(numbers[pos1], numbers[pos2]);
            num_rounds += delta_num_rounds(pos1, pos2);

            std::cout << num_rounds << '\n';
        }
    }
}