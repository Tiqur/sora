#!/bin/sh

eval "parallel --lb ./a.out ::: {1..$THREADS}"
