
#include <iostream>
#include "LinkedList.h"

int main()
{
    std::cout << "Hello World!" << std::endl;

    LinkedList::LinkedList linked_list;

    linked_list.PushFront(5);
    linked_list.PushFront(6);
    linked_list.PushFront(7);

    std::cout << linked_list.Front() << std::endl;
    std::cout << linked_list.Back() << std::endl;

    return 0;
}