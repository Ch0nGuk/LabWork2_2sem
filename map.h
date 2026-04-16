#ifndef MAP_H
#define MAP_H

#include "IEnumerator.h"
#include "Sequence.h"
#include "sequence_factory.h"

template <typename T, typename T2, typename Mapper>
Sequence<T2>* Map(const Sequence<T>& source, Mapper mapper, const SequenceFactory<T2>& factory)
{
    Sequence<T2>* result = factory.Create();
    IEnumerator<T>* enumerator = source.GetEnumerator();

    try
    {
        while (enumerator->MoveNext())
        {
            Sequence<T2>* next = result->Append(mapper(enumerator->Current()));
            if (next != result)
            {
                delete result;
                result = next;
            }
        }
    }
    catch (...)
    {
        delete enumerator;
        delete result;
        throw;
    }

    delete enumerator;
    return result;
}

#endif // MAP_H
