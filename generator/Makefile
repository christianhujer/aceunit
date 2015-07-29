SOURCES:=$(sort $(shell find src/prj -name "*.java"))
LIBRARIES:=lib/annotations.jar lib/japi-lib-argparser-0.3.0.jar
MODE:=$(shell which ant && echo ant || echo native)
EMPTY:=
SP:=$(EMPTY) $(EMPTY)

ifeq "$(MODE)" "ant"
AceUnit.jar: $(SOURCES)
	ant
else
AceUnit.jar: copyResources compileClasses
	jar cvfe $@ net.sf.aceunit.GenTest -C classes/production .

.PHONY: copyResources
copyResources: | classes/production/
	rsync -r --exclude="*.java" src/prj/ classes/production/

.PHONY: compileClasses
compileClasses: $(SOURCES) $(LIBRARIES) | classes/production/
	cd classes/production && jar xf ../../lib/annotations.jar
	cd classes/production && jar xf ../../lib/japi-lib-argparser-0.3.0.jar
	javac -sourcepath src/prj/ -d classes/production/ $(SOURCES) -classpath $(subst $(SP),:,$(LIBRARIES))

classes/production/:
	mkdir -p $@

.PHONY: clean
clean:
	$(RM) AceUnit.jar -r classes/
endif
