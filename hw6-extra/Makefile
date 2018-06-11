# CSE 374
# HW 6
# Chen Bai, Luke Jiang
# 15/05/2018

# This is the Makefile for HW 6 project


GCC = gcc -Wall -std=c11 -g
TOTAL = -o
INTER = -c

bench: getmem.o freemem.o get_mem_stats.o print_heap.o mem_utils.o bench.o
	$(GCC) $(TOTAL) bench getmem.o freemem.o get_mem_stats.o print_heap.o mem_utils.o bench.o

getmem.o: getmem.c mem.h mem_impl.h
	$(GCC) $(INTER) getmem.c 

freemem.o: freemem.c mem.h mem_impl.h
	$(GCC) $(INTER) freemem.c

get_mem_stats.o: get_mem_stats.c mem.h mem_impl.h
	$(GCC) $(INTER) get_mem_stats.c

print_heap.o: print_heap.c mem.h mem_impl.h
	$(GCC) $(INTER) print_heap.c

mem_utils.o: mem_utils.c mem_impl.h
	$(GCC) $(INTER) mem_utils.c

bench.o: bench.c mem.h
	$(GCC) $(INTER) bench.c

clean:
	rm -f bench *.o *~ result.txt
