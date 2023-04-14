/*
** EPITECH PROJECT, 2023
** game.c
** File description:
** game file
*/

#include <ctype.h>
#include "stumper.h"
#include "macro.h"
#include "struct.h"

void afficher_nombre_essais(struct GameInfo* game_info)
{
    printf("Tries: %d\n\n", game_info->num_tries);
}

void afficher_mot_cache(struct GameInfo* game_info)
{
    for (int i = 0; i < game_info->word_length; i++) {
        if (game_info->found_letters[i]) {
            printf("%c", game_info->word[i]);
        } else {
            printf("*");
        }
    }
    printf("\n");
    afficher_nombre_essais(game_info);
}

int verifier_victoire(struct GameInfo* game_info)
{
    for (int i = 0; i < game_info->word_length; i++) {
        if (!game_info->found_letters[i])
            return SUCCESS;
    }
    return ERROR;
}

void jouer_tour(struct GameInfo* game_info)
{
    char input;
    int found = 0;

    printf("\nYour letter: ");
    scanf(" %c", &input);
    for (int i = 0; i < game_info->word_length; i++) {
        if (game_info->word[i] == input) {
            game_info->found_letters[i] = 1;
            found = 1;
        }
    }
    if (!found)
        game_info->num_tries--;

    afficher_mot_cache(game_info);
}

void fin_de_jeu(struct GameInfo* game_info)
{
    if (verifier_victoire(game_info)) {
        printf("\nCongratulations!\n");
    } else {
        printf("\nYou lost!");
    }
}
