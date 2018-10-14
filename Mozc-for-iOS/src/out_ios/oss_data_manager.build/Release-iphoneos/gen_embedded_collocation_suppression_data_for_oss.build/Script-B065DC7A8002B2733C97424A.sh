#!/bin/sh
echo note: "[oss] Generating ${SHARED_INTERMEDIATE_DIR}/data_manager/oss/embedded_collocation_suppression_data.h"
exec python ../../build_tools/redirect.py "${SHARED_INTERMEDIATE_DIR}/data_manager/oss/embedded_collocation_suppression_data.h" "${BUILT_PRODUCTS_DIR}/gen_collocation_suppression_data_main" "--suppression_data=../../data/dictionary_oss/collocation_suppression.txt"
exit 1

