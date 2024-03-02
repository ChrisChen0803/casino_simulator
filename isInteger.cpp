#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <string>

bool isInteger(const std::string& s) {
    try {
        std::stoi(s);
        return true;
    } catch (const std::invalid_argument&) {
        return false;
    } catch (const std::out_of_range&) {
        return false;
    }
}