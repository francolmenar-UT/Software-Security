#!/bin/bash
SOURCES=(
    defect1.c
    defect2.c
    defect3.c
    defect4.c
    defect5.c
    defect6.c
    defect7.c
    defect8.c
    defect9.c
    defect10.c
    defect11.c
    defect12.c
    defect13.c
    defect14.c
)

RED='\033[1;31m'
GREEN='\033[1;32m'
LIGHT_GREY='\033[0;37m'
NC='\033[0m' # No Color


# Set CWD to script dir
cd "${0%/*}"

function run_action() {
  printf "## Running ${GREEN}$1${NC}\n"
  eval $1
}

function run_test() {
        printf "\n##########################################################################################\n"

        run_action "clang -g -fsanitize=address -Wall $1"
        run_action "clang -g -fsanitize=memory -Wall $1"
        run_action "cppcheck --enable=all $1"
        run_action "gcc -g -Wall $1"
        run_action "valgrind --leak-check=full ./a.out"
        run_action "gcc -g -fsanitize=address -Wall $1"
        run_action "./a.out"

        printf "\n##########################################################################################\n"
        

}

function run_for_sources() {
   arr=("$@")
   for i in "${arr[@]}";
      do
        run_test "$i"
        # printf "###############################################################\n"

        # printf "## Running ${LIGHT_GREY} gcc -Wall ${GREEN}$i${NC}\n"
        # gcc -Wall $i

        # printf "## Running ${LIGHT_GREY} clang -fsanitize=address -Wall $i ${GREEN}$i${NC}\n"
        # clang -fsanitize=address -Wall $i

        # printf "## Running ${LIGHT_GREY} clang -fsanitize=memory -Wall $i ${GREEN}$i${NC}\n"
        # clang -fsanitize=memory -Wall $i

        # printf "## Running ${LIGHT_GREY} cppcheck --enable=all --check-config ${GREEN}$i${NC}\n"
        # cppcheck --enable=all --check-config $i

        # printf "## Running ${LIGHT_GREY} valgrind ${GREEN}./a.out${NC}\n"
        # valgrind ./a.out
        # printf "###############################################################\n"
        

      done
}

if [ $# -eq 0 ]
  then
    run_for_sources "${SOURCES[@]}"
  else
    run_test "$1"
fi




# printf "${GREEN} RUNNING FOR FAILING FILES"
# run_and_print $ERROR_SOURCES

# for i in "${ERROR_SOURCES[@]}"; do
#     printf "${GREEN}$ build/compiler --source $i${NC}\n"
    
#     build/compiler --source $i
#     echo ""

# done