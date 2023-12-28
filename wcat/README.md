# wcat
A simple `cat` clone, from: https://github.com/remzi-arpacidusseau/ostep-projects/tree/master/initial-utilities#wcat.

> **Details**
> * Your program **wcat** can be invoked with one or more files on the command
  line; it should just print out each file in turn. 
> * In all non-error cases, **wcat** should exit with status code 0, usually by
  returning a 0 from **main()** (or by calling **exit(0)**).
> * If *no files* are specified on the command line, **wcat** should just exit
  and return 0. Note that this is slightly different than the behavior of 
  normal UNIX **cat** (if you'd like to, figure out the difference).
> * If the program tries to **fopen()** a file and fails, it should print the
  exact message "wcat: cannot open file" (followed by a newline) and exit
  with status code 1.  If multiple files are specified on the command line,
  the files should be printed out in order until the end of the file list is
  reached or an error opening a file is reached (at which point the error
  message is printed and **wcat** exits). 
