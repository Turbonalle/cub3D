#!/bin/bash

find ../src/ -type f -exec cat {} \; | wc -l