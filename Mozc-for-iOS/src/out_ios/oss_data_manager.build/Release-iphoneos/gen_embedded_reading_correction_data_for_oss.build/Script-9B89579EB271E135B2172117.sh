#!/bin/sh
echo note: "[oss] Generating ${SHARED_INTERMEDIATE_DIR}/data_manager/oss/reading_correction_data.h"
exec python ../../rewriter/gen_reading_correction_data.py "--output=${SHARED_INTERMEDIATE_DIR}/data_manager/oss/reading_correction_data.h" "--input=../../data/dictionary_oss/reading_correction.tsv"
exit 1

