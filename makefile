#!/bin/bash
SRCS := $(wildcard *.cpp)
OBJS := ./DES

all: $(OBJS)

$(OBJS): $(SRCS)
	clang++ -Wall -std=c++14 $(SRCS) -o $(OBJS)
