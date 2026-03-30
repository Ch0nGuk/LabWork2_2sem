#ifndef ARRAY_SEQUENCE_H
#define ARRAY_SEQUENCE_H

#include "Sequence.h"
#include "DynamicArray.h"

template <typename T> 
class ArraySequence : public Sequence<T>
{
protected:
    DynamicArray<T> data;
public:
    ArraySequence() : data() {}
    ArraySequence(const T* items, int size) : data(items, size) {}
    ArraySequence(const DynamicArray<T>& other) : data(other) {}

    const T& GetFirst() const override
    {
        return data.Get(0);
    }
    const T& GetLast() const override
    {
        return data.Get(data.GetSize() - 1);
    }
    const T& Get(int index) const override
    {
        return data.Get(index);
    }
    int GetLength() const override
    {
        return data.GetSize();
    }
};

#endif // ARRAY_SEQUENCE_H