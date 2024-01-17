all: read_shm write_shm read_on_hv

read_shm: read_shm.c
	gcc -o $@ $<

write_shm: write_shm.c
	gcc -o $@ $<

read_on_hv: ivshmem_mmap.c
	gcc -o $@ $<
