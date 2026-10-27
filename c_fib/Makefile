PROGS         =	c_fib c_fib2
SRCS.c_fib    =	c_fib.c
SRCS.c_fib2   =	c_fib2.c

.PHONY : test_output
test_output:
	@${.OBJDIR}/c_fib -n20 -c1; \
	${.OBJDIR}/c_fib -n19 -c5; \
	${.OBJDIR}/c_fib2 -n20 -c1;\
	${.OBJDIR}/c_fib2 -n19 -c5

# COPTS        ?=	-O1
CFLAGS.check += -fomit-frame-pointer

.include <mkc.minitest.mk>
.include <mkc.prog.mk>
