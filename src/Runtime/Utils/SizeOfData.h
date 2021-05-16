#pragma once

#include <array>
#include <cstdint>
#include <string>
#include <vector>

namespace Runtime {

template <typename T>
inline size_t sizeof_data(const T& val) { return sizeof(val); }

template <>
inline size_t sizeof_data<std::string>(const std::string& val) { return val.size(); }

template <typename T, std::size_t N>
inline size_t sizeof_data(const std::array<T, N>& val) { return val.size() * sizeof(T); }

template <typename T>
inline size_t sizeof_data(const std::vector<T>& val) { return val.size() * sizeof(T); }

};

using Runtime::sizeof_data;