// [TD-1] Mesure de temps et échantillonnage en temps. Juan RAMIREZ
#ifndef time_h_INCLUDED
#define time_h_INCLUDED

#include <iostream>
#include <time.h>
#include <unistd.h>

// a) Gestion simplifiée du temps Posix

// Fonction pour imprimer un timespec
std::ostream& operator<<(std::ostream& os, const timespec& time_ts);

// Déclarez et implémentez les fonctions suivantes permettant de convertir des millisecondes en timespec et vice-versa:
double timespec_to_ms(const timespec& time_ts);
timespec timespec_from_ms(double time_ms);

// Déclarez et implémentez les fonctions suivantes permettant respectivement d'obtenir le temps courant et l'opposé d'un temps:
timespec timespec_now();
timespec timespec_negate(const timespec& time_ts);

// Déclarez et implémentez les fonctions suivantes permettant respectivement d’ajouter et de soustraire deux timespec:
timespec timespec_add(const timespec& time1_ts, const timespec& time2_ts);
timespec timespec_subtract(const timespec& time1_ts, const timespec& time2_ts);

// En utilisant la fonction Posix nanosleep(), déclarez et implémentez la fonction suivante permettant d’endormir
// la tâche appelante durant le temps spécifié.
timespec timespec_wait(const timespec& delay_ts);

// En utilisant les fonctions ci-dessous, déclarez et implémentez les opérateurs ci-dessous afin de pouvoir utiliser les variables timespec comme des scalaires:
timespec  operator- (const timespec& time_ts);
timespec  operator+ (const timespec& time1_ts, const timespec& time2_ts);
timespec  operator- (const timespec& time1_ts, const timespec& time2_ts);
timespec& operator+= (timespec& time_ts, const timespec& delay_ts);
timespec& operator-= (timespec& time_ts, const timespec& delay_ts);
bool operator== (const timespec& time1_ts, const timespec& time2_ts);
bool operator!= (const timespec& time1_ts, const timespec& time2_ts);
bool operator< (const timespec& time1_ts, const timespec& time2_ts);
bool operator> (const timespec& time1_ts, const timespec& time2_ts);

#endif // time_h
