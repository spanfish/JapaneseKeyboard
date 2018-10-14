#!/bin/sh
echo note: "Generating ${SHARED_INTERMEDIATE_DIR}/session/session_stress_test_data.h"
exec python ../build_tools/redirect.py "${SHARED_INTERMEDIATE_DIR}/session/session_stress_test_data.h" gen_session_stress_test_data.py ../data/test/stress_test/sentences.txt
exit 1

