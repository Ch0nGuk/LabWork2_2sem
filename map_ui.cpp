#include "map_ui.h"

#include <iostream>

#include "sequence_ui_utils.h"

namespace
{
    int Identity(int value)
    {
        return value;
    }

    int DoubleValue(int value)
    {
        return value * 2;
    }

    int SquareValue(int value)
    {
        return value * value;
    }

    int NegateValue(int value)
    {
        return -value;
    }
}

void MapInUi(UiState& state)
{
    int index = 0;
    if (!SelectSequenceIndex(state, "Select sequence: ", index))
    {
        return;
    }

    std::cout << "Select map function:\n";
    std::cout << "1. Identity\n";
    std::cout << "2. Double\n";
    std::cout << "3. Square\n";
    std::cout << "4. Negate\n";

    int choice = 0;
    if (!ReadInt("Choice: ", choice))
    {
        return;
    }

    int (*map_func)(int) = nullptr;

    switch (choice)
    {
    case 1:
        map_func = Identity;
        break;
    case 2:
        map_func = DoubleValue;
        break;
    case 3:
        map_func = SquareValue;
        break;
    case 4:
        map_func = NegateValue;
        break;
    default:
        std::cout << "Unknown map function.\n";
        return;
    }

    Sequence<int>* result = state.sequences[index]->Map(map_func);
    state.sequences.push_back(result);

    std::cout << "Created mapped sequence: ";
    PrintSequence(result);
    std::cout << "\n";
}
