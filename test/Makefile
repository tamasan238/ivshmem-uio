all: read_shm write_shm write_shm_pass write_shm_drop read_on_hv

read_shm: read_shm.c
	gcc -o $@ $<

write_shm: write_shm.c
	gcc -o $@ $<

write_shm_pass: write_shm_pass.c
	gcc -o $@ $<

write_shm_drop: write_shm_drop.c
	gcc -o $@ $<

read_on_hv: ivshmem_mmap.c
	gcc -o $@ $<
