//************************************************************************************
// Nom du fichier : serviceJeuReflex.c
// Auteur : Harold Malbrouck
//
// Date de création : 1er juin 2025
//
// Description : Service principal pour le jeu de réflexe. Affiche une touche aléatoire
//               à presser entre 1 et 9 et mesure le temps de réaction. Le joueur
//               appuie sur '0' pour revenir au menu.
//
// Dépendances : interfaceJeuReflex.h, interfaceClavier.h, serviceMenu.h
//************************************************************************************

#include "../include/serviceJeuReflex.h"
#include "../include/interfaceJeuReflex.h"
#include "../include/interfaceClavier.h"
#include "../include/serviceMenu.h"
#include <unistd.h>
#include <stdlib.h>
#include <syslog.h>
#include <time.h>
#include <stdio.h>
#include <fcntl.h>
#include <poll.h>
#include <sys/ioctl.h>
#include <gpiod.h>

void serviceJeuReflex_lancer() {
//************************************************************************************
// Fonction principale du jeu de réflexe.
// Génère une touche aléatoire entre 1 et 9, l'affiche sur l'écran LCD,
// attend l'entrée utilisateur, mesure le temps de réaction et affiche le résultat.
// Quitte avec la touche '0'.
//************************************************************************************
    char touche;

    while (1) {
        // Choisir un chiffre entre 1 et 9 à appuyer
        srand(time(NULL));
        int touche_attendue = (rand() % 9) + 1;
        char message[32];

        // Marquer le temps de début
        struct timespec start, end;
        clock_gettime(CLOCK_MONOTONIC, &start);

        // Affiche le message à l'utilisateur
        snprintf(message, sizeof(message), "Appuie sur %d !", touche_attendue);
        interfaceJeuReflex_afficherMessage(message);

        // Attendre la touche pressée
        touche = interfaceClavier_attendreTouche();
        usleep(300000); // anti-rebond simple

        // Si l'utilisateur souhaite quitter
        if (touche == '0') {
            syslog(LOG_INFO, "Sortie du jeu réflexe par touche 0");
            interfaceJeuReflex_afficherMessage("Retour menu...");
            sleep(1);
            break;
        }

        // Si la bonne touche a été pressée
        if (touche == ('0' + touche_attendue)) {
            clock_gettime(CLOCK_MONOTONIC, &end);
            long delta_ms = (end.tv_sec - start.tv_sec) * 1000 +
                            (end.tv_nsec - start.tv_nsec) / 1000000;
            snprintf(message, sizeof(message), "Reflex: %ld ms", delta_ms);
            interfaceJeuReflex_afficherMessage(message);
            sleep(2);
        } 
        // Si une autre touche entre 1 et 9 a été pressée
        else if (touche >= '1' && touche <= '9') {
            interfaceJeuReflex_afficherMessage("Raté !");
            sleep(2);
        }
    }

    // Retour au menu après appui sur '0'
    if (touche == '0') {
        serviceMenu_traiterTouche(touche);
    }
}
