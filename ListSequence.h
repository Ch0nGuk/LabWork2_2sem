#ifndef LIST_SEQUENCE_H
#define LIST_SEQUENCE_H

#include "Sequence.h"
#include "LinkedList.h"

template <typename T> 
class ListSequence : public Sequence<T>
{
protected:
    LinkedList<T> data;

public:
    ListSequence() : data() {}
    ListSequence(const T* items, int size) : data(items, size) {}
    ListSequence(const LinkedList<T>& other) : data(other) {}

    ListSequence<T>* Instance() override
    {
        return this;
    }

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

    Sequence<T>* Append(const T& item) override
    {
        return Instance()->AppendInternal(item);
    }

    Sequence<T>* Prepend(const T& item) override
    {
        return Instance()->PrependInternal(item);
    }

    Sequence<T>* InsertAt(int index, const T& item) override
    {
        return Instance()->InsertAtInternal(index, item);
    }

    Sequence<T>* GetSubsequence(int startIndex, int endIndex) const override
    {
        if (startIndex < 0 || endIndex < 0 || startIndex > endIndex || endIndex >= data.GetSize())
        {
            throw std::out_of_range("Index out of range");
        }

        return new ListSequence<T>(data.GetSubList(startIndex, endIndex));
    }

    Sequence<T>* Concat(const Sequence<T>& other) const override
    {
        LinkedList<T> otherList;
        for (int index = 0; index < other.GetLength(); index++)
        {
            otherList.Append(other.Get(index));
        }

        return new ListSequence<T>(data.Concat(otherList));
    }

    Sequence<T>* Slice(int startIndex, int count, const Sequence<T>& replacement) const override
    {
        int this_size = this->GetLength();
        if (startIndex < 0 || count < 0 || startIndex > this_size || startIndex + count > this_size)
        {
            throw std::out_of_range("Index out of range");
        }

        LinkedList<T> new_list;

        for (int index = 0; index < startIndex; index++)
        {
            new_list.Append(this->Get(index));
        }

        for (int index = 0; index < replacement.GetLength(); index++)
        {
            new_list.Append(replacement.Get(index));
        }

        for (int index = startIndex + count; index < this_size; index++)
        {
            new_list.Append(this->Get(index));
        }

        return new ListSequence<T>(new_list);
    }

    Sequence<Sequence<T>*>* Split(const T& separator) const override
    {
        ListSequence<Sequence<T>*>* parts = new ListSequence<Sequence<T>*>();
        int part_start = 0;

        for (int index = 0; index < this->GetLength(); index++)
        {
            if (this->Get(index) == separator)
            {
                if (part_start == index)
                {
                    parts->Append(new ListSequence<T>());
                }
                else
                {
                    parts->Append(this->GetSubsequence(part_start, index - 1));
                }
                part_start = index + 1;
            }
        }

        if (part_start == this->GetLength())
        {
            parts->Append(new ListSequence<T>());
        }
        else
        {
            parts->Append(this->GetSubsequence(part_start, this->GetLength() - 1));
        }

        return parts;
    }

    Sequence<T>* Map(T (*func)(T)) const override
    {
        int size = this->GetLength();
        ListSequence<T> mapped;

        for (int ind = 0; ind < size; ind++)
        {
            mapped.Append(func(this->Get(ind)));
        }

        return new ListSequence<T>(mapped);
    }

    Sequence<T>* Where(bool (*predicate)(T)) const override
    {
        int size = this->GetLength();
        LinkedList<T> new_list;
        for (int ind = 0; ind < size; ind++)
        {
            if (predicate(this->Get(ind))) 
            {
                new_list.Append(this->Get(ind));
            }
        }

        return new ListSequence<T>(new_list);
    }

protected:
    Sequence<T>* AppendInternal(const T& item) override
    {
        data.Append(item);
        return this;
    }

    Sequence<T>* PrependInternal(const T& item) override
    {
        data.Prepend(item);
        return this;
    }

    Sequence<T>* InsertAtInternal(int index, const T& item) override
    {
        data.InsertAt(index, item);
        return this;
    }
};

#endif // LIST_SEQUENCE_H
