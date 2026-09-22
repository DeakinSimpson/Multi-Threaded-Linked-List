//
// Created by deakin on 9/22/26.
//

#pragma once

namespace LinkedList
{
    template <typename T>
    struct Node
    {
        T data;
        Node* next;

        explicit Node(const T data) : data { data }, next { nullptr } {  }
        explicit Node(const T data, Node* next)
            : data { data }
            , next { next }
        {  }
    };

    template <typename T>
    class LinkedList
    {
        Node<T>* head_;

    public:

        LinkedList() : head_(nullptr) {  }

        T Front() const { return head_->data; }

        T Back() const
        {
            Node<T>* backNode { GetBackNode() };
            return backNode->data;
        }

        void PushFront(const T data)
        {
            // if the list is empty, initialise head with data
            if (!head_)
            {
                head_ = new Node<T>(data);
            }

            Node<T>* temp { new Node<T>(data, head_) };
            head_ = temp;
        }

        void PushBack(const T data)
        {
            Node<T>* backNode { GetBackNode() };
            backNode->next = new Node<T>(data);
        }

    private:

        Node<T>* GetBackNode() const
        {
            Node<T>* cur { head_ };
            while (cur->next)
            {
                cur = cur->next;
            }

            return cur;
        }

    };
}