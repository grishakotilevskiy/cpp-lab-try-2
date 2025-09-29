#pragma once
#include <vector>
#include <random>

struct NumberData {
    int number;
    int frequency;
};

class FrequencyRandomizer {
public:
    FrequencyRandomizer(const std::vector<NumberData>& data);
    int operator()();

private:
    std::vector<int> weighted_sequence;
    std::mt19937 generator;
    std::uniform_int_distribution<> distribution;
};
