doc:
	pdflatex Answer.tex
	xdg-open Answer.pdf
	make clean

clean:
	find . -type f ! -name "*.pdf" ! -name "*.tex" ! -name "makefile" -exec rm -f {} \;

.PHONY: clean doc