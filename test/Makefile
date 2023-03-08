# Do not include cross in subs, people will not want to run this automatically.
subs:=\
    coverage-clang/ \
    coverage-gcov/ \
    e2eTests/ \
    generatorTests/ \
    special/ \


include ../recurse.mk

all::
	$(MAKE) -C generatorTests clean
	$(MAKE) -C generatorTests all

all::
	$(MAKE) -C generatorTests clean
	ACEUNIT_FLAGS="-t objdump" $(MAKE) -C generatorTests all

all::
	$(MAKE) -C generatorTests clean
	ACEUNIT_FLAGS="-t nm"      $(MAKE) -C generatorTests all

all::
	$(MAKE) -C generatorTests clean
	ACEUNIT_FLAGS="-t readelf" $(MAKE) -C generatorTests all

