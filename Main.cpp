#include <iostream>
#include <vector>
#include <string>
#include <optional>
#include <iterator>

namespace Kmp
{
    std::vector<int> CreatePrefixes(const std::string_view &s)
    {
        std::vector<int> result(size(s));
        for (int i = 1, k = 0; i < size(s); ++i)
        {
            while (k > 0 && s[k] != s[i])
            {
                k = result[k - 1];
            }
            if (s[k] == s[i])
            {
                ++k;
            }
            result[i] = k;
        }
        return result;
    }

    std::optional<size_t> Find(const std::string_view &s, const std::string_view &pattern)
    {
        if (empty(pattern))
        {
            return {};
        }
        const auto prefixes = CreatePrefixes(pattern);
        for (int i = 0, k = 0; i < size(s); ++i)
        {
            for (;; k = prefixes[k - 1])
            {
                if (pattern[k] == s[i])
                {
                    if (++k == size(pattern))
                    {
                        return i + 1 - size(pattern);
                    }
                    break;
                }
                if (k == 0)
                {
                    break;
                }
            }
        }
        return {};
    }

    std::vector<size_t> FindAll(std::string str, const std::string_view &sub)
    {
        std::vector<size_t> res;
        size_t plus = 0;
        for (std::optional<size_t> i; i = Find(str, sub);)
        {
            res.push_back(*i + plus);
            str.erase(begin(str), begin(str) + *i + 1);
            plus += (*i + 1);
        }
        return res;
    }
}
template<typename T> std::ostream &operator<<(std::ostream &cout, const std::vector<T> &vec)
{
    cout << "{ ";
    std::copy(cbegin(vec), cend(vec), std::ostream_iterator<T>(cout, " "));
    return cout << "}";
}

int main()
{
    for (std::string text, pattern;;)
    {
        std::cout << "Text: ";
        std::getline(std::cin, text);
        std::cout << "Pattern: ";
        std::getline(std::cin, pattern);
        std::cout << "Indexes: " << Kmp::FindAll(std::move(text), pattern) << std::endl;
    }
}