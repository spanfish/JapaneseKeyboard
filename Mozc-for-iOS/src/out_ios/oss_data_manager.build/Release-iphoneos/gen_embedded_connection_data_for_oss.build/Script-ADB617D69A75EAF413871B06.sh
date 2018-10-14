#!/bin/sh
echo note: "[oss] Generating ${SHARED_INTERMEDIATE_DIR}/data_manager/oss/embedded_connection_data.h"
exec python ../../data_manager/gen_connection_data.py "--text_connection_file=${SHARED_INTERMEDIATE_DIR}/data_manager/oss/connection_single_column.txt" "--id_file=../../data/dictionary_oss/id.def" "--special_pos_file=../../data/rules/special_pos.def" "--header_output_file=${SHARED_INTERMEDIATE_DIR}/data_manager/oss/embedded_connection_data.h" "--target_compiler=clang" "--use_1byte_cost=0"
exit 1

