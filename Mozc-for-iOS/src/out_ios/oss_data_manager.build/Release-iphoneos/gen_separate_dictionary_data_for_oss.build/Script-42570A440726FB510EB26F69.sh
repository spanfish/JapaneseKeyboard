#!/bin/sh
echo note: "Generating ${SHARED_INTERMEDIATE_DIR}/data_manager/oss/system.dictionary."
exec "${BUILT_PRODUCTS_DIR}/gen_system_dictionary_data_main" "--input=../../data/dictionary_oss/dictionary00.txt ../../data/dictionary_oss/dictionary01.txt ../../data/dictionary_oss/dictionary02.txt ../../data/dictionary_oss/dictionary03.txt ../../data/dictionary_oss/dictionary04.txt ../../data/dictionary_oss/dictionary05.txt ../../data/dictionary_oss/dictionary06.txt ../../data/dictionary_oss/dictionary07.txt ../../data/dictionary_oss/dictionary08.txt ../../data/dictionary_oss/dictionary09.txt ../../data/dictionary_oss/reading_correction.tsv" "--output=${SHARED_INTERMEDIATE_DIR}/data_manager/oss/system.dictionary"
exit 1

