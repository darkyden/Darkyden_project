//************************************************************************************
// Nom du fichier : main.c
// Auteur : Harold Malbrouck
//
// Date de création : 30 Mai 2025
// Rev : 1.0
//       2.0 01 Juin 2025
//
// Description : Point d’entrée de l’application LCD interactive sur CM3588.
//               Initialise les pilotes LCD et clavier, puis lance la boucle principale
//               qui affiche un menu interactif selon les touches pressées.
//
//************************************************************************************
#include "../include/serviceMenu.h"
#include "../include/interfaceClavier.h"
#include "../include/interfaceLCD.h"
//#include "../include/serviceAnimation.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <syslog.h>

int main() {
    openlog("lcd_demo", LOG_PID | LOG_CONS, LOG_USER);
    syslog(LOG_INFO, "Démarrage de l'application LCD interactive");

    // Initialisation de l'écran LCD
    if (interfaceLCD_init("/dev/i2c-8", 0x27) < 0) {
        syslog(LOG_ERR, "Erreur d'initialisation LCD");
	fprintf(stderr,"LCD INITT FAILED\\n");
        return EXIT_FAILURE;
    }
    
	// Initialisation du clavier I²C
    if (interfaceClavier_init("/dev/gpiochip3", 10, "/dev/i2c-8", 0x14) < 0) {
        syslog(LOG_ERR, "Erreur d'initialisation clavier");
	fprintf(stderr,"Clavier INIT FAILED\\n");
        return EXIT_FAILURE;
    }
    
	// Affichage du menu principal
    serviceMenu_afficher();

    // Boucle principale d'interaction
    while (1) {
        char touche = interfaceClavier_attendreTouche();
        if (touche) {
            syslog(LOG_INFO, "Touche reçue : %c", touche);
            serviceMenu_traiterTouche(touche);
        }
        sleep(1);
    }

    closelog();
    return EXIT_SUCCESS;
}
