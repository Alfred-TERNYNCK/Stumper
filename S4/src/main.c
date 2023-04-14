#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <time.h>

// Définition de la structure Pokemon
typedef struct {
    char name[20];
    int attack;
    int defense;
    int speed;
    int health;
} Pokemon;

// Prototypes de fonction
void combat(Pokemon* pokemon1, Pokemon* pokemon2);

void lireFichierPokemon(const char* nomFichier, Pokemon* pokemons, int* numPokemons) {
    FILE* fichier = fopen(nomFichier, "r");
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier %s\n", nomFichier);
        return;
    }

    char ligne[256];
    fgets(ligne, sizeof(ligne), fichier); // Lire la première ligne pour ignorer l'en-tête

    while (fgets(ligne, sizeof(ligne), fichier)) {
        char* token = strtok(ligne, ";"); // Séparer la ligne en tokens avec le délimiteur ";"

        // Copier les informations dans la structure Pokemon
        strncpy(pokemons[*numPokemons].name, token, sizeof(pokemons[*numPokemons].name) - 1);
        pokemons[*numPokemons].name[sizeof(pokemons[*numPokemons].name) - 1] = '\0';
        
        token = strtok(NULL, ";");
        pokemons[*numPokemons].attack = atoi(token);

        token = strtok(NULL, ";");
        pokemons[*numPokemons].defense = atoi(token);

        token = strtok(NULL, ";");
        pokemons[*numPokemons].speed = atoi(token);

        token = strtok(NULL, ";");
        pokemons[*numPokemons].health = atoi(token);

        (*numPokemons)++; // Incrémenter le nombre de Pokémons lus
    }

    fclose(fichier);
}

int main() {
    // Initialisation du générateur de nombres aléatoires
    srand(time(0));

    // Création des Pokémons
    Pokemon poke_one;
    Pokemon poke_two;

    // Appel de la fonction de combat
    combat(&poke_one, &poke_two);

    return 0;
}

// Combat entre les deux Pokémons
void combat(Pokemon* pokemon1, Pokemon* pokemon2) {
    printf("%s a %d points d'attaque, %d points de défense, %d points de vitesse et %d points de santé.\n", pokemon1->name, pokemon1->attack, pokemon1->defense, pokemon1->speed, pokemon1->health);
    printf("%s a %d points d'attaque, %d points de défense, %d points de vitesse et %d points de santé.\n", pokemon2->name, pokemon2->attack, pokemon2->defense, pokemon2->speed, pokemon2->health);

    while (pokemon1->health > 0 && pokemon2->health > 0) {
        // Déterminer le Pokémon qui commence le tour en fonction de leur vitesse
        Pokemon* attaquant;
        Pokemon* defenseur;
        if (pokemon1->speed > pokemon2->speed) {
            attaquant = pokemon1;
            defenseur = pokemon2;
        } else {
            attaquant = pokemon2;
            defenseur = pokemon1;
        }

        // Calculer les dégâts infligés par l'attaquant
        int degats = rand() % (attaquant->attack + 1);

        // Réduire les dégâts en fonction de la défense du défenseur
        degats -= defenseur->defense;

        // Vérifier si les dégâts sont positifs (ne peuvent pas être négatifs)
        if (degats < 0) {
            degats = 0;
        }

        // Mettre à jour la santé du défenseur
        defenseur->health -= degats;

        // Afficher les résultats du tour
        printf("%s attaque pour %d dégâts.\n", attaquant->name, degats);
        printf("%s bloque %d dégâts.\n", defenseur->name, defenseur->defense);
        printf("%s perd %d points de santé (%d restants).\n", defenseur->name, degats, defenseur->health);

        // Vérifier si le défenseur est KO
        if (defenseur->health <= 0) {
            printf("%s est KO.\n", defenseur->name);
            printf("%s remporte le combat!\n", attaquant->name);
            return;
        }
        // Échanger les rôles d'attaquant et de défenseur pour le prochain tour
        Pokemon* temp = attaquant;
        attaquant = defenseur;
        defenseur = temp;

        // Attendre une courte pause pour simuler le déroulement du combat
        printf("\n");
        //sleep(1);
    }

    // Si les deux Pokémons ont encore de la santé après la boucle, c'est un match nul
    printf("Match nul!\n");
}

   
