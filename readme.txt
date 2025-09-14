So as to compile any of the source files, use the following:
g++ -g file.cpp -lncurses -lpanel -o file.exe

Where -g flag is not actually necessary and -lpanel is only needed in panel using lessons (such as 7th).

To compile every file within a directory, use compile_all_in_dir.sh by passing the number of the directory in question.
Example:
    ./compile_all_in_dir.sh 2

The example above will compile separatedly every source file found into "2_Basic_screen_manipulation" directory.
