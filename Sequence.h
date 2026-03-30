#ifndef SEQUENCE_H
#define SEQUENCE_H

template <typename T>
class Sequence
{
public:
    virtual ~Sequence() = default;

    virtual const T& GetFirst() const = 0;
    virtual const T& GetLast() const = 0;
    virtual const T& Get(int index) const = 0;
    virtual int GetLength() const = 0;

    virtual Sequence<T>* Append(const T& item) = 0;
    virtual Sequence<T>* Prepend(const T& item) = 0;
    virtual Sequence<T>* InsertAt(int index, const T& item) = 0;
    virtual Sequence<T>* GetSubsequence(int start_index, int end_index) const = 0;
    virtual Sequence<T>* Concat(const Sequence<T>& other) const = 0;
    virtual Sequence<T>* Slice(int startIndex, int count, const Sequence<T>& replacement) const = 0;
    virtual Sequence<Sequence<T>*>* Split(const T& separator) const = 0;

    virtual Sequence<T>* Instance() = 0;

    virtual Sequence<T>* Map(T (*func)(T)) const = 0;
    virtual Sequence<T>* Where(bool (*predicate)(T)) const = 0;
    T Reduce(T (*func)(T, T), T startValue) const
    {
        T result = startValue;
        for (int index = 0; index < GetLength(); index++)
        {
            result = func(result, Get(index));
        }
        return result;
    }



protected:
    virtual Sequence<T>* AppendInternal(const T& item) = 0;
    virtual Sequence<T>* PrependInternal(const T& item) = 0;
    virtual Sequence<T>* InsertAtInternal(int index, const T& item) = 0;
};

#endif // SEQUENCE_H
