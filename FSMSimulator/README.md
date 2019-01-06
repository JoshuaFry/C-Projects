This program creates a Finite State Machine based of the specFile.txt.
The first letter on any line in the Spec File determines the state, then the transition.
so State A: might have a transition (z,B) where z sends you into state B.
This program takes in 4 command line arguments, the runnable, the specFile.txt, a starting state
and an end state. Once the program begins you will prompted to enter a Test Path of state
transitions that will begin at your specified starting state. If the path does not end at
the correct ending state that was specified or if an incorrect transition is entered the path
will be "REJECTED!" else it will be "ACCEPTED!".
Note that after you enter a test path and press enter you must also press control+d to continue
execution.

ex:

FSMSimulator admin$ ./a.out specFile.txt A S
STATE MACHINE:
A: (a, B)  (b, A)
B: (c, D)  (d, A)
C: (a, A)  (b, A)
S: (b, C)  (c, A)  (d, A)  (e, A)  (s, B)
==================================

Enter Test: a d b a
PATH: B A A B
REJECTED!

ex:

FSMSimulator admin$ ./a.out specFile.txt B A
STATE MACHINE:
A: (a, B)  (b, A)
B: (c, D)  (d, A)
C: (a, A)  (b, A)
S: (b, C)  (c, A)  (d, A)  (e, A)  (s, B)
==================================

Enter Test: d a d a d
PATH: A B A B A
ACCEPTED!
