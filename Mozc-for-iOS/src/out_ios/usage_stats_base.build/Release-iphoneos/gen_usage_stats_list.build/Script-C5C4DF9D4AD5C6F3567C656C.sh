#!/bin/sh
exec python ../build_tools/redirect.py "${SHARED_INTERMEDIATE_DIR}/usage_stats/usage_stats_list.h" gen_stats_list.py ../data/usage_stats/stats.def
exit 1

