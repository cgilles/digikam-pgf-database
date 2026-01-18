#!/bin/bash

# Copyright (c) 2021, Dmitri Popov, <dmpop@linux.com>
#
# Redistribution and use is allowed according to the terms of the BSD license.

dir="$HOME/digikam-thumbnails"
if [ -z "$1" ]; then
echo "Specify path to the thumbnails-digikam.db database"
echo "example $0 /path/to/thumbnails-digikam.db"
 exit 1
fi
cd
mkdir -p $dir
sqlite3 $1 "SELECT writefile('$dir/thumbnail-' || id || '.pgf', data) from Thumbnails;"
echo "-----"
echo "All done! Thumbnails have been exported to $dir"
