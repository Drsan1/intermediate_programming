#include <cstdint>
#include <iostream>
#include <vector>

std::uint8_t getU8(const std::vector<std::uint8_t>& vec, std::size_t idx)
{
    return vec[idx];
}

std::uint16_t getU16(const std::vector<std::uint8_t>& vec, std::size_t idx)
{
    std::uint16_t tmp = getU8(vec, idx + 1);
    tmp <<= 8;
    tmp += getU8(vec, idx);
    return tmp;
}

std::uint32_t getU32(const std::vector<std::uint8_t>& vec, std::size_t idx)
{
    std::uint32_t tmp = getU16(vec, idx + 2);
    tmp <<= 16;
    tmp += getU16(vec, idx);
    return tmp;
}

std::uint64_t getU64(const std::vector<std::uint8_t>& vec, std::size_t idx)
{
    std::uint64_t tmp = getU32(vec, idx + 4);
    tmp <<= 32;
    tmp += getU32(vec, idx);
    return tmp;
}

// ukázka jak se to dá napsat, v praxi se spíš vyhněte:
/*
std::uint64_t getU64(const std::vector<std::uint8_t>& vec, std::size_t idx) {
    std::uint64_t buffer = 0;
    for (size_t i = idx + 8; i != idx; i--) {
        buffer <<= 8;
        buffer += vec[i - 1];
    }
    return buffer;
}
*/

void setU8(std::vector<std::uint8_t>& vec, std::size_t idx, std::uint8_t value)
{
    vec[idx] = value;
}

void setU16(std::vector<std::uint8_t>& vec, std::size_t idx, std::uint16_t value)
{
    setU8(vec, idx, value & 0xFF);
    setU8(vec, idx + 1, value >> 8);
}

void setU32(std::vector<std::uint8_t>& vec, std::size_t idx, std::uint32_t value)
{
    setU16(vec, idx, value & 0xFFFF);
    setU16(vec, idx + 2, value >> 16);
}

void setU64(std::vector<std::uint8_t>& vec, std::size_t idx, std::uint64_t value)
{
    setU32(vec, idx, value & 0xFFFFFFFF);
    setU32(vec, idx + 4, value >> 32);
}

std::vector<std::uint8_t> asU8(const std::vector<std::uint16_t>& vec)
{
    std::vector<std::uint8_t> result(vec.size() * 2);
    for (size_t i = 0; i < vec.size(); i++) {
        result[i * 2] = vec[i];
        result[i * 2 + 1] = (vec[i] >> 8);
    }
    return result;
}
std::vector<std::uint16_t> asU16(const std::vector<std::uint32_t>& vec) {
    std::vector<std::uint16_t> result(vec.size() * 2);
    for (size_t i = 0; i < vec.size(); i++) {
        result[i * 2] = vec[i];
        result[i * 2 + 1] = (vec[i] >> 16);
    }
}
std::vector<std::uint32_t> asU32(const std::vector<std::uint64_t>& vec) {
    std::vector<std::uint32_t> result(vec.size() * 2);
    for (size_t i = 0; i < vec.size(); i++) {
        result[i * 2] = vec[i];
        result[i * 2 + 1] = (vec[i] >> 32);
    }
}

void printVec(const std::vector<std::uint8_t>& vec)
{
    for (std::uint16_t elem : vec) {
        std::cout << static_cast<int>(elem) << ", ";
    }
    std::cout << std::endl;
}

int main()
{
    std::vector<std::uint8_t> memory { 0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF };
    std::vector<std::uint16_t> test { 0xFFEE, 0x0123 };

    std::cout << "Hello world!" << std::endl
              << std::hex;

    for (std::uint8_t elem : memory) {
        std::cout << static_cast<int>(elem) << ", ";
    }

    std::cout << std::endl
              << getU64(memory, 0) << std::endl;

    std::vector<std::uint8_t> lol = asU8(test);
    printVec(lol);
}
