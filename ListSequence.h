#ifndef LIST_SEQUENCE_H
#define LIST_SEQUENCE_H

#include "Sequence.h"
#include "LinkedList.h"

template <typename T> 
class ListSequence : public Sequence<T>
{
protected:
    LinkedList <T> data;

public:
    ListSequence() : data() {}
    ListSequence(const T* items, int size) : data(items, size) {}
    ListSequence(const LinkedList<T>& other) : data(other) {}

    const T& GetFirst() const override
    {
        return data.GetFirst();
    }
    const T& GetLast() const override
    {
        return data.GetLast();
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

#endif // LIST_SEQUENCE_H