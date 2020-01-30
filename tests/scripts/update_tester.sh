test_path="../tiny_lpp_tests"
test_dir="../tiny_lpp_tests/tests/"

passed=0
failed=0

#g++ -g *.h *.cpp
#rm *.gch

cp a.out $test_path

for testFile in ${test_dir}*.lpp; do
    ${test_path}/a.out $testFile
    if [ $? -ne 0 ]; then
        echo -e "Test ${testFile} \e[31mfailed\e[0m"
        printf "\n\e[34mPerhaps the miniLpp program has an empty statement? (empty line inside a Inicio - Fin clause)?\e[0m"
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