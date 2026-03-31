#include "insert_at_ui.h"

#include <iostream>

#include "sequence_ui_utils.h"

void InsertAtInUi(UiState& state)
{
    int index = 0;
    if (!SelectSequenceIndex(state, "Select sequence: ", index))
    {
        return;
    }

    int insert_index = 0;
    if (!ReadInt("Write insert index: ", insert_index))
    {
        return;
    }

    int item = 0;
    if (!ReadInt("Write item to insert: ", item))
    {
        return;
    }

    try
    {
        Sequence<int>* result = state.sequences[index]->InsertAt(insert_index, item);

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
    catch (const std::exception& error)
    {
        std::cout << "Operation failed: " << error.what() << "\n";
    }
}
