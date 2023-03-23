#/usr/bin/env bash

set -eu

function testing {
    local input="$1"
    local result="$2"
    local expected="$3"
    if [ "$result" != "$expected" ]; then
	echo "failed (${input},${result},${expected})"
    else
	echo "success (${input},${result},${expected})"
    fi
}

echo "no options"

testing "a b c" "`./slugifier "a b c"`" "a-b-c"
testing " a b c" "`./slugifier " a b c"`" "-a-b-c"
testing "a b c" "`./slugifier "a b c "`" "a-b-c-"
testing " a b c " "`./slugifier " a b c "`" "-a-b-c-"

echo "removing leading dash"

testing "a b c" "`./slugifier -l "a b c"`" "a-b-c"
testing " a b c" "`./slugifier -l " a b c"`" "a-b-c"
testing "a b c " "`./slugifier -l "a b c "`" "a-b-c-"
testing " a b c " "`./slugifier -l " a b c "`" "a-b-c-"

echo "removing trailing dash"

testing "a b c" "`./slugifier -t "a b c"`" "a-b-c"
testing " a b c" "`./slugifier -t " a b c"`" "-a-b-c"
testing "a b c " "`./slugifier -t "a b c "`" "a-b-c"
testing " a b c " "`./slugifier -t " a b c "`" "-a-b-c"

echo "removing both leading and trailing dash"

testing "a b c" "`./slugifier -lt "a b c"`" "a-b-c"
testing " a b c" "`./slugifier -lt " a b c"`" "a-b-c"
testing "a b c " "`./slugifier -lt "a b c "`" "a-b-c"
testing " a b c " "`./slugifier -lt " a b c "`" "a-b-c"
