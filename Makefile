all : nm objdump

$(NAME) :
	(cd nm; make all)

clean :
	(cd nm; make clean)
	(cd objdump; make clean)

fclean:
	(cd nm; make fclean)
	(cd objdump; make fclean)

re : fclean all


nm:
	(cd nm; make all)
	(cd objdump; make all)

objdump :
	(cd objdump; make all)

.PHONY: all clean flcean re nm objdump
