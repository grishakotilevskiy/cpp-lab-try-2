#pragma once
#include <vector>
#include <map>
#include "FrequencyRandomizer.h"

class StatisticsReporter {
public:
    StatisticsReporter(const std::vector<NumberData>& data, const std::map<int, int>& results, int n);
    void printReport() const;

private:
    const std::vector<NumberData>& input_data;
    const std::map<int, int>& simulation_results;
    int num_trials;
};
