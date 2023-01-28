benchmark: benchmark.cpp pooled_allocator.hpp
	g++ -O3 -o benchmark -lmimalloc -L/usr/local/lib/mimalloc-2.0 -I/usr/local/include/mimalloc-2.0 benchmark.cpp

.PHONY: clean
clean:
	rm benchmark

.PHONY: run
run:
	MIMALLOC_SHOW_STATS=1 MIMALLOC_LARGE_OS_PAGES=1 ./benchmark