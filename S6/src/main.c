/*
** EPITECH PROJECT, 2023
** stumper6
** File description:
** stumper
*/

#include "stumper.h"

void choisirMotAleatoire(FILE *fichier, char *motSecret) {
    int nbMots = 0;
    char mot[MAX_WORD_LENGTH];
    while (fgets(mot, MAX_WORD_LENGTH, fichier) != NULL) {
        nbMots++;
    }
    rewind(fichier);
    int motAleatoire = rand() % nbMots;
    for (int i = 0; i <= motAleatoire; i++) {
        fgets(motSecret, MAX_WORD_LENGTH, fichier);
    }
    motSecret[strcspn(motSecret, "\n")] = '\0';
}

int estMotValide(char *mot) {
    for (int i = 0; mot[i] != '\0'; i++) {
        if ((mot[i] < 'a' || mot[i] > 'z') && (mot[i] < 'A' || mot[i] > 'Z')) {
            return 0;
        }
    }
    return 1;
}

void afficherLettresCorrectes(char *motSecret, char *motEssai) {
    for (int i = 0; motSecret[i] != '\0' && motEssai[i] != '\0'; i++) {
        if (motEssai[i] == motSecret[i]) {
            printf("%c", motEssai[i]);
        } else {
            printf("*");
        }
    }
    printf("\n\n");
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s fichier_mots\n", argv[0]);
        return 1;
    }

    FILE *fichier = fopen(argv[1], "r");
    if (fichier == NULL) {
        printf("Erreur: impossible d'ouvrir le fichier %s\n", argv[1]);
        return 1;
    }

    srand(time(0));

    char motSecret[MAX_WORD_LENGTH];
    choisirMotAleatoire(fichier, motSecret);

    fclose(fichier);

    printf("*: invalid letter\n");
    printf("?: incorrectly placed letter\n");
    printf("Will you find the word?\n");
    printf("%c", motSecret[0]);

    for (int i = 1; motSecret[i] != '\0'; i++)
        printf("%c", '*');
    printf("\n\n");

    // Boucle de jeu
    char motEssai[MAX_WORD_LENGTH];
    int numRound = 1; // Numéro du tour
    int numEssai = 0; // Nombre d'essais effectués

    while (1) {
        printf("Round %d\n", numRound);
        printf(">");
        fgets(motEssai, MAX_WORD_LENGTH, stdin);

        // Supprimer le caractère de fin de ligne du mot saisi
        motEssai[strcspn(motEssai, "\n")] = '\0';

        // Vérifier si le mot saisi est valide (seulement des lettres)
        if (!estMotValide(motEssai)) {
            printf("*: lettre invalide\n");
            continue;
        }

        // Vérifier si le mot saisi a la même longueur que le mot secret
        if (strlen(motEssai) - 1 < strlen(motSecret) - 1) {
            printf("Word too short. Retry.\n");
            numRound++;
            numEssai++;
            continue;
        }
        if (strlen(motEssai) - 1 > strlen(motSecret) - 1) {
            printf("Word too long. Retry.\n");
            numRound++;
            numEssai++;
            continue;
        }

        if (strcmp(motEssai, motSecret) == 0) {
            printf("\nYou won!\n");
            break;
        } else {
            afficherLettresCorrectes(motSecret, motEssai);
            numRound++;
            numEssai++;
        }

        if (numEssai == MAX_TRIES) {
            printf("\nYou lost!\n");
            break;
        }
    }

    return 0;
}
