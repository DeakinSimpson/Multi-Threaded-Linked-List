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
        size_t size_;

    public:

        LinkedList() : head_ { nullptr }, size_ { 0 } {  }

        /**
         *
         * @return Number of elements in the list
         */
        size_t Size() const { return size_; }

        /**
         *
         * @return True if list is empty, false otherwise
         */
        bool Empty() const { return head_; }

        /**
         *
         * @return The head of the list
         */
        T Front() const { return head_->data; }

        /**
         *
         * @return The tail of the list
         */
        T Back() const
        {
            Node<T>* backNode { GetTailPointer() };
            return backNode->data;
        }

        /**
         *
         * @param data The value that will become the new head
         */
        void PushFront(const T data)
        {
            // if the list is empty, initialise head with data
            if (!head_)
            {
                head_ = new Node<T>(data);
            }

            Node<T>* temp { new Node<T>(data, head_) };
            head_ = temp;

            ++size_;
        }

        /**
         *
         * @param data The value that will become the new tail
         */
        void PushBack(const T data)
        {
            Node<T>* backNode { GetTailPointer() };
            backNode->next = new Node<T>(data);

            ++size_;
        }

    private:
        /**
         *
         * @return Pointer to the tail node
         */
        Node<T>* GetTailPointer() const
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