#pragma once
#include <vector>
#include <random>

class FrequencyRandomizer {
public:
    FrequencyRandomizer(const std::vector<int>& numbers, const std::vector<int>& frequencies);
    int operator()();

private:
    std::vector<int> m_numbers;
    std::vector<int> m_cumulative_frequencies;
    int m_total_frequency;
    std::mt19937 m_rng;
};
