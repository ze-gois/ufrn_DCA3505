mkdir -p build

for test in $(ls ./tests); do
    echo gcc -o build/$(echo $test | grep -o "t[0-9][0-9]") tests/$test
    gcc -o build/$(echo $test | grep -o "t[0-9][0-9]") tests/$test
    LD_PRELOAD=./liba1.so ./build/$(echo $test | grep -o "t[0-9][0-9]")
done
