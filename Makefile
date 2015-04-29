all: rtsjam

rtsjam:
	gcc -std=gnu99 rtsjam.c -o rtsjam

clean:
	rm rtsjam

install: rtsjam
	cp rtsjam /usr/local/bin

uninstall: /usr/local/bin/rtsjam
	rm /usr/local/bin/rtsjam
	
