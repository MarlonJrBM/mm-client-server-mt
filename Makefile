BIN_0 = cliente
BIN_1 = servidor

.PHONY: cliente servidor clean

all: $(BIN_0) $(BIN_1)
	@echo Success

$(BIN_0):
	make -f client.mk

$(BIN_1):
	make -f server.mk

doc:
	doxygen Doxyfile

clean:
	make clean -f client.mk
	make clean -f server.mk
	-rm -rf doc

depend:
	make depend -f client.mk
	make depend -f server.mk



# DO NOT DELETE
