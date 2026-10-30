.PHONY: bench
bench: bench.tsv

tool_lang_script +=	luajit     _   Lua        JIT         scripts_fib/lua_fib
tool_lang_script +=	lua        _   Lua        Interpreter scripts_fib/lua_fib
tool_lang_script +=	gforth     <   Forth      Interpreter scripts_fib/forth_fib
tool_lang_script +=	ruby       _   Ruby       Interpreter scripts_fib/ruby_fib
tool_lang_script +=	mruby      _   Ruby       Interpreter scripts_fib/ruby_fib
tool_lang_script +=	gawk      -f   AWK        Interpreter scripts_fib/awk_fib
tool_lang_script +=	mawk      -f   AWK        Interpreter scripts_fib/awk_fib
tool_lang_script +=	nawk      -f   AWK        Interpreter scripts_fib/awk_fib
tool_lang_script +=	js         _   EcmaScript Interpreter scripts_fib/js_fib
tool_lang_script +=	rhino      _   EcmaScript Interpreter scripts_fib/js_fib
tool_lang_script +=	node       _   EcmaScript JIT         scripts_fib/nodejs_fib
tool_lang_script +=	slsh       _   Slang      Interpreter scripts_fib/slang_fib
tool_lang_script +=	perl       _   Perl       Interpreter scripts_fib/perl_fib
tool_lang_script +=	python2.7  _   Python2    Interpreter scripts_fib/python_fib
tool_lang_script +=	python3.13 _   Python3    Interpreter scripts_fib/python_fib
tool_lang_script +=	pypy       _   Python3    JIT         scripts_fib/python_fib
tool_lang_script +=	pike       _   Pike       Interpreter scripts_fib/pike_fib
tool_lang_script +=	php8.5     _   PHP        Interpreter scripts_fib/php_fib
tool_lang_script +=	./my_fib/my_fib -s4 -     Compiler    _
tool_lang_script +=	./my_fib/my_fib -r3 -     Compiler    _
tool_lang_script +=	./c_fib/c_fib   _ C       Compiler    _

bench.tsv:
	@rm -f ${.TARGET}
.for t o l ijc s in ${tool_lang_script}
	@cmd=`which ${t} 2>/dev/null`; \
	printf '%s' 'Bench for ${t:T}... ' 1>&2; \
	if test -x ${t:Q} -o -n "$$cmd"; then  \
	  { printf '%s %s\t%s\t%s\t' ${t:T} "${o:S/^_$//}" ${l:Q} ${ijc:Q}; \
	    time -p ${t} ${o:S/_//} ${s:S/^_$//} 2>&1 >/dev/null | \
	    awk '$$1 == "user" {print $$2}'; \
	    echo 'done' 1>&2; \
	  } >> ${.TARGET}; \
	else \
	  echo 'NOT FOUND' 1>&2; \
	fi
.endfor

CLEANFILES       +=		bench.tsv
