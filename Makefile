all: tabvar tabparam

tabvar: tabvar.c
	gcc -Wall tabvar.c -g3 -o $(@)


tabparam: tabparam.c
	gcc -Wall tabparam.c -g3 -o $(@)
