#!/bin/bash
ls && mkdir -p build && cd build && cmake .. && make && cd .. && ls
