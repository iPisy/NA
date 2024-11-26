doc:
	pdflatex IX\(3.1\).tex
	pdflatex IX\(3.2\).tex
	pdflatex Answer.tex
	bibtex Answer.aux
	pdflatex Answer.tex
	pdflatex Answer.tex
	xdg-open Answer.pdf
	make clean

clean:
	find . -type f ! -name "Answer.pdf" ! -name "*.tex" ! -name "makefile" ! -name "references.bib" -exec rm -f {} \;

.PHONY:clean doc