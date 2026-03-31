#ifndef UI_STATE_H
#define UI_STATE_H

#include <vector>

#include "Sequence.h"

struct UiState
{
    std::vector<Sequence<int>*> sequences;
};

#endif // UI_STATE_H
