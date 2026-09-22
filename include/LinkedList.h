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
        explicit Node(const int data) : data { data }, next { nullptr } {  }
        explicit Node(const int data, Node* next)
            : data { data }
            , next { next }
        {  }
    };

    class LinkedList
    {
        Node* head_;

    public:

        LinkedList() : head_(nullptr) {  }

        int Front() const { return head_->data; }

        int Back() const
        {
            Node* cur { head_ };
            while (cur->next)
            {
                cur = cur->next;
            }

            return cur->data;
        }

        void PushFront(const int data)
        {
            // if the list is empty, initialise head with data
            if (!head_)
            {
                head_ = new Node(data);
            }

            Node* temp { new Node(data, head_) };
            head_ = temp;
        }



    };
}