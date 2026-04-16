#include "subsequence_ui.h"

#include <iostream>

#include "sequence_ui_utils.h"

void GetSubsequenceInUi(UiState& state)
{
    int index = 0;
    if (!SelectSequenceIndex(state, "Select sequence: ", index))
    {
        return;
    }

    int start_index = 0;
    int end_index = 0;
    if (!ReadInt("Write start index: ", start_index))
    {
        return;
    }

    if (!ReadInt("Write end index: ", end_index))
    {
        return;
    }

    try
    {
        Sequence<int>* result = state.sequences[index]->GetSubsequence(start_index, end_index);
        state.sequences.push_back(result);

        std::cout << "Created subsequence: ";
        PrintSequence(result);
        std::cout << "\n";
    }
    catch (const std::exception& error)
    {
        std::cout << "Operation failed: " << error.what() << "\n";
    }
}
