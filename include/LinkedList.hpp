    //
    // Created by deakin on 9/22/26.
    //

/* Resources:
 * - Simple, Fast, and Practical Non-Blocking and Blocking Concurrent Queue
 *   Algorithms* - Michael & Scott
 */

#pragma once
#include <memory>


    namespace ThreadSafeList
{
    template <typename T>
    struct Node
    {
        std::unique_ptr<T> data;
        Node* next { nullptr };

        Node() = default;

        explicit Node(const T data, Node* next = nullptr)
            : data { std::make_unique<T>(std::move(data)) }
            , next { next }
        {  }
    };

    template <typename T>
    class ThreadSafeList
    {
        Node<T>* head_;
        std::atomic<size_t> size_ { 0 };
        std::mutex mtx_;

    public:
        struct Iterator
        {
            using iterator_category = std::forward_iterator_tag;
            using difference_type   = std::ptrdiff_t;
            using value_type        = T;
            using pointer           = T*;
            using reference         = T&;

            Iterator(Node<T>* ptr) : m_ptr { ptr } {  }

            // getting the values a reference is pointing to
            reference operator*() const { return *m_ptr->data; }
            pointer operator->() const { return &m_ptr->data; }

            // Prefix increment (gets next node)
            Iterator& operator++()
            {
                m_ptr = m_ptr->next;
                return *this;
            }

            // Postfix increment
            Iterator operator++(int)
            {
                Iterator tmp = *this;
                ++(*this);
                return tmp;
            }

            friend bool operator== (const Iterator& a, const Iterator& b)
            {
                return a.m_ptr == b.m_ptr;
            }

            friend bool operator!= (const Iterator& a, const Iterator& b)
            {
                return a.m_ptr != b.m_ptr;
            }

        private:
            Node<T>* m_ptr;
            friend class ThreadSafeList;    // allows linked list to read m_ptr
        };

        /**
         *
         * @return Iterator of the front of the list (the head)
         */
        Iterator begin() const
        {
            return Iterator(head_->next);
        }

        /**
         *
         * @return Iterator of the end of the list, out of bounds (tail)
         */
        Iterator end() const
        {
            return Iterator(nullptr);
        }

        ThreadSafeList() : head_ { new Node<T>() }, size_ { 0 } {  }

        ThreadSafeList(std::initializer_list<T> lst)
            : head_ { new Node<T>() }, size_ { 0 }
        {
            for (const auto& l : lst)
            {
                push_back(l);
            }
        }

        ~ThreadSafeList()
        {
            clear();
            delete head_;
        }

        ThreadSafeList(const ThreadSafeList&) = delete;
        ThreadSafeList& operator=(const ThreadSafeList&) = delete;

        /**
         *
         * @return Number of elements in the list
         */
        size_t size() const
        {
            return size_.load(std::memory_order_relaxed);
        }

        /**
         *
         * @return Number of elements in the list O(n)
         */
        size_t size_nt() const
        {
            auto cur { head_->next };
            size_t size {};

            while (cur)
            {
                cur = cur->next;
                ++size;
            }

            return size;
        }

        /**
         *
         * @return True if list is empty, false otherwise
         */
        bool empty() const
        {
            return size_.load(std::memory_order_relaxed) == 0;
        }

        /**
         *
         * @return The head of the list
         */
        T front() const { return *head_->next->data; }

        /**
         *
         * @return The tail of the list
         */
        T back() const
        {
            auto cur { head_ };
            while (cur->next) cur = cur->next;
            return *cur->data;
        }

        /**
         *
         * @param data The value that will become the new head
         */
        void push_front(const T data)
        {
            std::lock_guard<std::mutex> lock(mtx_);
            head_->next = new Node<T>(std::move(data), head_->next);
            size_.fetch_add(1, std::memory_order_relaxed);
        }

        /**
         *
         * @param data The value that will become the new tail
         */
        void push_back(const T data)
        {
            std::lock_guard<std::mutex> lock(mtx_);
            Node<T>* cur { head_ };
            while (cur->next) cur = cur->next;
            cur->next = new Node<T>(std::move(data));
            size_.fetch_add(1, std::memory_order_relaxed);
        }

        /**
        *
        * @param it Iterator of the Node to be removed
        * @return Iterator of the next Node in the linked list
        */
        Iterator erase(const Iterator& it)
        {
            // get the pointer of the target
            Node<T>* target { it.m_ptr };
            if (!target)
            {
                return end();
            }

            Node<T>* prev { head_ };

            // prev is not at end and != to target, loop until at target
            while (prev && prev->next != target)
            {
                prev = prev->next;
            }

            // if prev == nullptr then not found
            if (!prev)
            {
                return end();
            }

            // update prev->next to skip over target
            prev->next = target->next;

            delete target;

            size_.fetch_sub(1, std::memory_order_relaxed);

            return Iterator(prev->next);
        }

         void clear()
         {
             Node<T>* cur { head_->next };

             while (cur)
             {
                 auto next { cur->next };
                 delete cur;
                 cur = next;
             }

             head_->next = nullptr;
             size_.store(0, std::memory_order_relaxed);
        }
    };
}
