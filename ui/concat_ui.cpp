#include "concat_ui.h"

#include <iostream>

#include "sequence_ui_utils.h"

void ConcatInUi(UiState& state)
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

    try
    {
        Sequence<int>* result = state.sequences[first_index]->Concat(*state.sequences[second_index]);
        state.sequences.push_back(result);

        std::cout << "Created concatenated sequence: ";
        PrintSequence(result);
        std::cout << "\n";
    }
    catch (const std::exception& error)
    {
        std::cout << "Operation failed: " << error.what() << "\n";
    }
}
