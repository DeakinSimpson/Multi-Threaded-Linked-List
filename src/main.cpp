
#include <iostream>

#include "LinkedList.h"

int main()
{
    LinkedList::LinkedList<int> list;
    list.PushBack(1);
    list.PushBack(2);
    list.PushBack(3);
    list.PushFront(0);

    // Should print: 0 1 2 3
    for (int v : list)
        std::cout << v << ' ';
    std::cout << '\n';

    // Sanity checks
    std::cout << "distance: " << std::distance(list.begin(), list.end()) << '\n'; // 4
    std::cout << "size:     " << list.Size() << '\n';                             // 4
    std::cout << "empty:    " << std::boolalpha << list.Empty() << '\n';          // false

    return 0;
}