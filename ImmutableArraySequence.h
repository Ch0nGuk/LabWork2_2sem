#ifndef IMMUTABLE_ARRAY_SEQUENCE_H
#define IMMUTABLE_ARRAY_SEQUENCE_H

#include "ArraySequence.h"
#include "DynamicArray.h"

template <typename T>
class ImmutableArraySequence : public ArraySequence<T>
{
public:
    ImmutableArraySequence() : ArraySequence<T>() {}
    ImmutableArraySequence(const T* items, int size) : ArraySequence<T>(items, size) {}
    ImmutableArraySequence(const DynamicArray<T>& other) : ArraySequence<T>(other) {}

    ImmutableArraySequence<T> Append(const T& item) const
    {
        int oldSize = this->GetLength();
        DynamicArray<T> new_arr(oldSize + 1);
        for (int ind = 0; ind < oldSize; ind++)
        {
            new_arr.Set(ind, this->data.Get(ind));
        }
        new_arr.Set(oldSize, item);

        return ImmutableArraySequence<T>(new_arr);
    }

    ImmutableArraySequence<T> Prepend(const T& item) const
    {
        int oldSize = this->GetLength();
        DynamicArray<T> new_arr(oldSize + 1);
        for (int ind = 0; ind < oldSize; ind++)
        {
            new_arr.Set(ind + 1, this->data.Get(ind));
        }
        new_arr.Set(0, item);

        return ImmutableArraySequence<T>(new_arr);
    }

    ImmutableArraySequence<T> InsertAt(int index, const T& item) const
    {
        if (index < 0 || index > this->data.GetSize())
        {
            throw std::out_of_range("Index out of range");
        }
        if (index == 0)
        {
            return Prepend(item);
        }
        if (index == this->data.GetSize())
        {
            return Append(item);
        }
        
        int oldSize = this->GetLength();
        DynamicArray<T> new_arr(oldSize + 1);
        for (int ind = 0; ind < index; ind++)
        {
            new_arr.Set(ind, this->data.Get(ind));
        }
        new_arr.Set(index, item);
        for (int ind = index; ind < oldSize; ind++)
        {
            new_arr.Set(ind + 1, this->data.Get(ind));
        }

        return ImmutableArraySequence<T>(new_arr);
    }

    ImmutableArraySequence<T> GetSubsequence(int startIndex, int endIndex) const
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

        return ImmutableArraySequence<T>(subData);
    }

    ImmutableArraySequence<T> Concat(const Sequence<T>& other) const
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

        return ImmutableArraySequence<T>(new_arr);
    }
};

#endif // IMMUTABLE_ARRAY_SEQUENCE_H
