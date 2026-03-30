#include "Sequence.h"
#include "DynamicArray.h"
#include "LinkedList.h"
#include "ArraySequence.h"
#include "ListSequence.h"
#include "MutableArraySequence.h"
#include "ImmutableArraySequence.h"

int main()
{
    int items[] = {1, 2, 3};

    DynamicArray<int> array(items, 3);
    LinkedList<int> list(items, 3);

    Sequence<int>* mutableSeq = new MutableArraySequence<int>(items, 3);
    mutableSeq = mutableSeq->Append(4);
    mutableSeq = mutableSeq->Prepend(0);
    mutableSeq = mutableSeq->InsertAt(2, 99);
    Sequence<int>* mutableSub = mutableSeq->GetSubsequence(1, 3);
    Sequence<int>* mutableConcat = mutableSeq->Concat(*mutableSub);

    Sequence<int>* immutableSeq = new ImmutableArraySequence<int>(items, 3);
    Sequence<int>* immutableAppend = immutableSeq->Append(4);
    Sequence<int>* immutablePrepend = immutableSeq->Prepend(0);
    Sequence<int>* immutableInsert = immutableSeq->InsertAt(1, 99);
    Sequence<int>* immutableSub = immutableSeq->GetSubsequence(0, 2);
    Sequence<int>* immutableConcat = immutableSeq->Concat(*mutableSeq);

    Sequence<int>* listSeq = new ListSequence<int>(items, 3);
    listSeq = listSeq->Append(4);
    listSeq = listSeq->Prepend(0);
    listSeq = listSeq->InsertAt(2, 99);
    Sequence<int>* listSub = listSeq->GetSubsequence(1, 3);
    Sequence<int>* listConcat = listSeq->Concat(*immutableSeq);

    int result = array.GetSize() + list.GetSize() + mutableSeq->GetLength() + mutableSub->GetLength() +
                 mutableConcat->GetLength() + immutableSeq->GetLength() +
                 immutableAppend->GetLength() + immutablePrepend->GetLength() +
                 immutableInsert->GetLength() + immutableSub->GetLength() + immutableConcat->GetLength() +
                 listSeq->GetLength() + listSub->GetLength() + listConcat->GetLength();

    delete mutableSeq;
    delete mutableSub;
    delete mutableConcat;
    delete immutableSeq;
    delete immutableAppend;
    delete immutablePrepend;
    delete immutableInsert;
    delete immutableSub;
    delete immutableConcat;
    delete listSeq;
    delete listSub;
    delete listConcat;

    return result;
}
