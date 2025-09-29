#include "StatisticsReporter.h"
#include <iostream>
#include <iomanip>
#include <numeric>
#include <cmath>

StatisticsReporter::StatisticsReporter(const std::vector<NumberData>& data, const std::map<int, int>& results, int n)
    : input_data(data), simulation_results(results), num_trials(n) {
}

void StatisticsReporter::printReport() const {
    std::cout << "--- Input Data ---" << std::endl;
    std::cout << "N = " << num_trials << std::endl;
    std::cout << "Numbers:     ";
    for (const auto& item : input_data) {
        std::cout << item.number << "\t";
    }
    std::cout << std::endl;
    std::cout << "Frequencies: ";
    for (const auto& item : input_data) {
        std::cout << item.frequency << "\t";
    }
    std::cout << "\n\n--- Results ---" << std::endl;

    double total_frequency_sum = 0;
    for (const auto& item : input_data) {
        total_frequency_sum += item.frequency;
    }

    double max_difference = 0.0;

    std::cout << std::fixed << std::setprecision(4);
    std::cout << "Number\tExpected Freq.\tActual Freq.\tDifference" << std::endl;
    std::cout << "--------------------------------------------------------" << std::endl;

    for (const auto& item : input_data) {
        double expected_freq = static_cast<double>(item.frequency) / total_frequency_sum;
        double actual_count = simulation_results.count(item.number) ? simulation_results.at(item.number) : 0;
        double actual_freq = actual_count / num_trials;
        double difference = std::abs(expected_freq - actual_freq);

        if (difference > max_difference) {
            max_difference = difference;
        }

        std::cout << item.number << "\t" << expected_freq << "\t\t" << actual_freq << "\t\t" << difference << std::endl;
    }

    std::cout << "\nMax frequency difference: " << max_difference << std::endl;

}
