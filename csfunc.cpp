#pragma once
#include "PlagueSimulatorLib.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <random>
// #include <format>

namespace Ethene
{
    std::string ReadAllText(const std::string &path)
    {
        std::ifstream file(path);
        if (file.is_open())
        {
            std::string line;
            std::getline(file,line);
            file.close();
            return line;
        }
        else if(!file)
        {
            std::cerr<<"NoFiles"<<std::endl;
            return "";
        }
        else
        {
            std::cerr << "Unable to open file" << std::endl;
            return "";
        }
    }

    std::vector<std::string> ReadAllLines(const std::string &path)
    {
        std::vector<std::string> lines;
        std::ifstream file(path);
        if (file.is_open())
        {
            std::string line;
            while (std::getline(file, line))
            {
                lines.push_back(line);
            }
            file.close();
        }
        else
        {
            std::cerr << "Unable to open file" << std::endl;
        }
        return lines;
    }

    std::vector<std::string> Split(const std::string &str, char delimiter)
    {
        std::vector<std::string> result;
        std::istringstream iss(str);
        std::string token;

        while (std::getline(iss, token, delimiter))
        {
            result.push_back(token);
        }

        return result;
    }

    bool IsInset(const std::set<std::string> &mySet, const std::string &str)
    {
        auto it = mySet.find(str);
        return (it != mySet.end());
    }

    int GetRandomNumber(const int &lowerLimit, const int &upperLimit)
    {
        static std::mt19937 generator(std::random_device{}());
        std::uniform_int_distribution<int> distribution(lowerLimit, upperLimit);
        return distribution(generator);
    }
}
