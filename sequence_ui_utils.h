#ifndef SEQUENCE_UI_UTILS_H
#define SEQUENCE_UI_UTILS_H

#include <string>

#include "ui_state.h"

bool ReadInt(const std::string& prompt, int& value);
void PrintSequence(const Sequence<int>* sequence);
void PrintStoredSequences(const UiState& state);
bool SelectSequenceIndex(const UiState& state, const std::string& prompt, int& index);

#endif // SEQUENCE_UI_UTILS_H
