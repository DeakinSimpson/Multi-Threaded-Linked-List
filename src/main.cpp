
#include <iostream>
#include "LinkedList.h"

int main()
{
    std::cout << "Hello World!" << std::endl;

    LinkedList::LinkedList linked_list;

    linked_list.InsertBeginning(5);

    std::cout << linked_list.Front() << std::endl;

    return 0;
}