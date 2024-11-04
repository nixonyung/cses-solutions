/*
(ref.) <https://github.com/Jonathan-Uy/CSES-Solutions/blob/main/Sorting%20and%20Searching/Reading%20Books.cpp>

There are only two possibilities (and their optimal solutions):
  if the longest book is longer than all the other books combined:
    1. assign Kotivalo to read the longest book,
       Justiina to read all the other books (and possibly waits),
    2. assign Justiina to read the longest book
       Kotivalo to read all the other books (and possibly waits)
    => time spent = longest_book_duration * 2
  else:
    1. assign Kotivalo to read the longest book,
       Justiina to read books in ascending order of durations (and never waits)
       - Justiina should finish at least 1 book before Kotivalo finishes
    2. assign Kotivalo to read the remaining books in ascending order of durations (so that it is impossible for Justlina to be reading the book),
       Justlina to continue reading all the other books, then the longest book
    => time spent = sum(book_durations) (because there is no waiting)

optimization: as there are only two possible results, simply compute both and return the larger one
*/

#include <algorithm>
#include <iostream>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    unsigned N;
    {
        std::cin >> N;
    }

    unsigned long book_durations_sum = 0;
    unsigned max_book_duration = 0;
    {
        unsigned book_duration;
        for (unsigned i = 0; i < N; i++) {
            std::cin >> book_duration;

            book_durations_sum += book_duration;
            max_book_duration = std::max(max_book_duration, book_duration);
        }
    }
    std::cout << std::max(book_durations_sum, (unsigned long)max_book_duration * 2) << '\n';
}