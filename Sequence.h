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
};

#endif // SEQUENCE_H