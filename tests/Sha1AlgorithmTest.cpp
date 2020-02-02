#include <Sha1Algorithm.hpp>

#include <iostream>

#define ESCAPE_SEQUENCE "\x1b"
#define RESET_TEXT ESCAPE_SEQUENCE"[0m"
#define RED_TEXT ESCAPE_SEQUENCE"[31m"
#define YELLOW_TEXT ESCAPE_SEQUENCE"[33m"
#define GREEN_TEXT ESCAPE_SEQUENCE"[92m"

struct BaseEncodeCase {
    std::string parameter;
    std::string result;
};

bool TestSha1(const char * testName, std::vector<BaseEncodeCase> testCases, std::string(*fncToTest)(const std::string&)) {
    std::cout << YELLOW_TEXT "\nBEGAN " RESET_TEXT << testName << std::endl;

    for (auto testCase : testCases) {
        std::string sha1 = fncToTest(testCase.parameter);

        if (sha1.compare(testCase.result)) {
            std::cout << RED_TEXT "[FAILED!]" << RESET_TEXT " Test Case ( " << testCase.parameter << " )\n";
            std::cout << "Got: " << sha1 << "\nExp: " << testCase.result << std::endl;
            std::cout << "Testing terminated!\n\n";
            return false;
        } else {
            std::cout << GREEN_TEXT "[PASSED!]" << RESET_TEXT " Test Case ( " << testCase.parameter << " ) Passed!\n";
        }
    }

    return true;
}

int main(int argc, char ** argv) {

    std::vector<BaseEncodeCase> testCasesSha1 =  {
        {"A Test", "8f0c0855915633e4a7de19468b3874c8901df043"},
        {"The quick brown fox jumps over the lazy dog", "2fd4e1c67a2d28fced849ee1bb76e7391b93eb12"},
        {"The quick brown fox jumps over the lazy cog", "de9f2c7fd25e1b3afad3e85a0bd17d9b100db4b3"},
        {std::string(512, 'A'), "10106f85d6ff9e833817fea16ae015fd9f81795c"},
        {"", "da39a3ee5e6b4b0d3255bfef95601890afd80709"},
    };

    if (TestSha1("Sha1Hash", testCasesSha1, Sha1Algorithm::Sha1Hash) != true) return -1;

    std::cout << GREEN_TEXT "\nAll tests finished with success\n\n" RESET_TEXT;

}