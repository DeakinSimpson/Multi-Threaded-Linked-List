//
// Created by Deakin on 28/09/2026.
//

#include <gtest/gtest.h>
#include "LinkedList.hpp"

TEST(begin, returns_nullptr_when_empty_list)
{
    ThreadSafeList::ThreadSafeList<int> tsll {};

    EXPECT_EQ(tsll.begin(), nullptr);
}

TEST(begin, returns_iterator_to_first_node)
{
    ThreadSafeList::ThreadSafeList<int> tsll {};

    tsll.push_front(1);
    tsll.push_front(2);

    EXPECT_EQ(*tsll.begin(), 2);
}

TEST(end, returs_nullptr_when_empty_list)
{
    ThreadSafeList::ThreadSafeList<int> tsll {};

    EXPECT_EQ(tsll.end(), nullptr);
}

TEST(end, returns_iterator_to_next_last_node)
{
    ThreadSafeList::ThreadSafeList<int> tsll {};

    tsll.push_front(1);
    tsll.push_front(2);

    EXPECT_EQ(tsll.end(), nullptr);
}

TEST(initializer_list, create_list_with_initialisation_list)
{
    ThreadSafeList::ThreadSafeList<int> tsll { 1, 2, 3, 4 };

    std::vector<int> testVec {};

    for (auto i : tsll)
    {
        testVec.push_back(i);
    }

    EXPECT_EQ(testVec[0], 1);
    EXPECT_EQ(testVec[1], 2);
    EXPECT_EQ(testVec[2], 3);
    EXPECT_EQ(testVec[3], 4);
}

TEST(size, return_zero_when_empty_list)
{
    ThreadSafeList::ThreadSafeList<int> tsll {};

    EXPECT_EQ(tsll.size(), 0);
}

TEST(size, return_correct_size)
{
    ThreadSafeList::ThreadSafeList<int> tsll { 1, 2, 3, 4 };

    EXPECT_EQ(tsll.size(), 4);
}

TEST(empty, return_true_if_empty)
{
    ThreadSafeList::ThreadSafeList<int> tsll {};

    EXPECT_EQ(tsll.empty(), true);
}


TEST(empty, return_false_if_contains_data)
{
    ThreadSafeList::ThreadSafeList<int> tsll {};

    tsll.push_front(1);
    tsll.push_front(2);

    EXPECT_EQ(tsll.empty(), false);
}

TEST(front, return_the_front_object)
{
    ThreadSafeList::ThreadSafeList<int> tsll { 1, 2, 3, 4 };

    EXPECT_EQ(tsll.front(), 1);
}

TEST(back, return_back_object)
{
    ThreadSafeList::ThreadSafeList<int> tsll { 1, 2, 3, 4 };

    EXPECT_EQ(tsll.back(), 4);
}

TEST(push_front, push_to_empty_list_success)
{
    ThreadSafeList::ThreadSafeList<int> tsll {};

    EXPECT_NO_THROW({
        tsll.push_front(0);
    });
}

TEST(push_front, push_to_list_with_elements_success)
{
    ThreadSafeList::ThreadSafeList<int> tsll { 1, 2, 3, 4 };

    EXPECT_NO_THROW({
        tsll.push_front(0);
    });
}

TEST(push_front, multithreaded_pushing_returns_correct_size)
{
    ThreadSafeList::ThreadSafeList<int> tsll {};

    auto push_func = [](
            ThreadSafeList::ThreadSafeList<int>& list,
            int count,
            int num){
        for (int i {}; i < count; ++i)
        {
            list.push_front(num);
        }
    };

    std::thread t1(push_func, std::ref(tsll), 10000, 0);
    std::thread t2(push_func, std::ref(tsll), 10000, 1);

    t2.join();
    t1.join();

    EXPECT_EQ(tsll.size(), 20000);
}

TEST(push_back, push_to_empty_list_success)
{
    ThreadSafeList::ThreadSafeList<int> tsll {};

    EXPECT_NO_THROW({
        tsll.push_back(0);
    });
}

TEST(push_back, push_to_list_with_elements_success)
{
    ThreadSafeList::ThreadSafeList<int> tsll { 1, 2, 3, 4 };

    EXPECT_NO_THROW({
        tsll.push_back(5);
    });
}

TEST(push_back, multithreaded_pushing_returns_correct_size)
{
    ThreadSafeList::ThreadSafeList<int> tsll {};

    auto push_func = [](
            ThreadSafeList::ThreadSafeList<int>& list,
            int count,
            int num){
        for (int i {}; i < count; ++i)
        {
            list.push_back(num);
        }
    };

    std::thread t1(push_func, std::ref(tsll), 10000, 0);
    std::thread t2(push_func, std::ref(tsll), 10000, 1);

    t2.join();
    t1.join();

    EXPECT_EQ(tsll.size(), 20000);
}

TEST(erase, erase_works_with_valid_iterator)
{
    ThreadSafeList::ThreadSafeList<int> tsll { 1, 2, 3, 4 };

    auto it { tsll.begin() };

    std::advance(it, 2);

    tsll.erase(it);

    std::vector<int> v(tsll.begin(), tsll.end());

    EXPECT_EQ(v, (std::vector<int>{ 1, 2, 4 }));
}