#include "FrequencyRandomizer.h"
#include <numeric>

FrequencyRandomizer::FrequencyRandomizer(const std::vector<int>& numbers, const std::vector<int>& frequencies)
    : m_numbers(numbers) {
    
    std::random_device rd;
    m_rng.seed(rd());

    m_total_frequency = 0;
    for (int freq : frequencies) {
        m_total_frequency += freq;
    }

    int current_sum = 0;
    for (int freq : frequencies) {
        current_sum += freq;
        m_cumulative_frequencies.push_back(current_sum);
    }
}

int FrequencyRandomizer::operator()() {
    if (m_total_frequency == 0) {
        return 0;
    }

    std::uniform_int_distribution<int> dist(1, m_total_frequency);
    int random_value = dist(m_rng);

    for (size_t i = 0; i < m_cumulative_frequencies.size(); ++i) {
        if (random_value <= m_cumulative_frequencies[i]) {
            return m_numbers[i];
        }
    }
    
    return 0;
}
