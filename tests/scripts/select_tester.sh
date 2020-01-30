test_dir="./tests/select_tests/"

echo "Compiling make!...."

make

if [ $? -ne 0 ]; then 
    echo "Make failed"
    exit 1
fi

clear

passed=0
failed=0


for testFile in ${test_dir}*.txt; do
    ./a.out $testFile
    if [ $? -ne 0 ]; then
        echo -e "Test ${testFile} \e[31mfailed\e[0m"
        printf "\n\n ------------------------------------------ \n\n"
        failed=$((failed + 1))
    else
        echo -e "Test ${testFile} \e[32mpassed\e[0m"
        echo
        passed=$((passed + 1))
    fi
done


total=$((failed + passed))
echo "============================="
echo -e "Total tests: $total"
echo -e "Failed: \e[31m$failed\e[0m"
echo -e "Passed: \e[32m$passed\e[0m"
echo "============================="



