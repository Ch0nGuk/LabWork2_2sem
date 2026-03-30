#ifndef MUTABLE_LIST_SEQUENCE_H
#define MUTABLE_LIST_SEQUENCE_H

#include "LinkedList.h"
#include "ListSequence.h"

template <typename T>
class MutableListSequence : public ListSequence<T>
{
public:
    MutableListSequence() : ListSequence<T>() {}
    MutableListSequence(const T* items, int size) : ListSequence<T>(items, size) {}
    MutableListSequence(const LinkedList<T>& other) : ListSequence<T>(other) {}
    
    void Append(const T& item)
    {
        this->data.Append(item);
    }

    void Prepend(const T& item)
    {
        this->data.Prepend(item);
    }

    void InsertAt(int index, const T& item)
    {
        this->data.InsertAt(index, item);
    }

    MutableListSequence<T> GetSubsequence(int startIndex, int endIndex) const
    {
        if (startIndex < 0 || endIndex < 0 || startIndex > endIndex || endIndex >= this->data.GetSize())
        {
            throw std::out_of_range("Index out of range");
        }

        LinkedList<T> sub_list;
        for (int ind = startIndex; ind < endIndex + 1; ind++)
        {
            sub_list.Append(this->Get(ind));
        }

        return MutableListSequence<T>(sub_list);
    }

    MutableListSequence<T> Concat(const Sequence<T>& other) const
    {
        LinkedList<T> newList = this->data;

        for (int ind = 0; ind < other.GetLength(); ind++)
        {
            newList.Append(other.Get(ind));
        }

        return MutableListSequence<T>(newList);
    }

};

#endif // MUTABLE_LIST_SEQUENCE_H