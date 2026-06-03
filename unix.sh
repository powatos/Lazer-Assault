#!/bin/bash

set -e

# Ensure LazerAssault.tar.gz exists in current directory
mkdir LazerAssault
tar -xzf LazerAssault.tar.gz -C LazerAssault

LazerAssault/build/LazerAssaultGame