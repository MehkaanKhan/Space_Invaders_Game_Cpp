#ifndef LEADERBOARD_HPP
#define LEADERBOARD_HPP

#include <vector>
#include <string>

class Leaderboard {
public:
    void AddScore(int score);
    std::vector<int> GetScores();
private:
    const std::string fileName = "scores.txt";
};

#endif
