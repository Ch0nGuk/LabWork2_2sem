#include "Sequence.h"
#include "DynamicArray.h"
#include "LinkedList.h"
#include "ArraySequence.h"
#include "ListSequence.h"
#include "MutableArraySequence.h"
#include "ImmutableArraySequence.h"
#include "map.h"
#include "sequence_factory.h"

int main()
{
    int items[] = {1, 2, 3};

    DynamicArray<int> array(items, 3);
    LinkedList<int> list(items, 3);

    Sequence<int>* mutable_seq = new MutableArraySequence<int>(items, 3);
    mutable_seq = mutable_seq->Append(4);
    mutable_seq = mutable_seq->Prepend(0);
    mutable_seq = mutable_seq->InsertAt(2, 99);
    Sequence<int>* mutable_sub = mutable_seq->GetSubsequence(1, 3);
    Sequence<int>* mutable_concat = mutable_seq->Concat(*mutable_sub);
    ListSequenceFactory<int> map_factory;
    Sequence<int>* mutable_map = Map<int, int>(*mutable_seq, [](int value) { return value * value; }, map_factory);

    Sequence<int>* immutable_seq = new ImmutableArraySequence<int>(items, 3);
    Sequence<int>* immutable_append = immutable_seq->Append(4);
    Sequence<int>* immutable_prepend = immutable_seq->Prepend(0);
    Sequence<int>* immutable_insert = immutable_seq->InsertAt(1, 99);
    Sequence<int>* immutable_sub = immutable_seq->GetSubsequence(0, 2);
    Sequence<int>* immutable_concat = immutable_seq->Concat(*mutable_seq);

    Sequence<int>* list_seq = new ListSequence<int>(items, 3);
    list_seq = list_seq->Append(4);
    list_seq = list_seq->Prepend(0);
    list_seq = list_seq->InsertAt(2, 99);
    Sequence<int>* list_sub = list_seq->GetSubsequence(1, 3);
    Sequence<int>* list_concat = list_seq->Concat(*immutable_seq);

    int result = array.GetSize() + list.GetSize() + mutable_seq->GetLength() + mutable_sub->GetLength() +
                 mutable_concat->GetLength() + mutable_map->GetLength() + immutable_seq->GetLength() +
                 immutable_append->GetLength() + immutable_prepend->GetLength() +
                 immutable_insert->GetLength() + immutable_sub->GetLength() + immutable_concat->GetLength() +
                 list_seq->GetLength() + list_sub->GetLength() + list_concat->GetLength();

    delete mutable_seq;
    delete mutable_sub;
    delete mutable_concat;
    delete mutable_map;
    delete immutable_seq;
    delete immutable_append;
    delete immutable_prepend;
    delete immutable_insert;
    delete immutable_sub;
    delete immutable_concat;
    delete list_seq;
    delete list_sub;
    delete list_concat;

    return result;
}
