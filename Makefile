CXX = g++
CXXFLAGS = -Wall -O2 -std=c++17

SRC_DIR = src
BUILD_DIR = build
GEN_DIR = generators

all: | $(BUILD_DIR) $(GEN_DIR) $(BUILD_DIR)/clique $(BUILD_DIR)/max_set $(BUILD_DIR)/sat $(BUILD_DIR)/cli $(GEN_DIR)/sat_gen $(GEN_DIR)/graph_gen

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(GEN_DIR):
	mkdir -p $(GEN_DIR)

$(BUILD_DIR)/clique: $(SRC_DIR)/clique.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

$(BUILD_DIR)/max_set: $(SRC_DIR)/max_set.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

$(BUILD_DIR)/sat: $(SRC_DIR)/sat.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

$(BUILD_DIR)/cli: $(SRC_DIR)/main.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

$(GEN_DIR)/sat_gen: generators/sat_gen.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

$(GEN_DIR)/graph_gen: generators/graph_gen.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

run: $(BUILD_DIR)/cli
	./build/cli

clean:
	rm -rf $(BUILD_DIR)/* $(GEN_DIR)/sat_gen $(GEN_DIR)/clique_gen
