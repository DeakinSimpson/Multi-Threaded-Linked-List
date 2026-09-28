
#include <iostream>
#include <list>
#include <random>
#include <thread>

#include "LinkedList.hpp"

enum class PushType
{
    Front,
    Back,
    Both,
};

// adds count number of number to mtList
void AddNumbersToList(
    ThreadSafeList::ThreadSafeList<int>& mtList,
    int number,
    int count,
    PushType pt)
{
    for (int i {}; i < count; ++i)
    {
        if (pt == PushType::Back)
        {
            mtList.push_back(number);
        } else if (pt == PushType::Front)
        {
            mtList.push_front((number));
        } else
        {
            if (i % 2 == 0)
            {
                mtList.push_back(number);
            } else
            {
                mtList.push_front(number);
            }
        }
    }
}

int main()
{
    ThreadSafeList::ThreadSafeList<int> mtList;

    std::thread t1(AddNumbersToList, std::ref(mtList), 1, 10000, PushType::Front);
    std::thread t2(AddNumbersToList, std::ref(mtList), 0, 10000, PushType::Front);


    t1.join();
    t2.join();

    std::cout << mtList.size() << std::endl;
    std::cout << mtList.size_nt() << std::endl;;

    std::cout << mtList.front() << std::endl;
    std::cout << mtList.back() << std::endl;

    for (auto m : mtList)
    {
        std::cout << m << std::endl;
    }
    return 0;
}