
# MAY NEED TO BE UPDATED

mycc = cc -std=c99 -Wall -pedantic -Werror
ObjectFiles = mergetars.o FindBestDup.o clean.o copy.o createTar.o \
		createdir.o extract.o store.o


mergetars: $(ObjectFiles)
	$(mycc) -o mergetars $(ObjectFiles)

%.o : %.c mergetars.h
	$(mycc) -c $<
clean:
	rm -f $(ObjectFiles)
