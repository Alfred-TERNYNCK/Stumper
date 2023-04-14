#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>

#define MAX_POKEMON_NAME_LEN 100
#define MAX_LINE_LEN 1000

typedef struct {
    char name[MAX_POKEMON_NAME_LEN];
    int attack;
    int defense;
    int speed;
    int health;
} Pokemon;

void parsePokemonData(char* fileName, Pokemon* pokemon) {
    FILE* file = fopen(fileName, "r");
    if (file == NULL) {
        printf("Impossible d'ouvrir le fichier : %s\n", fileName);
        return;
    }

    char line[MAX_LINE_LEN];
    while (fgets(line, MAX_LINE_LEN, file) != NULL) {
        if (line[0] == '#') {
            continue; // Ignorer les commentaires
        }

        char* token;
        
        token = strtok(line, ";");
        strcpy(pokemon->name, token);
        token = strtok(NULL, ";");
        pokemon->attack = atoi(token);
        token = strtok(NULL, ";");
        pokemon->defense = atoi(token);
        token = strtok(NULL, ";");
        pokemon->speed = atoi(token);
        token = strtok(NULL, ";");
        pokemon->health = atoi(token);

        printf("Pokemon %s a %d points d'attaque, %d points de défense, %d points de vitesse et %d points de vie.\n",
               pokemon->name, pokemon->attack, pokemon->defense, pokemon->speed, pokemon->health);
    }

    fclose(file);
}

void simulateFight(Pokemon* pokemon1, Pokemon* pokemon2) {
    Pokemon* attacker;
    Pokemon* defender;

    if (pokemon1->speed > pokemon2->speed) {
        attacker = pokemon1;
        defender = pokemon2;
    } else if (pokemon2->speed > pokemon1->speed) {
        attacker = pokemon2;
        defender = pokemon1;
    } else {
        int random = rand() % 2;
        if (random == 0) {
            attacker = pokemon1;
            defender = pokemon2;
        } else {
            attacker = pokemon2;
            defender = pokemon1;
        }
    }

    printf("\nLe combat commence entre %s et %s !\n", pokemon1->name, pokemon2->name);
    printf("%s attaque en premier avec une vitesse de %d.\n", attacker->name, attacker->speed);

    while (pokemon1->health > 0 && pokemon2->health > 0) {
        int damage = rand() % (attacker->attack + 1); // Calculer les dégâts infligés par l'attaquant
        int remainingDamage = damage - defender->defense; // Calculer les dégâts restants après la défense

        // Vérifier que les dégâts ne sont pas négatifs
        if (remainingDamage < 0) {
            remainingDamage = 0;
        }

        // Mettre à jour les points de vie du défenseur
        defender->health -= remainingDamage;

        printf("%s attaque %s et lui inflige %d dégâts.\n", attacker->name, defender->name, remainingDamage);
        printf("%s a maintenant %d points de vie.\n", defender->name, defender->health);

        // Échanger les rôles d'attaquant et de défenseur pour le prochain tour
        Pokemon* temp = attacker;
        attacker = defender;
        defender = temp;

        // Pause pour mieux visualiser les étapes du combat
        sleep(1);
    }

    // Déterminer le gagnant
    if (pokemon1->health <= 0) {
        printf("%s est KO ! %s remporte le combat !\n", pokemon1->name, pokemon2->name);
    } else {
        printf("%s est KO ! %s remporte le combat !\n", pokemon2->name, pokemon1->name);
    }
}

int main(int ac, char **av) {
    DIR* dir = opendir("pokecfg"); // Ouvrir le dossier pokecfg
    if (dir == NULL) {
        printf("Impossible d'ouvrir le dossier pokecfg.\n");
        return 1;
    }

    char *Pokemon1name = av[1];
    char *Pokemon2name = av[2];

    Pokemon pokemon1;
    Pokemon pokemon2;
    struct dirent* ent;
    int num_pokemon = 0; // Compteur pour le nombre de pokémons

    while ((ent = readdir(dir)) != NULL) {
        if (ent->d_type == DT_REG) { // Vérifier que l'entrée est un fichier régulier
            char fileName[MAX_LINE_LEN];
            snprintf(fileName, MAX_LINE_LEN, "pokecfg/%s", ent->d_name);
            fileName[MAX_LINE_LEN - 1] = '\0'; // Ajouter le caractère de fin de chaîne pour éviter un dépassement de tampon

            // Appeler la fonction pour parser les données du Pokemon en fonction du compteur
            if (num_pokemon == 0) {
                parsePokemonData(fileName, &pokemon1);
                num_pokemon++;
            } else if (num_pokemon == 1) {
                parsePokemonData(fileName, &pokemon2);
                num_pokemon++;
            }
        }
    }

    closedir(dir);

    if (num_pokemon < 2) {
        printf("Il n'y a pas assez de pokémons pour combattre.\n");
        return 1;
    }

    // Appeler la fonction pour simuler le combat entre les deux pokémons
    //simulateFight(&pokemon1, &pokemon2);

    return 0;
}

