#include "zip_ui.h"

#include <iostream>
#include <utility>

#include "../sequence_factory.h"
#include "sequence_ui_utils.h"
#include "../zip.h"

void ZipInUi(UiState& state)
{
    int first_index = 0;
    int second_index = 0;

    if (!SelectSequenceIndex(state, "Select first sequence: ", first_index))
    {
        return;
    }

    if (!SelectSequenceIndex(state, "Select second sequence: ", second_index))
    {
        return;
    }

    ListSequenceFactory<std::pair<int, int>> factory;
    Sequence<std::pair<int, int>>* result = Zip<int, int>(
        *state.sequences[first_index],
        *state.sequences[second_index],
        factory
    );

    state.pair_sequences.push_back(result);
    std::cout << "Created zipped sequence: ";
    PrintSequence(result);
    std::cout << "\n";
}
