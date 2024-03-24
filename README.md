# ROB305-ConceptionMultitaches

For compilation, use the following command in TPS directory:

    mkdir build
    cd build
    cmake ..
    make

To run the files of first Tp, go into the build/Tp1 directory and run the following command:

    ./tp1_a
    ./tp1_b
    ./tp1_c {Counter}

To run the files of second Tp, go into the build/Tp2 directory and run the following command:

    ./tp2_a {loop} {tasks}
    ./tp2_b {loop} {tasks} {UtilizMutex: true or false}

To run the files of third Tp, go into the build/Tp3 directory and run the following command:

    ./tp3_a
    ./tp3_b
    ./tp3_c

Answer of Tp3 B questions: 
- Call_callback est défini comme statique afin de conserver une copie unique de la fonction membre de la classe sur différents objets.
- La classe callback() doit être définie comme virtuelle, car elle sera réécrite dans chaque instance différente en fonction de l'application du programme.

To run the files of fourth Tp, go into the build/Tp4 directory and run the following command:
    
        ./tp4_a Then, type "s" to stop and enter
        ./tp4_b
        ./tp4_c

To run the files of fifth Tp, go into the build/Tp5 directory and run the following command:
    
        ./tp5_a
