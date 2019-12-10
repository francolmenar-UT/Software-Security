#!/bin/bash

set -e

# Feel free to add more tests. Add files named dumpX.txt that do something
# and then finally dump the content of the tree.

for i in io-tests/*.json; do
    echo "********** Testing $i **********"
    cat $i | python3 io-tests/tool.py -s
    cat $i | python3 io-tests/tool.py -b
done
