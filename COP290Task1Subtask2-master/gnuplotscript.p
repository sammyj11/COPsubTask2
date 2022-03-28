set style fill solid 0.25 border -1

set style boxplot outliers pointtype 0.1

set style data boxplot

set title 'My Plot' font 'Arial,14';

set xtics ('10' 10, '20' 9, '30' 8, '40' 7, '50' 6,'60' 5 ,'70' 4 , '80' 3,'90' 2,'100' 1)
set yrange[0 : 29500]
set ytics 500

plot for [i=1:10] 'data1.txt' using (i):i notitle
set term png
set output "printme.png"
