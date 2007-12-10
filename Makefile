.PHONY: all install clean

all:
	python setup.py build

install:
	python setup.py install

clean:
	python setup.py clean
	$(RM) -r build
