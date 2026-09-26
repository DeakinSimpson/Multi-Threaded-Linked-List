    //
    // Created by deakin on 9/22/26.
    //

    #pragma once

    namespace MTList
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
        class MTList
        {
            Node<T>* head_;
            size_t size_;

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
                reference operator*() const { return m_ptr->data; }
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
                friend class MTList;    // allows linked list to read m_ptr
            };

            /**
             *
             * @return Iterator of the front of the list (the head)
             */
            Iterator begin() const
            {
                return Iterator(head_);
            }

            /**
             *
             * @return Iterator of the end of the list, out of bounds (tail)
             */
            Iterator end() const
            {
                return Iterator(nullptr);
            }

            MTList() : head_ { nullptr }, size_ { 0 } {  }

            MTList(std::initializer_list<T> lst)
                : head_ { nullptr }, size_ { 0 }
            {
                for (const auto& l : lst)
                {
                    PushBack(l);
                }
            }

            /**
             *
             * @return Number of elements in the list
             */
            size_t Size() const { return size_; }

            /**
             *
             * @return True if list is empty, false otherwise
             */
            bool Empty() const { return !head_; }

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
                    return;
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
                if (!head_)
                {
                    head_ = new Node<T>(data);
                    return;
                }

                Node<T>* backNode { GetTailPointer() };
                backNode->next = new Node<T>(data);

                ++size_;
            }

            /**
             *
             * @param it Iterator of the Node to be removed
             * @return Iterator of the next Node in the linked list
             */
            Iterator Erase( const Iterator& it)
            {
                // get the pointer of the target
                Node<T>* target { it.m_ptr };

                // return nullptr (end) if invalid iterator
                if (!target) { return end(); }

                // if head skip prev updating as there is no prev
                if (target == head_)
                {
                    head_ = head_->next;
                } else
                {
                    Node<T>* prev { head_ };

                    // prev is not at end and != to target, loop until at target
                    while (prev && prev->next != target)
                    {
                        prev = prev->next;
                    }

                    // if prev == nullptr then not found
                    if (!prev) { return end(); }

                    // update prev->next to skip over target
                    prev->next = target->next;
                }

                // get next valuie and delete the node
                Node<T>* next { target->next };
                delete target;
                --size_;

                return Iterator(next);
            }

            void Clear()
            {
                Node<T>* cur { head_ };


                while (cur)
                {
                    auto next { cur->next };
                    delete cur;
                    cur = next;
                }

                head_ = nullptr;
                size_ = 0;
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