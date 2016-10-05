all:
	cd examples; make; cd ..
	cd tests; make; cd ..

.PHONY: clean

clean:
	cd examples; make clean; cd ..
	cd tests; make clean
