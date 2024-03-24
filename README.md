# ROB305-ConceptionMultitaches

This work is made by:
    - **Name**: Juan RAMIREZ
    - **Name**: Vanessa LOPEZ

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

Answer of Tp2 B questions:
- In tp2-A, when performing several iterations, it can be evidenced that the count does not reach the expected value, because there is no blocking when taking the data and it can be overwritten.
- In tp2-B, with the mutex we can see that it protects the data while it is being edited and remains available after the modifications have been made.


To run the files of third Tp, go into the build/Tp3 directory and run the following command:

    ./tp3_a
    ./tp3_b
    ./tp3_c

Answer of Tp3 B questions: 
- The constructor must be public to be instantiated when creating an object and the start and stop methods are the interfaces between the user and the operation of the program and must therefore be public. The class must be able to easily access the Callback( ) method without the user being able to manipulate it directly, therefore, it is defined protected. Call_callback() must be private because it is a method that is only used internally by the class and should not be accessible to the user.

- Call_callback is defined as static in order to maintain a single copy of the class member function on different objects.

- The callback() class must be defined as virtual, as it will be rewritten in each different instance according to the program application.

To run the files of fourth Tp, go into the build/Tp4 directory and run the following command:
    
        ./tp4_a Then, type "s" to stop and enter
        ./tp4_b
        ./tp4_c
        ./tp4_d

To run the files of fifth Tp, go into the build/Tp5 directory and run the following command:
    
        ./tp5_a
