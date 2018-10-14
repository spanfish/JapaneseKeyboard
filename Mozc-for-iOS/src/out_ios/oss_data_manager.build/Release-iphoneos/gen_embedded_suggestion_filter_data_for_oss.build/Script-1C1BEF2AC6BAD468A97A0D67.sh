#!/bin/sh
echo note: "[oss] Generating ${SHARED_INTERMEDIATE_DIR}/data_manager/oss/suggestion_filter_data.h"
exec "${BUILT_PRODUCTS_DIR}/gen_suggestion_filter_main" ../../data/dictionary_oss/suggestion_filter.txt "${SHARED_INTERMEDIATE_DIR}/data_manager/oss/suggestion_filter_data.h" --header
exit 1

