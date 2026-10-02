ACEUNIT:=../../../bin/aceunit

.ONESHELL:

.PHONY: all
all:
	if $(ACEUNIT) does-not-exist.o >/dev/null ; then
		echo "error: non-existent file should lead to exit 1."
		exit 1
	fi

.PHONY: clean
clean:: ;
