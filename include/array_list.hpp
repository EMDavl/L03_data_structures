#pragma once

#include <algorithm>  // copy
#include <cassert>    // assert
#include <stdexcept>  // out_of_range
#include <string>     // to_string

namespace itis {

/**
 * Структура данных "массив переменной длины".
 * Является одной из реализаций ADT Abstract List.
 */
    struct ArrayList {

    public:
        static constexpr int kInitCapacity = 10;
        static constexpr int kCapacityIncreaseCoefficient = 10;

    private:
        int size_{0};      // кол-во элементов
        int capacity_{0};  // емкость
        char *data_{nullptr};

    public:
        // default constructor
        ArrayList() : capacity_{kInitCapacity}, data_{new char[kInitCapacity]} {

        }

        /**
         * Создание массива переменной длины.
         *
         * @param capacity - начальная емкость массива.
         */
        explicit ArrayList(int capacity) {
            capacity_ = capacity;
            data_ = new char[capacity];
        }

        ~ArrayList() {
            delete[] data_;
            data_ = nullptr;
            size_ = 0;
            capacity_ = 0;
        }

        /**
         * Добавление элемента в конец массива.
         * Сложность операции - O(1) или O(n) в зависимости от необходимости увеличения размеров массива.
         *
         * При недостаточной емкости (capacity) массива осуществляется его расширение с сохранением предыдущих элементов.
         * @param element - значение элемента
         */
        void PushBack(char element) {
            if (capacity_ == size_) {
                resize(capacity_ + kCapacityIncreaseCoefficient);
            }
            data_[size_] = element;
            size_++;
        }

        /**
         * Вставка элемента в массив по индексу.
         * Сложность операции - O(n).
         *
         * Все элементы, находящиеся на позиции вставки и справа от нее, сдвигаются на единицу вправо.
         * При недостаточной емкомсти (capacity) массива осуществляется его расширение с сохранением предыдущих элементов.
         *
         * @param index - позиция для вставки
         * @param element - значение элемента
         *
         * @throws выбрасывает ошибку out_of_range при работе с некорректным индексом.
         */
        void Insert(int index, char element) {
            check_out_of_range(index);
            if (size_ == capacity_) {
                resize(capacity_ + kCapacityIncreaseCoefficient);
            }
            for (int i = size_; i > index; i--) {
                data_[i] = data_[i-1];
            }
            size_++;
            data_[index] = element;
        }

        /**
         * Удаление элемента массива по индексу.
         * Сложность операции - O(n).
         *
         * Все элементы, стоящие справа от удаленного элемента сдвигаются влево на единицу.
         *
         * @param index - индекс удаляемого элемента
         * @return значение удаленного элемента
         *
         * @throws выбрасывает ошибку out_of_range при работе с некорректным индексом.
         */
        char Remove(int index) {
            check_out_of_range(index);
            char elem = data_[index];

            for (int i = index; i < size_; ++i) {
                data_[i] = data_[i + 1];
            }

            size_--;
            return elem;
        }

        /**
         * Удаление всех элементов массива.
         * Сложность операции - O(1).
         *
         * Емкость (capacity) массива остается прежним.
         */
        void Clear() {
            size_ = 0;
        }

        /**
         * Получение элемента массива по индексу.
         * Сложность операции - O(1).
         *
         * @param index - индекс элемента
         * @return значение элемента по индексу
         *
         * @throws выбрасывает ошибку out_of_range при работе с некорректным индексом.
         */
        char Get(int index) const {
            check_out_of_range(index);
            char *a = data_ + index;
            return *a;
        }

        /**
         * Вычисление индекса элемента.
         * Сложность операции - O(n).
         *
         * @param element - значение элемента
         * @return индекс элемента или -1 при остутствии элемента в массиве
         */
        int IndexOf(char element) const {
            for (int i = 0; i < size_; ++i) {
                if (data_[i] == element) {
                    return i;
                }
            }
            return -1;
        }

        /**
         * Проверка наличия элемента в массиве.
         * Сложность операции - O(n).
         *
         * @param element - значение элемента
         * @return при наличии элемента - true, иначе - false
         */
        bool Contains(char element) const {
            for (int i = 0; i < size_; ++i) {
                if (element == data_[i]) {
                    return true;
                }
            }
            return false;
        }

        /**
         * Проверка наличия хотя бы одного элемента в массиве.
         * Сложность операции - O(1).
         *
         * @return при наличии хотя бы одного элемента - true, иначе - false
         */
        bool IsEmpty() const {
            return size_ == 0;
        }

        int GetSize() const {
            return size_;
        }

        int GetCapacity() const {
            return capacity_;
        }

    private:
        /**
         * Увеличение емкости массива.
         * Сложность операции - O(n).
         *
         * Элементы массива должны сохраниться на своих позициях.
         *
         * @param new_capacity - новая емкость массива (должна быть больше предыдущей)
         */
        void resize(int new_capacity) {
            assert(new_capacity > capacity_);
            char *time_data = new char[new_capacity];
            std::copy(data_, data_ + size_, time_data);
            delete[] data_;
            data_ = time_data;
            capacity_ = new_capacity;
        }

    private:
        void check_out_of_range(int index) const;
    };

// определение методов

    void ArrayList::check_out_of_range(int index) const {
        if (index >= size_) {
            throw std::out_of_range("index is out of range: " + std::to_string(size_));
        }
    }

}  // namespace itis
