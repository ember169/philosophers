    ____  __    _ __                       __                     
   / __ \/ /_  (_) /___  _________  ____  / /_  ___  __________   
  / /_/ / __ \/ / / __ \/ ___/ __ \/ __ \/ __ \/ _ \/ ___/ ___/   
 / ____/ / / / / / /_/ (__  ) /_/ / /_/ / / / /  __/ /  (__  )    
/_/   /_/ /_/_/_/\____/____/\____/ .___/_/ /_/\___/_/  /____/     
   ______         __            /_/                               
  /_  _ /_  _____/ /____  _____                                   
  / / / _ \/ ___/ __/ _ \/ ___/                                   
 / / /  __(__  ) /_/  __/ /                                       
/_/  \___/____/\__/\___/_/                                      

Will you die in the right way?                                    

PRE-TEST ---------------------------------------------------------->

Make: OK

Norminette: OK

Global Var: 0

DEATH TEST -------------------------------------------------------->
- One philo -

TEST 0: OK

TEST 1: OK

TEST 2: OK

TEST 3: OK

TEST 4: OK

DEATH TEST -------------------------------------------------------->
- No one must die -

TEST 0: OK

TEST 1: OK

TEST 2: OK

TEST 3: OK

TEST 4: OK

TEST 5: OK

TEST 6: OK

TEST 7: KO

    No philosopher should die.

    ARGS: 5 900 295 60 10

TEST 8: OK

TEST 9: OK

DEATH TEST -------------------------------------------------------->
- One must die -

TEST 0: OK

TEST 1: OK

TEST 2: OK

TEST 3: KO

    One philosopher should die.

    HINT: The tester looks for the word 'died' in stdout.

    ARGS: 8 180 60 121 2

TEST 4: OK

TEST 5: OK

TEST 6: OK

TEST 7: OK

TEST 8: OK

TEST 9: OK

VALGRIND ---------------------------------------------------------->
--tool=memcheck -

TEST 0: OK

TEST 1: OK

TEST 2: OK

TEST 3: OK

TEST 4: OK

TEST 5: OK

TEST 6: OK

TEST 7: OK

TEST 8: OK

TEST 9: OK

VALGRIND ---------------------------------------------------------->
--tool=helgrind -

TEST 0: OK

TEST 1: OK

TEST 2: OK

TEST 3: OK

TEST 4: OK

TEST 5: OK

TEST 6: OK

TEST 7: OK

TEST 8: OK

TEST 9: OK

ThreadSanitizer --------------------------------------------------->

TEST 0: OK

TEST 1: OK

TEST 2: OK

TEST 3: OK

TEST 4: OK

TEST 5: OK

TEST 6: OK

TEST 7: OK

TEST 8: OK

TEST 9: OK