#!/bin/bash

FLAC="flac"
ENC_FLAC_ARGS="--endian=little --channels=2 --bps=16 --sample-rate=44100 --sign=signed --force-raw-format -V -f --seekpoint=1s --best"
DEC_FLAC_ARGS="-d --endian=little --sign=signed --force-raw-format -V -f"
FILES="0???????????????????????????????"
DIR="/mnt/music1/audio/0/"

find $DIR -type f -name $FILES -exec $FLAC $ENC_FLAC_ARGS {} -o {}.flac \;
#find $DIR -type f -name $FILES -exec $FLAC $DEC_FLAC_ARGS {}.flac -o {}.raw \;
#find $DIR -type f -name $FILES -exec mv {}.raw {} \;
