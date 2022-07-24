Sofia Kampaki 3221

First of all we have tou add out syscalls to the kernel 
then we add the syscalls to the syscall table and define a function pointer for each one of them
Then we implement them and edit the makefile that compiles the kernel respectively.After that we compile the kernel and wait for a couple time
When its finished we are ready to start our VM  with the img and the test source code and our new edited kernel.There we can see how it works and what messages
are printed.The test code obly checks for pid = -1.
