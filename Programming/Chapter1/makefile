CXX = g++
CXXFLAGS = -Wall -std=c++11

SRC_DIR = src
LIB_DIR = lib
OUTPUT_DIR = output

SRCS = $(wildcard $(SRC_DIR)/*.cpp)

HEADERS = $(wildcard $(LIB_DIR)/*.h)

OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(OUTPUT_DIR)/%.o, $(SRCS))

BINS = $(patsubst $(SRC_DIR)/%.cpp, $(OUTPUT_DIR)/%, $(SRCS))

all: $(BINS)

$(OUTPUT_DIR)/%: $(OUTPUT_DIR)/%.o
	$(CXX) $(CXXFLAGS) -o $@ $<

$(OUTPUT_DIR)/%.o: $(SRC_DIR)/%.cpp $(HEADERS) | $(OUTPUT_DIR)
	$(CXX) $(CXXFLAGS) -I$(LIB_DIR) -c $< -o $@

$(OUTPUT_DIR):
	mkdir -p $(OUTPUT_DIR)

report: $(OUTPUT_DIR)
	pdflatex -output-directory=$(OUTPUT_DIR) $(SRC_DIR)/report.tex

clean:
	rm -rf $(OUTPUT_DIR)

run: all
	for bin in $(BINS); do \
		./$$bin; \
	done

.PHONY: all clean report run