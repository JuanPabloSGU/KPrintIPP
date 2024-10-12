all:
	$ (MAKE) -C src/pdl
	$ (MAKE) -C src/kernel
clean:
	$ (MAKE) -C src/pdl clean
	$ (MAKE) -C src/kernel clean
