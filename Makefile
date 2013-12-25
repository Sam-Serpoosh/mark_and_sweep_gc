default: test

build:
	gcc -o gc mark_and_sweep_test.c mark_and_sweep.c

test: build
	./gc
