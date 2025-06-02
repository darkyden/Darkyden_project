//************************************************************************************
// Nom du fichier : serviceJeu.c
// Auteur : Harold Malbrouck
//
// Date de création : 1er juin 2025
//
// Description : Service du mini-jeu pour écran LCD. 
//               Affiche un caractère qui défile de gauche à droite puis revient,
//               puis un message de fin sur une ligne différente.
//************************************************************************************

#include "../include/interfaceLCD.h"
#include <unistd.h>  // pour usleep()

void serviceJeu_lancer() {
//************************************************************************************
// Lance un petit animation simple : un caractère "O" défile de gauche à droite
//************************************************************************************
    interfaceLCD_clear();  // Nettoie l’écran avant de commencer

    // Mouvement de gauche à droite sur la ligne 3
    for (int i = 0; i < 20; i++) {
        interfaceLCD_clear();             // Efface pour chaque nouvelle position
        interfaceLCD_setCursor(2, i);     // Ligne 3 (indexée à partir de 0), colonne i
        interfaceLCD_print("O");          // Affiche le caractère
        usleep(120000);                   // Pause entre chaque déplacement (~120 ms)
    }

    // Mouvement de droite à gauche sur la ligne 2
    for (int i = 19; i >= 0; i--) {
        interfaceLCD_clear();             // Efface l’écran
        interfaceLCD_setCursor(1, i);     // Ligne 2, colonne i
        interfaceLCD_print("O");          // Affiche le caractère
        usleep(120000);                   // Pause
    }

    // Message de fin
    interfaceLCD_setCursor(3, 3);         // Ligne 4, colonne 4
    interfaceLCD_print("Fin du jeu!");
}
