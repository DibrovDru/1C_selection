#include "parser.hpp"
#include "util.hpp"
#include "game_graph.hpp"

int main() {
    std::string input_stack_str;
    size_t cards_num = 72;
    size_t stacks_num = 8;
    size_t stack_size = 9;
    std::cout << "Введите количество карт и количество стопок через пробел" << std::endl;
    std::cin >> cards_num >> stacks_num;
    stack_size = cards_num / stacks_num;

    ut::Table start_table;

    for (size_t i = 0; i < stacks_num; ++i) {
        std::cin >> input_stack_str;
        start_table.push_back(ps::ParseInputStack(input_stack_str, stack_size));
    }


    Game start_game(start_table);
    GameGraph graph(start_game, stacks_num, stack_size);

    std::cout << (graph.FindResult() ? "Yes" : "No");
}