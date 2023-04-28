/*
** EPITECH PROJECT, 2023
** main.c
** File description:
** main file
*/

#include "stumper.h"
#include "macro.h"
#include "struct.h"

int initialiser_mots(int argc, char ** argv, struct GameInfo* game_info)
{
    if (argc != 2) {
        printf("Erreur: Nombre d'arguments invalide\n");
        return ERROR;
    }
    FILE* fichier = fopen(argv[1], "r");
    if (fichier == NULL) {
        printf("Erreur: Impossible d'ouvrir le fichier %s\n", argv[1]);
        return ERROR;
    }
    game_info->num_words = 0;
    while (fgets(game_info->words[game_info->num_words],
    MAX_WORD_LENGTH, fichier)) {
        game_info->words[game_info->num_words]
        [strlen(game_info->words[game_info->num_words]) - 1] = '\0';
        (game_info->num_words)++;
    }
    fclose(fichier);
    return SUCCESS;
}

void initialiser_lettres_trouvees(struct GameInfo* game_info)
{
    for (int i = 0; i < game_info->word_length; i++)
        game_info->found_letters[i] = 0;
}

void choisir_mot(struct GameInfo* game_info)
{
    int index;
    srand(time(NULL));
    index = rand() % game_info->num_words;
    game_info->word = game_info->words[index];
    game_info->word_length = strlen(game_info->word);
}

int main(int argc, char* argv[])
{
    struct GameInfo game_info;

    if (initialiser_mots(argc, argv, &game_info) == ERROR)
        return ERROR;
    choisir_mot(&game_info);
    initialiser_lettres_trouvees(&game_info);
    game_info.num_tries = MAX_TRIES;
    afficher_mot_cache(&game_info);
    while (game_info.num_tries > 0 && !verifier_victoire(&game_info))
        jouer_tour(&game_info);
    fin_de_jeu(&game_info);
    return SUCCESS;
}
