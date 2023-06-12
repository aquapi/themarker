#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <filesystem>

// Some constants
const std::string binaryFile = "./index",
    outputFile = "./output.txt";

// Compare two output of files
inline bool compareFiles(const std::string& file1, const std::string& file2) {
    std::ifstream f1(file1);
    std::ifstream f2(file2);

    std::string line1, line2;
    while (std::getline(f1, line1) && std::getline(f2, line2)) 
        if (line1 != line2) 
            return false;

    return (f1.eof() && f2.eof());
}

// Compile the target file
inline bool compileCode(const std::string& codeFile) {
    int compilationResult = std::system(("g++ " + codeFile + " -o " + binaryFile).c_str());
    return (compilationResult == 0);
}

// Remove a file from filesystem
inline void deleteFile(const std::string& filePath) {
    std::filesystem::remove(filePath);
}

// Get total score from a test
inline int getTestScore(const std::string& testPath) {
    std::ifstream propertiesFile(testPath + "/properties.txt");
    int totalScore = 0;

    if (propertiesFile.is_open()) {
        std::string line;
        if (std::getline(propertiesFile, line)) 
            totalScore = std::stoi(line);
    }

    return totalScore;
}

// Print usage for the CLI
inline int printUsage(char* argv[]) {
    std::cout << "Usage: " << argv[0] << " <code_file> <tests_directory>" << std::endl;
    return 1;
};

int main(int argc, char* argv[]) {
    // Check the number of command line arguments
    if (argc != 3) 
        return printUsage(argv);

    std::string codeFile = argv[1];
    std::string testsDirectory = argv[2];

    // Compile the C++ code
    if (!compileCode(codeFile)) {
        std::cout << "Compilation Error" << std::endl;
        return 1;
    }

    // Iterate over test directories in the directory
    std::filesystem::directory_iterator testsIterator(testsDirectory);
    std::filesystem::directory_iterator endIterator;

    int currentPoints = 0;
    int totalTests = 0;
    int totalPoints = 0;

    for (; testsIterator != endIterator; ++testsIterator) {
        if (std::filesystem::is_directory(testsIterator->path())) {
            std::string testPath = testsIterator->path().string();
            std::string testName = testsIterator->path().filename().string();

            std::string inputPath = testPath + "/input.txt";
            std::string expectedOutputPath = testPath + "/expected.txt";

            // Extract the total score of the test from the properties file
            int testTotalScore = getTestScore(testPath);
            totalPoints += testTotalScore;

            // Run the compiled code and redirect output to a file
            int result = std::system((binaryFile + " < " + inputPath + " > " + outputFile).c_str());

            // Compare the output with the expected output
            if (result == 0 && compareFiles(outputFile.c_str(), expectedOutputPath)) {
                std::cout << "Test " << testName << ": Passed" << std::endl;
                currentPoints += testTotalScore;
            } else 
                std::cout << "Test " << testName << ": Failed" << std::endl;

            ++totalTests;

            // Delete the output file
            deleteFile(outputFile);
        }
    }

    // Calculate the total score
    std::cout << "Total Score: " << currentPoints << " out of " << totalPoints << std::endl;

    // Delete the binary file
    deleteFile(binaryFile);

    return 0;
}
