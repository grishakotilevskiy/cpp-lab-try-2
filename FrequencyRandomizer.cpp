#include "FrequencyRandomizer.h"

FrequencyRandomizer::FrequencyRandomizer(const std::vector<NumberData>& data) {
    if (data.empty()) {
        return;
    }

    for (const auto& item : data) {
        for (int j = 0; j < item.frequency; ++j) {
            weighted_sequence.push_back(item.number);
        }
    }

    std::random_device rd;
    generator.seed(rd());

    if (!weighted_sequence.empty()) {
        distribution = std::uniform_int_distribution<>(0, weighted_sequence.size() - 1);
    }
}

int FrequencyRandomizer::operator()() {
    if (weighted_sequence.empty()) {
        return 0;
    }
    return weighted_sequence[distribution(generator)];
}


