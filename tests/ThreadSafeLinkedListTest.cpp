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