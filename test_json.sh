#!/bin/bash

set -e

# Feel free to add more tests. Add files named dumpX.txt that do something
# and then finally dump the content of the tree.

for i in io-tests/*.json; do
    echo "********** Testing $i **********"
    cat $i | python3 io-tests/tool.py -s
    cat $i | python3 io-tests/tool.py -b
done

echo "********** Testing JSON output from 'cargo run' **********"
for i in {1..10}
do
    echo "********** Run $i **********"
   cargo run 1 2>/dev/null | io-tests/tool.py -s
   cargo run 1 2>/dev/null | io-tests/tool.py -b
done