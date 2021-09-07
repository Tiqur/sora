#!/bin/sh

parallel --lb ./a.out ::: $(seq $THREADS)
