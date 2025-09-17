# rm -rf ./build
# mkdir ./build
# cd ./build
# cmake ..
# make
# cd ..

TEST_BINARIES=$(find ./build -regex "\./build/t[0-9][0-9].*" -executable | sort)
LD_PRELOAD=./build/liblockdep_interpose.so ./build/t02_classic_deadlock

exit

for test_binary in $TEST_BINARIES; do
    echo LD_PRELOAD=./build/liblockdep_interpose.so $test_binary
    LD_PRELOAD=./build/liblockdep_interpose.so $test_binary
done

# ./build/t02_classic_deadlock &
# export TRACEE_PID=$!
# echo "Classic Deadlock at PID=$TRACEE_PID"
# sleep 3
# sudo ./build/ptrace-lockdep --verbose --all-threads --timeout=20 $TRACEE_PID
# export TRACER_PID=$!
