#!/bin/sh
echo note: "[oss] Generating ${SHARED_INTERMEDIATE_DIR}/data_manager/oss/collocation_data.data"
exec "${BUILT_PRODUCTS_DIR}/gen_collocation_data_main" "--collocation_data=../../data/dictionary_oss/collocation.txt" "--output=${SHARED_INTERMEDIATE_DIR}/data_manager/oss/collocation_data.data" --binary_mode
exit 1

