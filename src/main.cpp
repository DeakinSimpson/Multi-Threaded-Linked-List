
#include <iostream>

#include "LinkedList.h"

int main()
{
    LinkedList::LinkedList<int> list { 0, 1, 2, 3};

    // Should print: 0 1 2 3
    for (const int v : list)
    {
        std::cout << v << ' ';
    }
    std::cout << '\n';

    // Sanity checks
    std::cout << "distance: " << std::distance(list.begin(), list.end()) << '\n';
    std::cout << "size:     " << list.Size() << '\n';
    std::cout << "empty:    " << std::boolalpha << list.Empty() << '\n';

    return 0;
}