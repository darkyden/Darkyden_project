//************************************************************************************
// Nom du fichier : serviceDateHeure.c
// Auteur : Harold Malbrouck
//
// Date de création : 1er juin 2025
//
// Description : Service d'affichage de la date et de l'heure sur un écran LCD I²C.
//               Utilise les fonctions de la couche interface pour manipuler le LCD.
//************************************************************************************

#include "../include/interfaceLCD.h"
#include <time.h>

void serviceDateHeure_afficherDate() {
//************************************************************************************
// Affiche la date actuelle (format AAAA-MM-JJ) sur l'écran LCD.
//************************************************************************************
    char buffer[32];
    time_t now = time(NULL);                  // Récupère l'heure système actuelle
    struct tm *t = localtime(&now);           // Convertit en structure tm locale
    strftime(buffer, sizeof(buffer), "%Y-%m-%d", t); // Formate la date
    interfaceLCD_clear();                     // Efface l’écran
    interfaceLCD_setCursor(1, 4);             // Place le curseur
    interfaceLCD_print(buffer);               // Affiche la dat
}

void serviceDateHeure_afficherHeure() {
//************************************************************************************
// Affiche l'heure actuelle (format HH:MM:SS) sur l'écran LCD.
//************************************************************************************
    char buffer[32];
    time_t now = time(NULL);                  // Récupère l'heure système actuell
    struct tm *t = localtime(&now);           // Convertit en structure tm locale
    strftime(buffer, sizeof(buffer), "%H:%M:%S", t); // Formate l'heure
    interfaceLCD_clear();
    interfaceLCD_setCursor(1, 5);
    interfaceLCD_print(buffer);
}