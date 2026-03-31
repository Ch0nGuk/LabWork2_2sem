#include "slice_ui.h"

#include <iostream>

#include "sequence_ui_utils.h"

void SliceInUi(UiState& state)
{
    int source_index = 0;
    int replacement_index = 0;

    if (!SelectSequenceIndex(state, "Select source sequence: ", source_index))
    {
        return;
    }

    if (!SelectSequenceIndex(state, "Select replacement sequence: ", replacement_index))
    {
        return;
    }

    int start_index = 0;
    int count = 0;
    if (!ReadInt("Write slice start index: ", start_index))
    {
        return;
    }

    if (!ReadInt("Write slice count: ", count))
    {
        return;
    }

    try
    {
        Sequence<int>* result = state.sequences[source_index]->Slice(
            start_index,
            count,
            *state.sequences[replacement_index]
        );
        state.sequences.push_back(result);

        std::cout << "Created sliced sequence: ";
        PrintSequence(result);
        std::cout << "\n";
    }
    catch (const std::exception& error)
    {
        std::cout << "Operation failed: " << error.what() << "\n";
    }
}
