//************************************************************************************
// Nom du fichier : interfaceJeuReflex.c 
// Auteur : Harold Malbrouck 
//
// Date de création : 01 juin 2025
//
// Description : Module d'interface entre le jeu de réflexe et l'écran LCD.
//               Fournit une fonction pour afficher un message formaté.
//************************************************************************************

#include "../include/interfaceJeuReflex.h"
#include "../include/interfaceLCD.h"

void interfaceJeuReflex_afficherMessage(const char* message) {
//*******************************************************************************************
// Affiche un message sur le LCD avec un titre prédéfini pour le jeu de réflexe.
// Le message est affiché sur la deuxième ligne, la première ligne sert de titre.
//
// @param message Chaîne de caractères à afficher sous "REFLEX TEST".
//*******************************************************************************************
    interfaceLCD_clear();                  // Efface complètement l’écran
    interfaceLCD_setCursor(0, 0);          // Ligne 1, position 0
    interfaceLCD_print("REFLEX TEST");     // Affiche le titre

    interfaceLCD_setCursor(1, 0);          // Ligne 2, position 0
    interfaceLCD_print(message);           // Affiche le message spécifique
}
