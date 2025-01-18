/*
 * Question 1
 * Optimize this code without the usage of external libraries.
 *  Parse this into a vector and print it to stdout
 * You may use the std libraries or STL, as well as any features through C++20
 */

#include <iostream>
#include <string>
#include <vector>
#include <string_view>
#include <array>

int main() {

    constexpr const std::string_view originalText = "Hello World!";
    
    // you can modify any part of the code below
    constexpr const size_t spaces = std::count_if(originalText.begin(), originalText.end(), [](unsigned char c) { return c == ' '; });
    
    auto l = [&]() consteval -> std::array<std::string_view, spaces + 1> {
        std::array<std::string_view, spaces + 1> words1;
        std::size_t wStart = 0;
        std::size_t pos = originalText.find(" ");

        std::size_t wordCnt = 0;
        while (pos != std::string::npos) {
            words1[wordCnt] = std::move(std::string_view{&originalText[wStart], pos - wStart});
            wStart = pos + 1;
            ++wordCnt;
            pos = originalText.find(" ", wStart);
        }
        words1[wordCnt] = std::move(std::string_view{ &originalText[wStart], originalText.size() - wStart });
        return words1;
    };

    constexpr const std::array<std::string_view, spaces + 1> words = l();

    for (size_t i = 0; i < words.size(); ++i) {
        std::cout << words[i] << '\n';
    }
    return 0;
}