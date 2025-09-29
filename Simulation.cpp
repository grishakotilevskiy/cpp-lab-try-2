#include "Simulation.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <cmath>
#include <limits>

Simulation::Simulation(const std::string& input_filename)
    : m_filename(input_filename), m_N(0), m_max_deviation(0.0) {}

void Simulation::run() {
    if (!readData()) {
        return;
    }
    performCalculations();
    printResults();
}

bool Simulation::readData() {
    std::ifstream inputFile(m_filename);
    if (!inputFile.is_open()) {
        std::cout << "Error: Could not open " << m_filename << std::endl;
        return false;
    }

    inputFile >> m_N;
    if (inputFile.fail() || m_N <= 0) {
        std::cout << "Error: Invalid number of simulations N." << std::endl;
        return false;
    }

    inputFile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::string line_numbers;
    if (!std::getline(inputFile, line_numbers) || line_numbers.empty()) {
        std::cout << "Error: Could not read the line of numbers." << std::endl;
        return false;
    }
    std::stringstream ss_numbers(line_numbers);
    int number;
    while (ss_numbers >> number) {
        m_numbers.push_back(number);
    }

    std::string line_freqs;
    if (!std::getline(inputFile, line_freqs) || line_freqs.empty()) {
        std::cout << "Error: Could not read the line of frequencies." << std::endl;
        return false;
    }
    std::stringstream ss_freqs(line_freqs);
    int freq;
    while (ss_freqs >> freq) {
        m_frequencies.push_back(freq);
    }
    
    inputFile.close();

    if (m_numbers.size() != m_frequencies.size() || m_numbers.empty()) {
        std::cout << "Error: The number of numbers and frequencies do not match or are empty." << std::endl;
        return false;
    }

    return true;
}

void Simulation::performCalculations() {
    FrequencyRandomizer randomizer(m_numbers, m_frequencies);

    for (int i = 0; i < m_N; ++i) {
        int generated_number = randomizer();
        m_actual_counts[generated_number]++;
    }
}

void Simulation::printResults() {
    std::cout << "--- Simulation Results ---" << std::endl;
    std::cout << "Total simulations: " << m_N << std::endl << std::endl;

    double total_frequency_sum = 0;
    for (int f : m_frequencies) {
        total_frequency_sum += f;
    }

    if (total_frequency_sum == 0) {
        std::cout << "Error: Sum of frequencies is zero." << std::endl;
        return;
    }

    std::cout << std::fixed << std::setprecision(4);
    std::cout << "Number | Given Freq. | Actual Freq. | Deviation" << std::endl;
    std::cout << "---------------------------------------------------" << std::endl;

    for (size_t i = 0; i < m_numbers.size(); ++i) {
        double given_freq = m_frequencies[i] / total_frequency_sum;
        double actual_freq = static_cast<double>(m_actual_counts[m_numbers[i]]) / m_N;
        double deviation = std::abs(given_freq - actual_freq);

        if (deviation > m_max_deviation) {
            m_max_deviation = deviation;
        }

        std::cout << std::setw(6) << m_numbers[i] << " | "
            << std::setw(11) << given_freq << " | "
            << std::setw(12) << actual_freq << " | "
            << std::setw(9) << deviation << std::endl;
    }

    std::cout << "---------------------------------------------------" << std::endl;
    std::cout << "Max frequency deviation: " << m_max_deviation << std::endl;
}
