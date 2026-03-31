CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -pedantic
TARGET := lab_app

SOURCES := \
	append_ui.cpp \
	concat_ui.cpp \
	create_sequence_ui.cpp \
	insert_at_ui.cpp \
	main.cpp \
	map_ui.cpp \
	prepend_ui.cpp \
	print_sequences_ui.cpp \
	reduce_ui.cpp \
	run_tests_ui.cpp \
	sequence_ui_utils.cpp \
	slice_ui.cpp \
	subsequence_ui.cpp \
	tests.cpp \
	ui.cpp \
	where_ui.cpp

OBJECTS := $(SOURCES:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $(TARGET)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)

.PHONY: all clean
