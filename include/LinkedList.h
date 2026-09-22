//
// Created by deakin on 9/22/26.
//

#pragma once

namespace LinkedList
{
    struct Node
    {
        int data;
        Node* next;

        /**
         *
         * @param data The integer that the node will contain
         */
        explicit Node(const int data) : data(data), next(nullptr) {  }
    };

    class LinkedList
    {
        Node* head_;

    public:

        LinkedList() : head_(nullptr) {  }

        int Front() const { return head_->data; }

        void InsertBeginning(const int data)
        {
            // if the list is empty, initialise head with data
            if (!head_)
            {
                head_ = new Node(data);
            }
        }

    };
}