//
// Created by sitao on 4/19/2021.
//

#ifndef CODECHALLENGE_LONGESTSTRAND_LONGEST_STRAND_H
#define CODECHALLENGE_LONGESTSTRAND_LONGEST_STRAND_H

#include <iostream>
#include <filesystem>
#include <vector>
#include <fstream>
#include <thread>
#include <algorithm>
#include <chrono>

namespace fs = std::filesystem;
std::vector<char> get_file_content(const std::string&);
std::vector<std::pair<std::string, std::string>> generate_file_pairs(std::vector<std::string>);
std::tuple<int, int, int> longest_sub_strand(std::vector<char>, std::vector<char>);
bool comp(const std::tuple<std::string, std::string, int, int, int>&,
          const std::tuple<std::string, std::string, int, int, int>&);
void display_result(std::vector<std::tuple<std::string, std::string, int, int, int>>);

#endif //CODECHALLENGE_LONGESTSTRAND_LONGEST_STRAND_H
