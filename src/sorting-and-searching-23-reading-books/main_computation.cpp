#include "utils.hpp"

int main() {
    enable_fast_io();

    auto n = read<uint>();

    // (ref.) <https://github.com/Jonathan-Uy/CSES-Solutions/blob/main/Sorting%20and%20Searching/Reading%20Books.cpp>

    /*
    if the longest book is longer than all the other books combined:
        - Kotivalo reads the longest book, while Justiina finish all the other books (and possibly wait)
        - Justiina reads the longest book, while Kotivalo finish all the other books (and possibly wait)

        => time = longest_book_duration * 2
    else:
        - Kotivalo reads the longest book, while Justiina reads books in ascending order of length without waiting
          (because of the else case)
        - Justiina will finish at least 1 book, without stopping (because of the else case)
        - Kotivalo reads the remaining books in ascending order of length, Justlina continue to finish all books

        => time = sum(book_durations) (because there is no waiting)

    optimization:
        As there are only two possible cases, compute them both and choose the larger one as the ans
        without sorting inputs (to get the longest book).
    */

    ulong sum_book_durations = 0;
    uint max_book_duration = 0;
    {
        for (auto _ : iota(0U, n)) {
            auto book_duration = read<uint>();
            sum_book_durations += book_duration;
            max_book_duration = std::max(max_book_duration, book_duration);
        }
    }
    std::cout << std::max(sum_book_durations, (ulong)max_book_duration * 2) << '\n';
}