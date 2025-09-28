#include "FrequencyRandomizer.h"
#include <random>
#include <stdexcept>
#include <numeric>

FrequencyRandomizer::FrequencyRandomizer(const std::vector<int>& values,
    const std::vector<unsigned long long>& freqs)
    : values_(values)
{
    if (values_.empty() || freqs.empty() || values_.size() != freqs.size()) {
        throw std::runtime_error("FrequencyRandomizer");
    }

    // Перевірка частот і створення ваг для discrete_distribution
    std::vector<double> weights;
    weights.reserve(freqs.size());
    unsigned long long sum = 0;
    for (auto f : freqs) {
        if (f == 0) throw std::runtime_error("FrequencyRandomizer");
        weights.push_back(static_cast<double>(f));
        sum += f;
    }

    std::random_device rd;
    rng_.seed(rd());

    dist_ = std::discrete_distribution<std::size_t>(weights.begin(), weights.end());
}

int FrequencyRandomizer::operator()() {
    std::size_t idx = dist_(rng_);
    return values_.at(idx);
}
