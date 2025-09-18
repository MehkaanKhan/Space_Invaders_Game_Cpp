#include "Leaderboard.hpp"
#include <fstream>
#include <algorithm>

void Leaderboard::AddScore(int score) {
    std::ofstream outFile("scores.txt", std::ios::app);
    if (outFile.is_open()) {
        outFile << score << "\n";
        outFile.close();
    }
}

std::vector<int> Leaderboard::GetScores() {
    std::ifstream inFile("leaderboard.txt");
    std::vector<int> scores;
    int score;

    if (inFile.is_open()) {
        while (inFile >> score) {
            scores.push_back(score);
        }
        inFile.close();
    }

    std::sort(scores.rbegin(), scores.rend());  // Sort in descending order
    return scores;
}
