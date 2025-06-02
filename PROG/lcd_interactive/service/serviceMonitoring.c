//************************************************************************************
// Nom du fichier : serviceMonitoring.c
// Auteur : Harold Malbrouck
//
// Date de création : 30 mai 2025
// Rev: 1.0
//      2.0 01 juin 2025
//
// Description : Service d'affichage des statistiques système sur l'écran LCD I2C.
//               Affiche la température CPU, l'utilisation de la RAM et l'utilisation
//               du stockage eMMC. Le tout formaté sur 3 lignes du LCD.
//************************************************************************************

#include "../include/serviceMonitoring.h"
#include "../include/interfaceLCD.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void serviceMonitoring_lancer() {
//*********************************************************************************
// Lance le service de monitoring système.
// Lit les valeurs actuelles de température CPU, RAM et espace disque utilisé,
// puis les affiche sur l'écran LCD.
//**********************************************************************************
    char buffer[64];

    // --- Lecture de la température CPU ---
    FILE *fp = fopen("/sys/class/thermal/thermal_zone0/temp", "r");
    int temp = 0;
    if (fp) {
        fscanf(fp, "%d", &temp);   // La température est lue en millidegrés
        fclose(fp);
        temp /= 1000;              // Conversion en degrés Celsius
    }

    // --- Lecture de l'utilisation de la RAM ---
    long total = 0, free = 0;
    FILE *mem = fopen("/proc/meminfo", "r");
    if (mem) {
        char line[128];
        while (fgets(line, sizeof(line), mem)) {
            if (sscanf(line, "MemTotal: %ld kB", &total) == 1) continue;
            if (sscanf(line, "MemAvailable: %ld kB", &free) == 1) break;
        }
        fclose(mem);
    }

    int used = (total > 0) ? (int)(((total - free) * 100) / total) : 0;

    // --- Lecture de l’utilisation de la eMMC (via 'df') ---
    FILE *df = popen("df / | awk 'NR==2 {print $5}'", "r");
    char usage[8] = "?";
    if (df) {
        fgets(usage, sizeof(usage), df);  // Exemple de résultat : "45%"
        pclose(df);
    }

    // --- Affichage sur LCD ---
    interfaceLCD_clear();

    snprintf(buffer, sizeof(buffer), "CPU: %dC", temp);
    interfaceLCD_setCursor(0, 0);
    interfaceLCD_print(buffer);

    snprintf(buffer, sizeof(buffer), "RAM: %d%%", used);
    interfaceLCD_setCursor(1, 0);
    interfaceLCD_print(buffer);

    snprintf(buffer, sizeof(buffer), "eMMC: %s", usage);
    interfaceLCD_setCursor(2, 0);
    interfaceLCD_print(buffer);
}
