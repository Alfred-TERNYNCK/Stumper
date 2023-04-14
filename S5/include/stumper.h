/*
** EPITECH PROJECT, 2023
** my.h
** File description:
** .h
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "struct.h"

#ifndef STUMPER_H_
    #define STUMPER_H_

    void afficher_nombre_essais(struct GameInfo* game_info);
    void afficher_mot_cache(struct GameInfo* game_info);
    int verifier_victoire(struct GameInfo* game_info);
    void jouer_tour(struct GameInfo* game_info);
    void fin_de_jeu(struct GameInfo* game_info);
    void choisir_mot(struct GameInfo* game_info);
    void initialiser_lettres_trouvees(struct GameInfo* game_info);
    int initialiser_mots(int argc, char ** argv, struct GameInfo* game_info);
    void choisir_mot(struct GameInfo* game_info);

#endif
