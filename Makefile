all : nm

$(NAME) :
	(cd nm; make all)

clean :
	(cd nm; make clean)

fclean:
	(cd nm; make fclean)

re : fclean all


nm:
	(cd nm; make all)

.PHONY: all clean flcean re nm
