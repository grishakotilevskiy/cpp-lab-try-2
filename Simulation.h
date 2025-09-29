#pragma once
#include <string>
#include <vector>
#include <map>
#include "FrequencyRandomizer.h"

class Simulation {
public:
    Simulation(const std::string& input_filename);
    void run();

private:
    bool loadData();

    std::string filename;
    int n_trials;
    std::vector<NumberData> input_data;
    std::map<int, int> results;
    bool is_ready = false;
};
