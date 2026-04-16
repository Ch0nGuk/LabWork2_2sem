#include "unzip_ui.h"

#include <iostream>
#include <utility>

#include "../sequence_factory.h"
#include "sequence_ui_utils.h"
#include "../unzip.h"

void UnzipInUi(UiState& state)
{
    int index = 0;
    if (!SelectPairSequenceIndex(state, "Select pair sequence: ", index))
    {
        return;
    }

    ListSequenceFactory<int> factory;
    std::pair<Sequence<int>*, Sequence<int>*> result =
        Unzip<int, int>(*state.pair_sequences[index], factory, factory);

    state.sequences.push_back(result.first);
    state.sequences.push_back(result.second);

    std::cout << "Created first sequence: ";
    PrintSequence(result.first);
    std::cout << "\n";

    std::cout << "Created second sequence: ";
    PrintSequence(result.second);
    std::cout << "\n";
}
