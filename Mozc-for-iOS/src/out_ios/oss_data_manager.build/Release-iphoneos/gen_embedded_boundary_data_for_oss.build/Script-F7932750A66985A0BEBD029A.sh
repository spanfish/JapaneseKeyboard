#!/bin/sh
echo note: "[oss] Generating ${SHARED_INTERMEDIATE_DIR}/data_manager/oss/boundary_data.h."
exec python ../../build_tools/redirect.py "${SHARED_INTERMEDIATE_DIR}/data_manager/oss/boundary_data.h" ../../converter/gen_boundary_data.py ../../data/rules/boundary.def ../../data/dictionary_oss/id.def
exit 1

