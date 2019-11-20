
##########################################################################################
## Running [1;32mclang -fsanitize=address -Wall defect3.c[0m
## Running [1;32mclang -fsanitize=memory -Wall defect3.c[0m
## Running [1;32mcppcheck --enable=all defect3.c[0m
Checking defect3.c ...
## Running [1;32mgcc -Wall defect3.c[0m
## Running [1;32mvalgrind ./a.out[0m
valid: http://hej.com
invalid: http://0123456789ABCDEFGHIJ
## Running [1;32mgcc -fsanitize=address -Wall defect3.c[0m
## Running [1;32m./a.out[0m

##########################################################################################
