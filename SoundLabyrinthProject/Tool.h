#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <fstream>

template <typename T> int Sign(T val) {
	return (T(0.0f) < val) - (val < T(0.0f));
}

std::vector<std::string> readTFile(std::string fileName);


