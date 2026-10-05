SUBPRJ +=	my_fib c_fib scripts_fib presentation
NODEPS +=	test-presentation:test

.include "help.mk"

.include <mkc.subprj.mk>
