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
    bool readData();
    void performCalculations();
    void printResults();

    std::string m_filename;
    int m_N;
    std::vector<int> m_numbers;
    std::vector<int> m_frequencies;
    
    std::map<int, int> m_actual_counts;
    double m_max_deviation;
};
