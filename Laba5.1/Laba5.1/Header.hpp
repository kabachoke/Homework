#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <span>
#include <algorithm>


template<class T>
char* as_bytes(T& i);
void convert_to_bin();
std::string convert_from_bin();