#include "sequence_ui_utils.h"

#include <iostream>
#include <limits>

bool ReadInt(const std::string& prompt, int& value)
{
    std::cout << prompt;
    std::cin >> value;

    if (!std::cin)
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input.\n";
        return false;
    }

    return true;
}

void PrintSequence(const Sequence<int>* sequence)
{
    std::cout << "[";

    for (int index = 0; index < sequence->GetLength(); index++)
    {
        if (index > 0)
        {
            std::cout << ", ";
        }

        std::cout << sequence->Get(index);
    }

    std::cout << "]";
}

void PrintStoredSequences(const UiState& state)
{
    if (state.sequences.empty())
    {
        std::cout << "No sequences created.\n";
        return;
    }

    std::cout << "Stored sequences:\n";

    for (std::size_t index = 0; index < state.sequences.size(); index++)
    {
        std::cout << index + 1 << ". ";
        PrintSequence(state.sequences[index]);
        std::cout << " (length = " << state.sequences[index]->GetLength() << ")\n";
    }
}

bool SelectSequenceIndex(const UiState& state, const std::string& prompt, int& index)
{
    if (state.sequences.empty())
    {
        std::cout << "No sequences available.\n";
        return false;
    }

    PrintStoredSequences(state);

    int choice = 0;
    if (!ReadInt(prompt, choice))
    {
        return false;
    }

    if (choice <= 0 || choice > static_cast<int>(state.sequences.size()))
    {
        std::cout << "Wrong number.\n";
        return false;
    }

    index = choice - 1;
    return true;
}
