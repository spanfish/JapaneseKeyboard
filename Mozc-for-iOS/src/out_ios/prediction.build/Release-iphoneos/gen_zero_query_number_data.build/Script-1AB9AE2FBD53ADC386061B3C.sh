#!/bin/sh
echo note: "Generating ${SHARED_INTERMEDIATE_DIR}/prediction/zero_query_number_data.h"
exec python ../build_tools/redirect.py "${SHARED_INTERMEDIATE_DIR}/prediction/zero_query_number_data.h" gen_zero_query_number_data.py ../data/zero_query/zero_query_number.def
exit 1

