#!/bin/sh
echo note: "[oss] Generating ${SHARED_INTERMEDIATE_DIR}/data_manager/oss/segmenter_data.h."
exec "${BUILT_PRODUCTS_DIR}/gen_oss_segmenter_bitarray_main" "--output=${SHARED_INTERMEDIATE_DIR}/data_manager/oss/segmenter_data.h"
exit 1

