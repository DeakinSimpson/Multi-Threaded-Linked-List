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