#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <filesystem>

bool compareFiles(const std::string& file1, const std::string& file2) {
    std::ifstream f1(file1);
    std::ifstream f2(file2);

    std::string line1, line2;
    while (std::getline(f1, line1) && std::getline(f2, line2)) {
        if (line1 != line2) {
            return false;
        }
    }

    return (f1.eof() && f2.eof());
}

bool compileCode(const std::string& codeFile) {
    int compilationResult = std::system(("g++ " + codeFile + " -o index").c_str());
    return (compilationResult == 0);
}

int calculateScore(int totalTests, int passedTests, int totalPoints) {
    return (static_cast<double>(passedTests) / totalTests) * totalPoints;
}

void deleteFile(const std::string& filePath) {
    std::filesystem::remove(filePath);
}

int main(int argc, char* argv[]) {
    // Check the number of command line arguments
    if (argc != 3) {
        std::cout << "Usage: " << argv[0] << " <code_file> <tests_directory>" << std::endl;
        return 1;
    }

    std::string codeFile = argv[1];
    std::string testsDirectory = argv[2];

    // Compile the C++ code
    if (!compileCode(codeFile)) {
        std::cout << "Compilation Error" << std::endl;

        // Log the compilation error
        std::ofstream errorLog("compilation_error.log");
        errorLog << "Compilation Error" << std::endl;
        errorLog.close();

        return 1;
    }

    // Iterate over test files in the directory
    std::filesystem::directory_iterator testsIterator(testsDirectory);
    std::filesystem::directory_iterator endIterator;

    int passedTests = 0;
    int totalTests = 0;

    for (; testsIterator != endIterator; ++testsIterator) {
        if (std::filesystem::is_directory(testsIterator->path())) {
            std::string testPath = testsIterator->path().string();
            std::string testName = testsIterator->path().filename().string();

            std::string inputPath = testPath + "/input.txt";
            std::string expectedOutputPath = testPath + "/expected.txt";

            // Run the compiled code and redirect output to a file
            std::system(("./index < " + inputPath + " > ./out.txt").c_str());

            // Compare the output with the expected output
            if (compareFiles("./out.txt", expectedOutputPath)) {
                std::cout << "Test " << testName << ": Passed" << std::endl;
                ++passedTests;
            } else {
                std::cout << "Test " << testName << ": Failed" << std::endl;
            }

            ++totalTests;

            // Delete the output file
            deleteFile("./out.txt");
        }
    }

    // Calculate the total score
    int totalPoints = totalTests;
    int score = calculateScore(totalTests, passedTests, totalPoints);
    std::cout << "Total Score: " << score << " out of " << totalPoints << std::endl;

    // Delete the binary file
    deleteFile("./index");

    return 0;
}
