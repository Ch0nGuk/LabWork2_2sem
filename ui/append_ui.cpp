#include "append_ui.h"

#include <iostream>

#include "../UniquePtr.h"
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
        UniquePtr<Sequence<int>> owned_result(result);
        state.sequences.push_back(owned_result.get());
        std::cout << "Created new sequence: ";
        PrintSequence(owned_result.get());
        std::cout << "\n";
        owned_result.release();
        return;
    }

    std::cout << "Updated sequence: ";
    PrintSequence(result);
    std::cout << "\n";
}
