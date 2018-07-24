/**
 This is free and unencumbered software released into the public domain.

 
 See the included UNLICENSE file, or http://unlicense.org/
 */

#include <iostream>
#include <string>

// Require C++ 11
#include <functional>

// Require C++ 17
#include <string_view>

/** 
 * @brief  Rabin-Karp Algorithm - string-searching algorithm using hashing
 * @note   This implementation will count number of pattern string in target string
 * @param  target: given string that may contain pattern string
 * @param  pattern: string need to be find in target string
 * @retval Number of subsring match pattern string in target string
 */

std::size_t RabinKarp(
    std::string target,
    std::string pattern)
{
    // string -> string_view : Read without copying
    std::string_view targetStr = target;

    // Define hash function
    std::hash<std::string_view> hash_fn;

    std::size_t count = 0,
                hashPattern = hash_fn(pattern),
                loop_size = target.length() - pattern.length() + 1;

    // Loop through string
    for (std::size_t iter = 0; iter < loop_size; ++iter)
        // Compare hash of 2 substrings
        if (hash_fn(target.substr(iter, pattern.length())) == hashPattern)
            // Compare 2 strings
            if (target.substr(iter, pattern.length()) == pattern)
                ++count;

    return count;
}

int main()
{
    std::string input, str;
    std::cin >> input >> str;
    std::cout << RabinKarp(input, str) << std::endl;
    return 0;
}
