#include <stdio.h> // Bibliothèque standard du C utilisée pour les opérations d'entrée/sortie
#include <stdlib.h> // Bibliothèque standard du C utilisée pour la gestion de la mémoire dynamique, le contrôle des processus, la conversion de types et diverses autres fonctions utilitaires
#include <string.h> // Cette bibliothèque standard du C est utilisée pour manipuler des chaînes de caractères et des blocs de mémoire

#define MAX_LINE_LENGTH 1024

// Fonction vérifiant si une ligne correspond à la regex [abc]*
int verifier_regex(const char *ligne) {
    int longueur_chaine = strlen(ligne);

    for (int i = 0; i < longueur_chaine - 1; i++) {
        // Vérifie si chaque caractère est 'a', 'b' ou 'c'
        if (ligne[i] != 'a' && ligne[i] != 'b' && ligne[i] != 'c') {
            return 0;
        }
    }

    return 1;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Utilisez: %s <filename>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    FILE *file = fopen(argv[1], "r");
    if (!file) {
        perror("Erreur lors de l'ouverture du fichier");
        exit(EXIT_FAILURE);
    }

    char ligne[MAX_LINE_LENGTH];
    int count = 0;

    // On crée une boucle while pour lire le fichier ligne par ligne
    while (fgets(ligne, sizeof(ligne), file)) {
        // Vérifie si la ligne correspond à la regex
        if (verifier_regex(ligne)) {
            count++;
        }
    }

    fclose(file);

    printf("Nombre de lignes correspondantes au regex [abc]* : %d\n", count);
    return 0;
}


/*
    Commandes pour l'exécution

    gcc -o exo6-2 exo6-2.c
    ./exo6-2 /home/broly/Bureau/source/Fichiers/sample.txt
*/