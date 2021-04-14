#include "game_graph.hpp"

Game::Game(const ut::Table& start_table) :columns(start_table) {
}

int Game::FindMaxHead(int index) {
    int res = 1;
    int curr = columns[index].back();

    for (int i = columns[index].size() - 2; i >= 0; --i) {
        if (curr < columns[index][i]) {
            ++res;
            curr = columns[index][i];
        } else {
            break;
        }
    }

    return res;
}

GameGraph::GameGraph(Game& curr, size_t stacks_num, size_t stack_size) : start(curr),
                                                                         stack_size(stack_size),
                                                                         stacks_num(stacks_num) {
    for (int i = 0; i < stacks_num; ++i) {
        for (int j = 0; j < stacks_num; ++j) {
            curr.columns[i][j] = 100;
        }
    }
    games.insert(curr.columns);
}

bool GameGraph::AddEdge(Game &curr) {
    return games.insert(curr.columns).second;
}

void GameGraph::CheckFull(ut::CardStack& curr, int index) {
    bool full = true;

    if (curr.size() == stack_size) {
        for (int i = 0; i < curr.size(); --i) {
            int curr_value = curr[curr.size() - 1 - i];
            if (curr_value == 100) {
                curr_value = start.columns[index][curr.size() - 1 - i];
            }

            if (curr_value != i + 6) {
                full = false;
                break;
            }
        }

        if (full) {
            curr.clear();
        }
    }
}

void GameGraph::ChangeColumns(std::queue<Game> &queue, Game &curr, int index, int max_size) {
    for (int i = 1; i <= max_size; ++i) {
        int curr_index = curr.columns[index].size() - i;
        int curr_last = curr.columns[index][curr_index];


        for (int j = 0; j < stacks_num; ++j) {
            if (curr_last < curr.columns[j].back()) {
                Game new_game = curr;
                for (int k = 0; k < i; ++k) {
                    new_game.columns[j].push_back(curr.columns[index][curr_index + k]);
                }

                CheckFull(curr.columns[j], index);

                for (int k = 0; k < i; ++k) {
                    new_game.columns[index].pop_back();
                }


                if (!curr.columns[index].empty() && curr.columns[index][curr_index] == 100) {
                    new_game.columns[index][curr_index] = start.columns[index][curr_index];
                }

                if (AddEdge(new_game)) {
                    queue.push(new_game);
                }
            }
        }
    }
}

void GameGraph::FindNewGames(std::queue<Game> &queue, Game& curr) {
    for (int i = 0; i < stacks_num; ++i) {
        int curr_max_length = curr.FindMaxHead(i);

        if (!curr.columns[i].empty()) {
            ChangeColumns(queue, curr, i, curr_max_length);
        }
    }
}

bool GameGraph::FindResult() {
    std::queue<Game> games_queue;
    games_queue.push(start);

    while (!games_queue.empty()) {
        Game curr = games_queue.front();
        games_queue.pop();
        bool res = true;

        for (int i = 0; i < stacks_num; ++i) {
            if (!curr.columns[i].empty()) {
                res = false;
                break;
            }
        }

        if (res) {
            return true;
        }

        FindNewGames(games_queue, curr);
    }

    return false;
}