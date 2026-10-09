#!/bin/bash
mkdir -p logs reports build
: > logs/build.log
BUILD=FAILED; ANALYSIS=SKIPPED; TESTS=SKIPPED; SIZE=SKIPPED; RESULT=FAILED

run_stage() {
  echo "=== STAGE: $1 ===" | tee -a logs/build.log
  shift
  "$@" 2>&1 | tee -a logs/build.log
  return "${PIPESTATUS[0]}"
}

if run_stage "BUILD" make clean all; then
  BUILD=PASSED; ANALYSIS=FAILED
  if run_stage "STATIC ANALYSIS" make analyze; then
    ANALYSIS=PASSED; TESTS=FAILED
    if run_stage "UNIT TESTS" make test; then
      TESTS=PASSED; SIZE=FAILED
      if run_stage "SIZE REPORT" make size; then
        SIZE=PASSED; RESULT=PASSED
      fi
    fi
  fi
fi

printf "BUILD : %s\nSTATIC ANALYSIS : %s\nUNIT TESTS : %s\nSIZE REPORT : %s\nPIPELINE RESULT : %s\n" \
  "$BUILD" "$ANALYSIS" "$TESTS" "$SIZE" "$RESULT" > reports/ci_report.txt
cat reports/ci_report.txt
[ "$RESULT" = "PASSED" ]
