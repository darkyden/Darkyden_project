//************************************************************************************
// Nom du fichier : serviceMenu.c
// Auteur : Harold Malbrouck
//
// Date de création : 1er juin 2025
//
// Description : Service d'affichage du menu principal interactif.
//               Affiche les options sur l’écran LCD et traite les touches reçues.
//************************************************************************************

#include "../include/serviceMenu.h"
#include "../include/interfaceLCD.h"
#include "../include/serviceDateHeure.h"
#include "../include/serviceMonitoring.h"
#include "../include/serviceJeuReflex.h"
#include <string.h>
 
void serviceMenu_afficher() {
//*************************************************************************
// Affiche le menu principal sur l'écran LCD
// avec les options A, B, C, D et 0
//**************************************************************************
    interfaceLCD_clear();

    interfaceLCD_setCursor(0, 0);  // Ligne 1
    interfaceLCD_print("A: Date  B: Heure");

    interfaceLCD_setCursor(1, 0);  // Ligne 2
    interfaceLCD_print("C: Monitor D: Jeu");

    interfaceLCD_setCursor(2, 0);  // Ligne 3
    interfaceLCD_print("0: Menu");
}

void serviceMenu_traiterTouche(char touche) {
//*********************************************************************
// Traite une touche entrée par l'utilisateur depuis le clavier.
// Appelle le service correspondant selon le caractère reçu.
// @param touche Caractère reçu ('A', 'B', 'C', 'D', '0')
//********************************************************************
    switch (touche) {
        case 'A':
            serviceDateHeure_afficherDate();
            break;
        case 'B':
            serviceDateHeure_afficherHeure();
            break;
        case 'C':
            serviceMonitoring_lancer();
            break;
        case 'D':
            serviceJeuReflex_lancer();
            break;
        case '0':
            serviceMenu_afficher(); // Réaffiche le menu
            break;
        default:
            // Message en cas de touche non reconnue
            interfaceLCD_clear();
            interfaceLCD_setCursor(1, 0);
            interfaceLCD_print("Touche invalide !");
            break;
    }
}
