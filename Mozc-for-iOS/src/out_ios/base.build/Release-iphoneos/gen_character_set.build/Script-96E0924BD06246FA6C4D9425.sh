#!/bin/sh
exec python gen_character_set.py "--cp932file=../data/unicode/CP932.TXT" "--jisx0201file=../data/unicode/JIS0201.TXT" "--jisx0208file=../data/unicode/JIS0208.TXT" "--jisx0212file=../data/unicode/JIS0212.TXT" "--jisx0213file=../data/unicode/jisx0213-2004-std.txt" "--output=${SHARED_INTERMEDIATE_DIR}/base/character_set.h"
exit 1

