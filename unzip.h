#ifndef UNZIP_H
#define UNZIP_H

#include <utility>

#include "IEnumerator.h"
#include "Sequence.h"
#include "sequence_factory.h"

template <typename T1, typename T2>
std::pair<Sequence<T1>*, Sequence<T2>*> Unzip(
    const Sequence<std::pair<T1, T2>>& source,
    const SequenceFactory<T1>& first_factory,
    const SequenceFactory<T2>& second_factory)
{
    Sequence<T1>* first_result = first_factory.Create();
    Sequence<T2>* second_result = second_factory.Create();
    IEnumerator<std::pair<T1, T2>>* enumerator = source.GetEnumerator();

    try
    {
        while (enumerator->MoveNext())
        {
            const std::pair<T1, T2>& value = enumerator->Current();

            Sequence<T1>* next_first = first_result->Append(value.first);
            if (next_first != first_result)
            {
                delete first_result;
                first_result = next_first;
            }

            Sequence<T2>* next_second = second_result->Append(value.second);
            if (next_second != second_result)
            {
                delete second_result;
                second_result = next_second;
            }
        }
    }
    catch (...)
    {
        delete enumerator;
        delete first_result;
        delete second_result;
        throw;
    }

    delete enumerator;
    return std::make_pair(first_result, second_result);
}

#endif // UNZIP_H
