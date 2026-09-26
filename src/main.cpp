
#include <iostream>
#include <list>
#include <random>
#include <thread>

#include "LinkedList.h"

enum class PushType
{
    Front,
    Back,
    Both,
};

// adds count number of number to mtList
void AddNumbersToList(
    MTList::MTList<int>& mtList,
    int number,
    int count,
    PushType pt)
{
    for (int i {}; i < count; ++i)
    {
        if (pt == PushType::Back)
        {
            mtList.PushBack(number);
        } else if (pt == PushType::Front)
        {
            mtList.PushFront((number));
        } else
        {
            if (i % 2 == 0)
            {
                mtList.PushBack(number);
            } else
            {
                mtList.PushFront(number);
            }
        }
    }
}

int main()
{
    MTList::MTList<int> mtList;

    std::thread t1(AddNumbersToList, std::ref(mtList), 1, 10000, PushType::Front);
    std::thread t2(AddNumbersToList, std::ref(mtList), 0, 10000, PushType::Front);

    t1.join();
    t2.join();

    std::cout << mtList.Size();

    return 0;
}