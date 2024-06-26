// [TD1-a]

#include <iostream>
#include "time.h"

// Pas define. Mieux const

// a) Gestion simplifiée du temps Posix

// Fonction pour imprimer un timespec
std::ostream& operator<<(std::ostream& os, const timespec& time_ts)
{
    // Overload de l'opérateur << pour afficher un timespec
    os << time_ts.tv_sec << "[s], " << time_ts.tv_nsec << " [ns]" << "\n" << std::endl;
    return os;
};

// Déclarez et implémentez les fonctions suivantes permettant de convertir des millisecondes en timespec et vice-versa:
//(const ref&): C/C++ est passage par copy, alors on va copier un adress plutot que le valeur(long) (On veut pas le modifier)
double timespec_to_ms(const timespec& time_ts)
{
    double time_ms = time_ts.tv_sec * 1000.0 + time_ts.tv_nsec / 1000000.0;
    return time_ms;
};

timespec timespec_from_ms(double time_ms)
{
    timespec time_ts;
    time_ts.tv_sec = time_ms / 1000.0;
    time_ts.tv_nsec = (time_ms - time_ts.tv_sec * 1000.0) * 1000000.0;
    return time_ts;
};



// Déclarez et implémentez les fonctions suivantes permettant respectivement d'obtenir le temps courant et l'opposé d'un temps:
timespec timespec_now()
{
    timespec time_ts;
    clock_gettime(CLOCK_REALTIME, &time_ts);
    return time_ts;
};

timespec timespec_negate(const timespec& time_ts)
{
    timespec time_ts_neg;
    time_ts_neg.tv_sec = -time_ts.tv_sec;
    time_ts_neg.tv_nsec = -time_ts.tv_nsec;
    return time_ts_neg;
};



// Déclarez et implémentez les fonctions suivantes permettant respectivement d’ajouter et de soustraire deux timespec:
timespec timespec_add(const timespec& time1_ts, const timespec& time2_ts)
{
    timespec time_ts;
    time_ts.tv_sec = time1_ts.tv_sec + time2_ts.tv_sec;
    time_ts.tv_nsec = time1_ts.tv_nsec + time2_ts.tv_nsec;
    
    if (time_ts.tv_nsec >= 1000000000)
    {
        // Overflow dans les nanosecondes => on ajoute 1 seconde et on retire 1 milliard de nanosecondes
        time_ts.tv_sec += 1;
        time_ts.tv_nsec -= 1000000000;
    }
    
    return time_ts;
};

timespec timespec_subtract(const timespec& time1_ts, const timespec& time2_ts)
{
    timespec time_ts;
    time_ts.tv_sec = time1_ts.tv_sec - time2_ts.tv_sec;
    time_ts.tv_nsec = time1_ts.tv_nsec - time2_ts.tv_nsec;
    
    if (time_ts.tv_nsec < 0)
    {
        // Underflow dans les nanosecondes => on retire 1 seconde et on ajoute 1 milliard de nanosecondes
        time_ts.tv_sec -= 1;
        time_ts.tv_nsec += 1000000000;
    }
    
    return time_ts;
};



// En utilisant la fonction Posix nanosleep(), déclarez et implémentez la fonction suivante permettant d’endormir la tâche appelante durant le temps spécifié.
timespec timespec_wait(const timespec& delay_ts)
{
    timespec remaining_ts = delay_ts;
    timespec elapsed_ts;

    // Keep trying to sleep for the specified time
    while (true) {
        if (nanosleep(&remaining_ts, &elapsed_ts) == 0) {
            // Sleep successful, break out of the loop
            break;
        } else if (errno == EINTR) {
            // If nanosleep was interrupted by a signal, retry with the remaining time
            remaining_ts = elapsed_ts;
        } else {
            // Handle other errors (display an error message, exit, etc.)
            std::cerr << "Error in nanosleep" << std::endl;
            exit(EXIT_FAILURE);
        }
    }

    return elapsed_ts;
};



// Déclarez et implémentez les opérateurs ci-dessous afin de pouvoir utiliser les variables timespec comme des scalaires:
timespec  operator- (const timespec& time_ts)
{
    timespec time_ts_neg = timespec_negate(time_ts);
    return time_ts_neg;
};

timespec  operator+ (const timespec& time1_ts, const timespec& time2_ts)
{
    timespec time_ts_add = timespec_add(time1_ts, time2_ts);
    return time_ts_add;
};

timespec  operator- (const timespec& time1_ts, const timespec& time2_ts)
{
    timespec time_ts_sub = timespec_subtract(time1_ts, time2_ts);
    return time_ts_sub;
};

timespec& operator+= (timespec& time_ts, const timespec& delay_ts)
{
    time_ts = timespec_add(time_ts, delay_ts);
    return time_ts;
};

timespec& operator-= (timespec& time_ts, const timespec& delay_ts)
{
    time_ts = timespec_subtract(time_ts, delay_ts);
    return time_ts;
};

bool operator== (const timespec& time1_ts, const timespec& time2_ts)
{
    return (time1_ts.tv_sec == time2_ts.tv_sec) && (time1_ts.tv_nsec == time2_ts.tv_nsec);
};

bool operator!= (const timespec& time1_ts, const timespec& time2_ts)
{
    return !(time1_ts == time2_ts);
};

bool operator< (const timespec& time1_ts, const timespec& time2_ts)
{
    if (time1_ts.tv_sec < time2_ts.tv_sec)
    {
        return true;
    }
    else if (time1_ts.tv_sec == time2_ts.tv_sec)
    {
        return (time1_ts.tv_nsec < time2_ts.tv_nsec);
    }
    else
    {
        return false;
    }
};

bool operator> (const timespec& time1_ts, const timespec& time2_ts)
{
    return (time2_ts < time1_ts);
};
