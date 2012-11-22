#
# Columnstacks
#	xtic labels should be picked up from column heads ('title column')
#	key titles should be picked up from row heads ('key(1)')
#
set title "Immigration from Northern Europe\n(columstacked histogram)"
set style histogram columnstacked
set key noinvert box
set yrange [0:*]
set ylabel "Immigration by decade"
set xlabel "Country of Origin"
set tics scale 0.0
set ytics
unset xtics
set xtics norotate nomirror
plot 'immigration.dat' using 6 ti col, '' using 12 ti col, \
     '' using 13 ti col, '' using 14:key(1) ti col
#
