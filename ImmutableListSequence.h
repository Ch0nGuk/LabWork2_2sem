#ifndef IMMUTABLE_LIST_SEQUENCE_H
#define IMMUTABLE_LIST_SEQUENCE_H

#include "LinkedList.h"
#include "ListSequence.h"

template <typename T>
class ImmutableListSequence : public ListSequence<T>
{
public:
    ImmutableListSequence() : ListSequence<T>() {}
    ImmutableListSequence(const T* items, int size) : ListSequence<T>(items, size) {}
    ImmutableListSequence(const LinkedList<T>& other) : ListSequence<T>(other) {}

    ImmutableListSequence<T> Append(const T& item) const
    {
        LinkedList<T> newList = this->data;
        newList.Append(item);
        return ImmutableListSequence<T>(newList);
    }

    ImmutableListSequence<T> Prepend(const T& item) const
    {
        LinkedList<T> newList = this->data;
        newList.Prepend(item);
        return ImmutableListSequence<T>(newList);
    }

    ImmutableListSequence<T> InsertAt(int index, const T& item) const
    {
        LinkedList<T> newList = this->data;
        newList.InsertAt(index, item);
        return ImmutableListSequence<T>(newList);
    }

    ImmutableListSequence<T> GetSubsequence(int startIndex, int endIndex) const
    {
        if (startIndex < 0 || endIndex < 0 || startIndex > endIndex || endIndex >= this->GetLength())
        {
            throw std::out_of_range("Index out of range");
        }

        LinkedList<T> subList;
        for (int ind = startIndex; ind <= endIndex; ind++)
        {
            subList.Append(this->Get(ind));
        }

        return ImmutableListSequence<T>(subList);
    }

    ImmutableListSequence<T> Concat(const Sequence<T>& other) const
    {
        LinkedList<T> newList = this->data;

        for (int ind = 0; ind < other.GetLength(); ind++)
        {
            newList.Append(other.Get(ind));
        }

        return ImmutableListSequence<T>(newList);
    }
};

#endif // IMMUTABLE_LIST_SEQUENCE_H
