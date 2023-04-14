/*
** EPITECH PROJECT, 2023
** struct.h
** File description:
** structure gameinfo
*/

#include "macro.h"

#ifndef STRUCT_H_
    #define STRUCT_H_

    struct GameInfo {
        char words[1000][MAX_WORD_LENGTH];
        int num_words;
        char* word;
        int word_length;
        int num_tries;
        int found_letters[MAX_WORD_LENGTH];
    };

#endif
