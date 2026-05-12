#include "unzip_ui.h"

#include <iostream>
#include <utility>

#include "../sequence_factory.h"
#include "../UniquePtr.h"
#include "sequence_ui_utils.h"

void UnzipInUi(UiState& state)
{
    int index = 0;
    if (!SelectPairSequenceIndex(state, "Select pair sequence: ", index))
    {
        return;
    }

    ListSequenceFactory<int> factory;
    std::pair<Sequence<int>*, Sequence<int>*> raw_result =
        state.pair_sequences[index]->Unzip<int, int>(factory, factory);
    UniquePtr<Sequence<int>> first_result(raw_result.first);
    UniquePtr<Sequence<int>> second_result(raw_result.second);

    state.sequences.push_back(first_result.get());
    state.sequences.push_back(second_result.get());

    std::cout << "Created first sequence: ";
    PrintSequence(first_result.get());
    std::cout << "\n";

    std::cout << "Created second sequence: ";
    PrintSequence(second_result.get());
    std::cout << "\n";

    first_result.release();
    second_result.release();
}
