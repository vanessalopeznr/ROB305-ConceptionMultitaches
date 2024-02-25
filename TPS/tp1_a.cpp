// [TD-1] Mesure de temps et échantillonnage en temps. Juan RAMIREZ
#include <iostream>
#include "time.h"

int main()
{
    timespec time_ts = {1, 500000000};
    double time_ms = 1500.545;

    timespec time_ts_1 = {5, 125012};
    timespec time_ts_2 = {2, 999999999};

    timespec delay_ts = {2, 500000000};

    // =============================================================
    std::cout << "Test timespec_to_ms: " << std::endl;
    std::cout << timespec_to_ms(time_ts) << " [ms] \n" << std::endl;

    timespec time_ts_from_ms = timespec_from_ms(time_ms);
    std::cout << "Test ms_to_timespec: " << std::endl;
    std::cout << time_ts_from_ms << std::endl;
    // =============================================================


    // =============================================================
    timespec time_ts_now = timespec_now();
    std::cout << "Test timespec_now: " << std::endl;
    std::cout << time_ts_now << std::endl;

    timespec time_ts_neg = timespec_negate(time_ts);
    std::cout << "Test timespec_negate: " << std::endl;
    std::cout << time_ts_neg << std::endl;
    // =============================================================


    // =============================================================
    timespec time_ts_add = timespec_add(time_ts_1, time_ts_2);
    std::cout << "Test timespec_add: " << std::endl;
    std::cout << time_ts_add << std::endl;

    timespec time_ts_sub = timespec_subtract(time_ts_1, time_ts_2);
    std::cout << "Test timespec_subtract: " << std::endl;
    std::cout << time_ts_sub << std::endl;
    // =============================================================


    // =============================================================
    std::cout << "Test timespec_wait: Dormir pendant " << timespec_to_ms(delay_ts) << " [ms]" << std::endl;
    timespec elapsed_ts = timespec_wait(delay_ts);
    std::cout << "Finir de dormir. Elapsed time: " << elapsed_ts << std::endl;
    // =============================================================

    
    return 0;
};