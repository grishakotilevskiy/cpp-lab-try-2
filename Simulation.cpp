#include "Simulation.h"
#include "StatisticsReporter.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <limits>

Simulation::Simulation(const std::string& input_filename)
    : filename(input_filename) {
    is_ready = loadData();
}

void Simulation::run() {
    if (!is_ready) {
        std::cout << "Simulation cannot run due to data loading errors." << std::endl;
        return;
    }

    FrequencyRandomizer randomizer(input_data);

    results.clear();
    for (int i = 0; i < n_trials; ++i) {
        results[randomizer()]++;
    }

    StatisticsReporter reporter(input_data, results, n_trials);
    reporter.printReport();
}

bool Simulation::loadData() {
    std::ifstream input_file(filename);
    if (!input_file.is_open()) {
        std::cout << "Error: Could not open file " << filename << std::endl;
        return false;
    }

    input_file >> n_trials;
    if (input_file.fail() || n_trials <= 0) {
        std::cout << "Error: Invalid N in input file." << std::endl;
        return false;
    }
    input_file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::string line;
    std::vector<int> numbers_vec, freqs_vec;

    std::getline(input_file, line);
    std::stringstream numbers_stream(line);
    int num;
    while (numbers_stream >> num) numbers_vec.push_back(num);

    std::getline(input_file, line);
    std::stringstream freqs_stream(line);
    int freq;
    while (freqs_stream >> freq) freqs_vec.push_back(freq);

    if (numbers_vec.empty() || numbers_vec.size() != freqs_vec.size()) {
        std::cout << "Error: Mismatch in numbers and frequencies or data is empty." << std::endl;
        return false;
    }

    input_data.clear();
    for (size_t i = 0; i < numbers_vec.size(); ++i) {
        input_data.push_back({ numbers_vec[i], freqs_vec[i] });
    }

    return true;
}

