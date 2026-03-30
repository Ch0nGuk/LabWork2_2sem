#include "Sequence.h"
#include "DynamicArray.h"
#include "LinkedList.h"
#include "ArraySequence.h"
#include "ListSequence.h"
#include "MutableArraySequence.h"
#include "ImmutableArraySequence.h"
#include "MutableListSequence.h"
#include "ImmutableListSequence.h"

int main()
{
    int items[] = {1, 2, 3};

    DynamicArray<int> array(items, 3);
    LinkedList<int> list(items, 3);
    ArraySequence<int> arraySequence(items, 3);
    ListSequence<int> listSequence(items, 3);

    MutableArraySequence<int> mutableArray(items, 3);
    mutableArray.Append(4);
    mutableArray.Prepend(0);
    mutableArray.InsertAt(2, 99);
    MutableArraySequence<int> mutableArraySub = mutableArray.GetSubsequence(1, 3);
    MutableArraySequence<int> mutableArrayConcat = mutableArray.Concat(arraySequence);

    ImmutableArraySequence<int> immutableArray(items, 3);
    ImmutableArraySequence<int> immutableArrayAppend = immutableArray.Append(4);
    ImmutableArraySequence<int> immutableArrayPrepend = immutableArray.Prepend(0);
    ImmutableArraySequence<int> immutableArrayInsert = immutableArray.InsertAt(1, 99);
    ImmutableArraySequence<int> immutableArraySub = immutableArray.GetSubsequence(0, 2);
    ImmutableArraySequence<int> immutableArrayConcat = immutableArray.Concat(listSequence);

    MutableListSequence<int> mutableList(items, 3);
    mutableList.Append(4);
    mutableList.Prepend(0);
    mutableList.InsertAt(2, 99);
    MutableListSequence<int> mutableListSub = mutableList.GetSubsequence(1, 3);
    MutableListSequence<int> mutableListConcat = mutableList.Concat(arraySequence);

    ImmutableListSequence<int> immutableList(items, 3);
    ImmutableListSequence<int> immutableListAppend = immutableList.Append(4);
    ImmutableListSequence<int> immutableListPrepend = immutableList.Prepend(0);
    ImmutableListSequence<int> immutableListInsert = immutableList.InsertAt(1, 99);
    ImmutableListSequence<int> immutableListSub = immutableList.GetSubsequence(0, 2);
    ImmutableListSequence<int> immutableListConcat = immutableList.Concat(arraySequence);

    return array.GetSize() + list.GetSize() + arraySequence.GetLength() +
           listSequence.GetLength() + mutableArraySub.GetLength() + mutableArrayConcat.GetLength() +
           immutableArrayAppend.GetLength() + immutableArrayPrepend.GetLength() + immutableArrayInsert.GetLength() +
           immutableArraySub.GetLength() + immutableArrayConcat.GetLength() + mutableListSub.GetLength() +
           mutableListConcat.GetLength() + immutableListAppend.GetLength() + immutableListPrepend.GetLength() +
           immutableListInsert.GetLength() + immutableListSub.GetLength() + immutableListConcat.GetLength();
}
