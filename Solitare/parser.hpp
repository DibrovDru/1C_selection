#pragma once
#include "util.hpp"
#include <string_view>
#include <sstream>
#include <string>

namespace ps {
    int GetCardID(char card) {
        int card_id = -1;

        switch (card) {
            case 'A':
                card_id = 14;
                break;

            case 'K':
                card_id = 13;
                break;

            case 'Q':
                card_id = 12;
                break;

            case 'J':
                card_id = 11;
                break;

            case '10':
                card_id = 10;
                break;
            
            case '9':
                card_id = 9;
                break;
            
            case '8':
                card_id = 8;
                break;

            case '7':
                card_id = 7;
                break;

            case '6':
                card_id = 6;
                break;

            default:
                break;
            }

        return card_id;
    }

    ut::CardStack ParseInputStack(const std::string& input_stack_str, size_t stack_size) {
        char eater;
        char card;
        int card_id;
        std::stringstream input(input_stack_str);

        ut::CardStack input_stack(stack_size, -1);

        for (size_t i = 0; i < stack_size; ++i) {
            input >> card >> eater;
            input_stack[i] = GetCardID(card);
        }

        return input_stack;
    }
}