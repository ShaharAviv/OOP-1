#pragma once

#include <memory>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <array>

template <typename T, int numRows, int numColumns> 
using Array2D = std::array<std::array<T,numColumns>,numRows>; 


