#!/bin/bash

time root -b -q -l run_Plotter.C+

find plotFiles/ -type d -exec cp plugins/index.php {} \;