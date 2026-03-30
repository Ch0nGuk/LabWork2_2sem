#ifndef ARRAY_SEQUENCE_H
#define ARRAY_SEQUENCE_H

#include "Sequence.h"
#include "DynamicArray.h"
#include "ListSequence.h"

template <typename T> 
class ArraySequence : public Sequence<T>
{
protected:
    DynamicArray<T> data;
public:
    ArraySequence() : data() {}
    ArraySequence(const T* items, int size) : data(items, size) {}
    ArraySequence(const DynamicArray<T>& other) : data(other) {}

    virtual ArraySequence<T>* Instance() override = 0;

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

        return CreateSequence(subData);
    }

    Sequence<T>* Concat(const Sequence<T>& other) const override
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

        return CreateSequence(new_arr);
    }

    Sequence<T>* Slice(int startIndex, int count, const Sequence<T>& replacement) const override
    {
        int this_size = this->GetLength();
        if (startIndex < 0 || count < 0 || startIndex > this_size || startIndex + count > this_size)
        {
            throw std::out_of_range("Index out of range");
        }

        int replacement_size = replacement.GetLength();
        DynamicArray<T> new_arr(this_size - count + replacement_size);
        int new_index = 0;

        for (int index = 0; index < startIndex; index++)
        {
            new_arr.Set(new_index, this->Get(index));
            new_index++;
        }

        for (int index = 0; index < replacement_size; index++)
        {
            new_arr.Set(new_index, replacement.Get(index));
            new_index++;
        }

        for (int index = startIndex + count; index < this_size; index++)
        {
            new_arr.Set(new_index, this->Get(index));
            new_index++;
        }

        return CreateSequence(new_arr);
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
                    parts->Append(CreateSequence(DynamicArray<T>()));
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
            parts->Append(CreateSequence(DynamicArray<T>()));
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
        DynamicArray<T> mapped(size);

        for (int ind = 0; ind < size; ind++)
        {
            mapped.Set(ind, func(this->Get(ind)));
        }

        return CreateSequence(mapped);
    }

    Sequence<T>* Where(bool (*predicate)(T)) const override
    {
        int size = this->GetLength();
        int new_size = 0;
        for (int ind = 0; ind < size; ind++)
        {
            if (predicate(this->Get(ind))) new_size++;
        }

        DynamicArray<T> new_arr(new_size);
        int new_ind = 0;
        for (int ind = 0; ind < size; ind++)
        {
            if (predicate(this->Get(ind))) 
            {
                new_arr.Set(new_ind, this->Get(ind));
                new_ind++;
            }
        }

        return CreateSequence(new_arr);
    }

protected:
    Sequence<T>* AppendInternal(const T& item) override
    {
        int oldSize = this->data.GetSize();
        this->data.Resize(oldSize + 1);
        this->data.Set(oldSize, item);

        return this;
    }

    Sequence<T>* PrependInternal(const T& item) override
    {
        int oldSize = this->data.GetSize();
        DynamicArray<T> tmp_array = this->data;
        this->data.Resize(oldSize + 1);
        for (int index = 0; index < oldSize; index++)
        {
            this->data.Set(index + 1, tmp_array.Get(index));
        }
        this->data.Set(0, item);

        return this;
    }

    Sequence<T>* InsertAtInternal(int index, const T& item) override
    {
        if (index < 0 || index > this->data.GetSize())
        {
            throw std::out_of_range("Index out of range");
        }
        if (index == 0)
        {
            return PrependInternal(item);
        }
        if (index == this->data.GetSize())
        {
            return AppendInternal(item);
        }
        int oldSize = this->data.GetSize();
        DynamicArray<T> tmp_array = this->data;
        this->data.Resize(oldSize + 1);
        for (int ind = index; ind < oldSize; ind++)
        {
            this->data.Set(ind + 1, tmp_array.Get(ind));
        }
        this->data.Set(index, item);

        return this;
    }

    virtual ArraySequence<T>* CreateSequence(const DynamicArray<T>& data) const = 0;

};

#endif // ARRAY_SEQUENCE_H
