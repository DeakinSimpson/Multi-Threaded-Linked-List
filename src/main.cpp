
#include <iostream>
#include <list>

#include "LinkedList.h"

int main()
{
    LinkedList::LinkedList<int> list { 0, 1, 2, 3 };

    // Should print: 0 1 2 3
    for (auto& v : list)
    {
        std::cout << v << ' ';
    }
    std::cout << '\n';

    auto it { list.begin() };
    while (it != list.end())
    {
        if (*it == 2)
        {
            it = list.Erase(it);
        } else
        {
            ++it;
        }
    }


    // Sanity checks
    std::cout << "distance: " << std::distance(list.begin(), list.end()) << '\n';
    std::cout << "size:     " << list.Size() << '\n';
    std::cout << "empty:    " << std::boolalpha << list.Empty() << '\n';

    list.Clear();

    std::cout << "size: " << list.Size() << std:: endl;


    return 0;
}