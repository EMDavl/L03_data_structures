#pragma once

#include <cassert>    // assert
#include <stdexcept>  // out_of_range
#include <string>     // to_string

namespace itis {

/**
 * Структура "узел".
 * Хранит в себе данные и указатель на следующий узел.
 */
    struct Node {
        char data;
        Node *next_;  // указатель на следующий узел
    };

    struct LinkedList {
    private:
        int size_{0};

        Node *head_{nullptr};
        Node *tail_{nullptr};

    public:
        // default constructor
        LinkedList() = default;

        ~LinkedList() {
            size_ = 0;
            head_ = nullptr;
            tail_ = nullptr;
        }

        /**
         * Добавление элемента в конец списка.
         * Сложность операции - O(1).
         *
         * @param element - значение элемента
         */
        void PushBack(char element) {
            Node *n = new Node;
            n->data = element;
            n->next_ = nullptr;
            tail_->next_ = n;
            tail_ = n;
        }

        /**
         * Вставка элемента в список по индексу.
         * Сложность операции вставки - O(1).
         * Сложность операции поиска узла - O(n).
         *
         * @param index - позиция для вставки
         * @param element - значение элемента
         *
         * @throws выбрасывает ошибку out_of_range при работе с некорректным индексом.
         */
        void Insert(int index, char element) {
            check_out_of_range(index);
            Node *nextNode = head_;
            for (int i = 0; i < index -1; ++i) {
                nextNode = nextNode->next_;
            }
            Node *newNode = new Node;
            newNode->data = element;

            newNode->next_ = nextNode->next_;
            nextNode->next_ = newNode;
        }

        /**
         * Удаление элемента списка по индексу.
         * Сложность операции удаления - O(1).
         * Сложность операции поиска узла - O(n).
         *
         * @param index - индекс удаляемого элемента
         * @return значение удаленного элемента
         *
         * @throws выбрасывает ошибку out_of_range при работе с некорректным индексом.
         */
        char Remove(int index) {
            check_out_of_range(index);
            Node *nextNode = head_;
            for (int i = 0; i < index-1; ++i) {
                nextNode = nextNode->next_;
            }
            Node *indexedNode = nextNode->next_;
            nextNode->next_ = nextNode->next_->next_;
            char nc = indexedNode->data;
            delete indexedNode;
            return nc;
        }

        /**
         * Удаление всех элементов списка. Сложность операции - O(n).
         */
        void Clear() {
            Node *previousNode;
            Node *nextNode = head_;
            for (int i = 0; i < tail_ - head_ - 1; ++i) {
                previousNode = nextNode;
                nextNode = nextNode->next_;
                delete[] previousNode;
            }
            delete[] nextNode;
        }

        /**
         * Получение элемента списка по индексу.
         * Сложность операции - O(n).
         *
         * @param index - индекс элемента
         * @return значение элемента по индексу
         *
         * @throws выбрасывает ошибку out_of_range при работе с некорректным индексом.
         */
        char Get(int index) const {
            check_out_of_range(index);
            Node *newNode = head_;
            for (int i = 0; i < index; ++i) {
                newNode = newNode->next_;
            }
            return newNode->data;
        }

        /**
         * Вычисление индекса элемента.
         * Сложность операции - O(n).
         *
         * @param element - значение элемента
         * @return индекс элемента или -1 при остутствии элемента в списке
         */
        int IndexOf(char element) const {
            Node *nextNode = head_;
            for (int i = 0; i < tail_ - head_; ++i) {
                if(nextNode->data == element){
                    return i;
                }
                if(nextNode == tail_) return -1;
                nextNode = nextNode->next_;
            }
            return -1;
        }

        /**
         * Проверка наличия хотя бы одного элемента в массиве.
         * Сложность операции - O(1).
         *
         * @return при наличии хотя бы одного элемента - true, иначе - false
         */
        bool IsEmpty() const {
            return head_ != nullptr;
        }

        int GetSize() const {
            return size_;
        }

        int GetCapacity() const {
            return size_;
        }

    private:

        /**
         * Поиск узла списка по значению элемента.
         * Сложность операции - O(n).
         *
         * Если в списке несколько элементов с одинаковым значением,
         * то возвращается первый встретившийся узел.
         *
         * @param element - значение элемента в узле
         * @return указатель на узел или nullptr - при отсутствии узла с таким значением
         */
        Node *find_node(char element) const {
            Node *nextNode = head_;
            for (int i = 0; i < tail_ - head_; ++i) {
                if(nextNode->data == element) return nextNode;
                if(nextNode == tail_) return nullptr;
                nextNode = nextNode->next_;
            }
            return nullptr;
        }

        /**
         * Поиск узла списка по значению элемента.
         * Сложность операции - O(n).
         *
         * @param element - значение элемента в узле
         * @return указатель на узел или nullptr - при отсутствии узла с таким значением
         */
        Node *find_node(int index) const {
            assert(index >= 0 && index < size_);
            Node *nextNode = head_;
            for (int i = 0; i < index; ++i) {
                nextNode = nextNode->next_;
            }

            return nextNode;
        }


        void check_out_of_range(int index) const;
    };

// реализация методов

    void LinkedList::check_out_of_range(int index) const {
        if (index >= size_) {
            throw std::out_of_range("index is out of range: " + std::to_string(size_));
        }
    }

}  // namespace itis