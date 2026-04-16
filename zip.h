#ifndef ZIP_H
#define ZIP_H

#include <utility>

#include "IEnumerator.h"
#include "Sequence.h"
#include "sequence_factory.h"

template <typename T1, typename T2>
Sequence<std::pair<T1, T2>>* Zip(
    const Sequence<T1>& first,
    const Sequence<T2>& second,
    const SequenceFactory<std::pair<T1, T2>>& factory)
{
    Sequence<std::pair<T1, T2>>* result = factory.Create();
    IEnumerator<T1>* first_enumerator = first.GetEnumerator();
    IEnumerator<T2>* second_enumerator = second.GetEnumerator();

    try
    {
        while (first_enumerator->MoveNext() && second_enumerator->MoveNext())
        {
            Sequence<std::pair<T1, T2>>* next =
                result->Append(std::make_pair(first_enumerator->Current(), second_enumerator->Current()));

            if (next != result)
            {
                delete result;
                result = next;
            }
        }
    }
    catch (...)
    {
        delete first_enumerator;
        delete second_enumerator;
        delete result;
        throw;
    }

    delete first_enumerator;
    delete second_enumerator;
    return result;
}

#endif // ZIP_H
