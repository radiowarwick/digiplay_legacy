#!/bin/bash
#
#
if [ -e $1 ]; then
	# -r 		encode directly from RAW format
	# -x 		swap byte order
	# -m s		stereo
	# -s 44.1	sample rate
	# -b 48		output bitrate
	# -q 9		fastest encoding, most enhancements off
	# -c		copyrighted
	# We take the first 5292000 bytes of the file (30 seconds)
	# -- cc --
	head -c 5292000  $1 | lame --silent -r -x -m s --bitwidth 16 -s 44.1 \
		-b 48 -q 9 -c --id3v1-only --tt "Track Preview" --ta "Radio Warwick" \
		--tl "Radio Warwick Music Database" - -
fi
