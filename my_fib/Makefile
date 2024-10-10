PROGS         =	my_fib
SRCS.my_fib   =	my_fib.c interp.c threaded_code.c svm.c rvm.c

#MKC_FEATURES +=	

CFLAGS.check  =	-Wno-shadow

.PHONY : test_output
test_output:
	@${.OBJDIR}/my_fib -n20 -c2 -r1; \
	${.OBJDIR}/my_fib -n19 -c2 -r2; \
	${.OBJDIR}/my_fib -n18 -c2 -r3; \
	${.OBJDIR}/my_fib -n17 -c2 -s1; \
	${.OBJDIR}/my_fib -n16 -c2 -s2; \
	${.OBJDIR}/my_fib -n15 -c2 -s3; \
	${.OBJDIR}/my_fib -n14 -c2 -s4; \
	${.OBJDIR}/my_fib -t

.include <mkc.minitest.mk>
.include <mkc.prog.mk>
