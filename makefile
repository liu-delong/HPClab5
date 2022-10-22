VPATH:=src
all:rpfg
omp_gemm:omp_gemm.cpp matrix_tool.cpp
	g++ $^ -g -o $@ -fopenmp
rog:omp_gemm
	./omp_gemm 4 4 4 1
	./omp_gemm 4 4 4 4
	for s in 512 1024 1536 2048; do \
		for t in 1 2 3 4 5 6 7 8; do \
			./omp_gemm $$s $$s $$s $$t; \
		done \
	done
schedule_gemm:schedule_gemm.cpp matrix_tool.cpp
	g++ $^ -g -o $@ -fopenmp
rsg:schedule_gemm
	for s in 4 512 1024 1536 2048; do \
		for m in default static dynamic; do \
			./schedule_gemm $$s $$s $$s 4 $$m; \
		done \
	done
libparallel_for.so:parallel_for.cpp
	g++ $^ -fPIC -shared -o $@ -lpthread
parallel_for_gemm:parallel_for_gemm.cpp matrix_tool.cpp libparallel_for.so
	g++ $^ -L. -lparallel_for -o $@
set_path:=export LD_LIBRARY_PATH=$$LD_LIBRARY_PATH:.
rpfg:parallel_for_gemm
	$(set_path) && ./parallel_for_gemm 1024 1024 1024 1
	$(set_path) && ./parallel_for_gemm 1024 1024 1024 4

