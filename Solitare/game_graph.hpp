#pragma once
#include <iostream>
#include <vector>
#include <unordered_set>
#include <queue>
#include "util.hpp"

struct Game {
    Game(const ut::Table& start_table);
    
    ut::Table columns;

    int FindMaxHead(int index);
};

class GameGraph {
private:
    size_t stacks_num = 8;
    size_t stack_size = 9;
    std::unordered_set<ut::Table> games;
    Game start;

public:
    explicit GameGraph(Game& curr, size_t stacks_num, size_t stack_size);

    bool AddEdge(Game& curr);
    void FindNewGames(std::queue<Game>& queue, Game& curr);
    void ChangeColumns(std::queue<Game>& queue, Game& curr, int index, int max_size);
    void CheckFull(ut::CardStack& curr, int index);

    bool FindResult();
};
