############################################################

MKC_REQUIRE_PROGS =	${PS2PDF} ${DOT} ${DVIPS} ${LATEX}

FILES             =	efficient_interpreter.pdf
FILESDIR          =	${DOCDIR}

############################################################

PS2PDF              =	ps2pdf
DOT                 =	dot
DVIPS               =   dvips
LATEX               =	latex

MKC_REQUIRE_PROGS   =	${PS2PDF} ${DOT} ${DVIPS} ${LATEX}

do-all : efficient_interpreter.pdf

.PHONY : pdf dvi rtf
pdf : efficient_interpreter.pdf
ps  : efficient_interpreter.ps
dvi : efficient_interpreter.dvi

.SUFFIXES: .ps .eps .pdf .dvi .tex .dot

fsa_list = expression_tree
#fsa_list = fsa_example fsa_divided_by_2 fsa_divided_by_3 bin_operation \
#   fsa_openvpn fsa_number dfa_example dfa_example1 mindfa_example1 \
#   dfa_abstar fsa_sep_23_star_openvpn

efficient_interpreter.ps efficient_interpreter.pdf efficient_interpreter.dvi: ${fsa_list:=.eps}

.ps.pdf:
	${PROG.${PS2PDF}} "$<" "$@"

#.tex.pdf:
#	pdflatex "$<" && pdflatex "$<"

.dot.eps:
	${PROG.${DOT}} -Tps ${.IMPSRC} > ${.TARGET}

.dvi.ps:
	${PROG.${DVIPS}} $<

.tex.dvi:
	${PROG.${LATEX}} "${.IMPSRC}" && ${PROG.${LATEX}} "${.IMPSRC}"

.gz:
	gzip ${.IMPSRC}

GARBAGE=	*.dvi *.aux *.vrb *.toc *.snm *.log *.nav *.out *.eps *.ps
CLEANFILES+=	${GARBAGE} *.pdf *.ps

.PHONY: clean-garbage
clean-garbage:
	rm -f ${GARBAGE}

.include <mkc.mk>
