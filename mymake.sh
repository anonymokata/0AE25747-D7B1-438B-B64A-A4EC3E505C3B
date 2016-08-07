#!/bin/bash
sleep 2
make
sleep 2
cd tests
sleep 2
make check_romancalc
sleep 2
cd ..
sleep 2
make check
