#!/bin/bash

data_filename=$1

gnuplot -p -e "
set xlabel 'Time (s)';
set ylabel 'Frequency (Hz)';
unset colorbox;
set terminal png transparent interlace large size 800,600 enhanced;
set output '$data_filename.png';
plot '$data_filename' using 2:1:3 with image"

open $data_filename.png


