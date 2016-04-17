#!/bin/bash
[ -d CMakeBuild ] || mkdir CMakeBuild
cd CMakeBuild && cmake .. && make && cd ..
