/**
 This is free and unencumbered software released into the public domain.

 
 See the included UNLICENSE file, or http://unlicense.org/
 */

#include <iostream>
#include <string>

/** 
 * @brief  Rabin-Karp Algorithm - string-searching algorithm using hashing
 * @note   This implementation will count number of pattern string in target string
 * @param  target: given string that may contain pattern string
 * @param  pattern: string need to be find in target string
 * @retval Position of match pattern string in target string,
 *         if pattern can't be found in target, return -1
 */

int RabinKarp(const std::string &target, const std::string &pattern)
{
    /** 
     * cnst: Random cnst number
     * mod: Modulo
     */
    const unsigned cnst = 257, mod = 1e9 + 7;

    /* Normal hash */
    auto hash = [](const std::string &str) -> unsigned {
        long long sum = 0;
        for (auto &iter : str)
        {
            sum = sum * cnst + iter;
            sum %= mod;
        }
        return sum;
    };

    /* Binary exponentiation */
    auto bin_pow = [](long long a, long long b) -> long long {
        long long res = 1;
        while (b != 0)
        {
            if (b & 1)
            {
                res *= a;
                res %= mod;
            }
            a *= a;
            a %= mod;
            b >>= 1;
        }
        return res;
    };

    // Avoid overflow
    long long
        targetSize = target.size(),
        patternSize = pattern.size(),
        power = bin_pow(cnst, patternSize),
        patternHash = hash(pattern),
        rollingHash = 0;

    /* Rolling Hash */
    for (long long i = 0; i < targetSize; ++i)
    {
        /* Add last character */
        rollingHash = rollingHash * cnst + target[i];
        rollingHash %= mod;
        if (i >= patternSize)
        {
            /* Sub first character */
            rollingHash -= power * target[i - patternSize];
            // Case: Negative
            while (rollingHash < 0)
                rollingHash += mod;
        }

        /* Compare hash */
        if (i >= patternSize - 1 && patternHash == rollingHash)
            /* Return: Success */
            return (i - patternSize + 1);
    }

    /* Return: Not Found */
    return -1;
}

int main()
{
    std::string input, str;
    std::cin >> input >> str;
    std::cout << RabinKarp(input, str) << std::endl;
    return 0;
}
