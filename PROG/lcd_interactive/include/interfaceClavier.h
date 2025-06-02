//************************************************************************************
// Nom du fichier : interfaceClavier.h 
// Auteur : Harold Malbrouck 
//
// Date de création : 30 Mai 2025
// Rev : 1.0
//       2.0 01 Juin 2025 
//
//  Description : Interface du module de gestion du clavier I²C avec interruption GPIO
//************************************************************************************
#ifndef INTERFACE_CLAVIER_H
#define INTERFACE_CLAVIER_H

int interfaceClavier_init(const char *chipname, int ligne_gpio, const char *i2c_device, int i2c_addr);
char interfaceClavier_attendreTouche(void);

#endif