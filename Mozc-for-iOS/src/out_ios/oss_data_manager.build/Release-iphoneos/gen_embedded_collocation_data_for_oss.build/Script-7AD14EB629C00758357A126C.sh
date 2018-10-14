#!/bin/sh
echo note: "[oss] Generating ${SHARED_INTERMEDIATE_DIR}/data_manager/oss/embedded_collocation_data.h"
exec python ../../build_tools/redirect.py "${SHARED_INTERMEDIATE_DIR}/data_manager/oss/embedded_collocation_data.h" "${BUILT_PRODUCTS_DIR}/gen_collocation_data_main" "--collocation_data=../../data/dictionary_oss/collocation.txt"
exit 1

