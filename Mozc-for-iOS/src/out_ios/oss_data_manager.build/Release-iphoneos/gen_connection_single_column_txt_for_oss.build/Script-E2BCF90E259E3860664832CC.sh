#!/bin/sh
echo note: "[oss] Decompressing ../../data/dictionary_oss/connection.deflate"
exec python ../../build_tools/zlib_util.py decompress ../../data/dictionary_oss/connection.deflate "${SHARED_INTERMEDIATE_DIR}/data_manager/oss/connection_single_column.txt"
exit 1

