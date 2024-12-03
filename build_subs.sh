#!/bin/bash

cd /external

git submodule update --recursive --remote

echo "Submodules updated successfully"