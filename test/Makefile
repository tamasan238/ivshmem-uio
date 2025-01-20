all: read_shm write_shm pass drop read_on_hv

read_shm: read_shm.c
	gcc -o $@ $<

write_shm: write_shm.c
	gcc -o $@ $<

pass: pass.c
	gcc -o $@ $<

drop: drop.c
	gcc -o $@ $<

read_on_hv: ivshmem_mmap.c
	gcc -o $@ $<
