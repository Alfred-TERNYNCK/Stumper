#include <stdio.h>
#include <string.h>

// Fonction pour compter le nombre d'occurrences d'un caractère dans une chaîne
int countOccurrences(char str[], char ch) {
    int count = 0;
    for (int i = 0; i < strlen(str); i++) {
        if (str[i] == ch) {
            count++;
        }
    }
    return count;
}

// Fonction pour trier les caractères par nombre d'occurrences (ordre décroissant)
void sortCharactersByOccurrences(char str[], int occurrences[], int len) {
    for (int i = 0; i < len - 1; i++) {
        for (int j = i + 1; j < len; j++) {
            if (occurrences[j] > occurrences[i]) {
                int temp_occurrences = occurrences[i];
                char temp_char = str[i];
                occurrences[i] = occurrences[j];
                str[i] = str[j];
                occurrences[j] = temp_occurrences;
                str[j] = temp_char;
            }
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2 || argc > 4) {
        printf("Usage: %s [-r] [-t] STR [SEARCHED_CHARACTERS]\n", argv[0]);
        return 1;
    }

    // Récupérer les options de ligne de commande
    int groupByOccurrences = 0;
    int sortByOccurrences = 0;
    char *str = argv[1];
    char *searchedCharacters = NULL;
    if (argc >= 3) {
        for (int i = 2; i < argc; i++) {
            if (strcmp(argv[i], "-r") == 0) {
                groupByOccurrences = 1;
            } else if (strcmp(argv[i], "-t") == 0) {
                sortByOccurrences = 1;
            } else {
                searchedCharacters = argv[i];
            }
        }
    }

    // Compter les occurrences des caractères dans la chaîne
    int len = strlen(str);
    int occurrences[len];
    for (int i = 0; i < len; i++) {
        if (searchedCharacters != NULL && strchr(searchedCharacters, str[i]) == NULL) {
            occurrences[i] = 0;
        } else {
            occurrences[i] = countOccurrences(str, str[i]);
        }
    }

    // Trier les caractères par nombre d'occurrences si l'option -t est spécifiée
    if (sortByOccurrences) {
        sortCharactersByOccurrences(str, occurrences, len);
    }

    // Afficher les caractères et leurs occurrences
    if (groupByOccurrences) {
        int maxOccurrences = occurrences[0];
        for (int i = 0; i < len; i++) {
            if (occurrences[i] == maxOccurrences) {
                printf("%c:%d\n", str[i], occurrences[i]);
            } else {
                break;
            }
        }
    } else {
        for (int i = 0; i < len; i++) {
            printf("%c:%d\n", str[i], occurrences[i]);
        }
    }

    return 0;
}
