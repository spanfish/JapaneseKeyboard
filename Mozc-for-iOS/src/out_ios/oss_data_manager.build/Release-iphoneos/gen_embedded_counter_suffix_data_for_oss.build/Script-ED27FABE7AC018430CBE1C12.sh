#!/bin/sh
echo note: "[oss] Generating ${SHARED_INTERMEDIATE_DIR}/data_manager/oss/counter_suffix_data.h"
exec python ../../rewriter/gen_counter_suffix_array.py "--id_file=../../data/dictionary_oss/id.def" "--output=${SHARED_INTERMEDIATE_DIR}/data_manager/oss/counter_suffix_data.h" ../../data/dictionary_oss/dictionary00.txt ../../data/dictionary_oss/dictionary01.txt ../../data/dictionary_oss/dictionary02.txt ../../data/dictionary_oss/dictionary03.txt ../../data/dictionary_oss/dictionary04.txt ../../data/dictionary_oss/dictionary05.txt ../../data/dictionary_oss/dictionary06.txt ../../data/dictionary_oss/dictionary07.txt ../../data/dictionary_oss/dictionary08.txt ../../data/dictionary_oss/dictionary09.txt ../../data/dictionary_oss/reading_correction.tsv
exit 1

