#!/usr/bin/env sh
mkdir -p env

cd env

# Download cpputest-3.8
wget https://github.com/cpputest/cpputest/releases/download/v3.8/cpputest-3.8.tar.gz

# unarchive cpputest
tar -xzvf cpputest-3.8.tar.gz

cd cpputest-3.8

./configure && make

export CPPUTEST_HOME="$PWD"
