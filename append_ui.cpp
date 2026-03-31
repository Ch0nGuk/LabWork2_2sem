#include "append_ui.h"

#include <iostream>

#include "sequence_ui_utils.h"

void AppendInUi(UiState& state)
{
    int index = 0;
    if (!SelectSequenceIndex(state, "Select sequence: ", index))
    {
        return;
    }

    int item = 0;
    if (!ReadInt("Write item to append: ", item))
    {
        return;
    }

    Sequence<int>* result = state.sequences[index]->Append(item);

    if (result != state.sequences[index])
    {
        state.sequences.push_back(result);
        std::cout << "Created new sequence: ";
        PrintSequence(result);
        std::cout << "\n";
        return;
    }

    std::cout << "Updated sequence: ";
    PrintSequence(result);
    std::cout << "\n";
}
