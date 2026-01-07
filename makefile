HINSTALL=/usr/include/tui
OINSTALL=/usr/bin
LINSTALL=/usr/lib

all: 
	cd lib && make todo
	cd tbuild && make todo
	cd tUI && make todo

clean:
	rm -f obj/* 
	cd lib && make clean
	cd tbuild && make clean
	cd tUI && make clean

install:
	cp obj/*.so $(LINSTALL)
	cp obj/*.a $(LINSTALL)
	cp obj/tbuild $(OINSTALL)
	cp obj/tUI $(OINSTALL)
	mkdir -p $(HINSTALL)
	cp hdrs/* $(HINSTALL)

