#ifndef MUTABLE_ARRAY_SEQUENCE_H
#define MUTABLE_ARRAY_SEQUENCE_H

#include "ArraySequence.h"
#include "DynamicArray.h"


template <typename T> 
class MutableArraySequence : public ArraySequence<T>
{
public:
    MutableArraySequence() : ArraySequence<T>() {}
    MutableArraySequence(const T* items, int size) : ArraySequence<T>(items, size) {}
    MutableArraySequence(const DynamicArray<T>& other) : ArraySequence<T>(other) {}

    void Append(const T& item) 
    {
        int oldSize = this->data.GetSize();
        this->data.Resize(oldSize + 1);
        this->data.Set(oldSize, item);
    }

    void Prepend(const T& item)
    {
        int oldSize = this->data.GetSize();
        DynamicArray<T> tmp_array = this->data;
        this->data.Resize(oldSize + 1);
        for (int index = 0; index < oldSize; index++)
        {
            this->data.Set(index + 1, tmp_array.Get(index));
        }
        this->data.Set(0, item);
    }

    void InsertAt(int index, const T& item)
    {
        if (index < 0 || index > this->data.GetSize())
        {
            throw std::out_of_range("Index out of range");
        }
        if (index == 0)
        {
            Prepend(item);
            return;
        }
        if (index == this->data.GetSize())
        {
            Append(item);
            return;
        }
        int oldSize = this->data.GetSize();
        DynamicArray<T> tmp_array = this->data;
        this->data.Resize(oldSize + 1);
        for (int ind = index; ind < oldSize; ind++)
        {
            this->data.Set(ind + 1, tmp_array.Get(ind));
        }
        this->data.Set(index, item);
    }

    MutableArraySequence<T> GetSubsequence(int startIndex, int endIndex) const
    {
        if (startIndex < 0 || endIndex < 0 || startIndex > endIndex || endIndex >= this->data.GetSize())
        {
            throw std::out_of_range("Index out of range");
        }

        int sub_size = endIndex - startIndex + 1;
        DynamicArray<T> subData(sub_size);
        for (int ind = 0; ind < sub_size; ind++)
        {
            subData.Set(ind, this->data.Get(ind + startIndex));
        }

        return MutableArraySequence<T>(subData);
    }

    MutableArraySequence<T> Concat(const Sequence<T>& other) const
    {
        int this_size = this->data.GetSize();
        int other_size = other.GetLength();
        DynamicArray<T> new_arr(this_size + other_size);
        for (int ind = 0; ind < this_size; ind++)
        {
            new_arr.Set(ind, this->data.Get(ind));
        }
        for (int ind = 0; ind < other_size; ind++)
        {
            new_arr.Set(ind + this_size, other.Get(ind));
        }

        return MutableArraySequence<T>(new_arr);
    }
};

#endif // MUTABLE_ARRAY_SEQUENCE_H
