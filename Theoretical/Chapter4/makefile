TEX_FILES := $(filter-out Answer.tex, $(wildcard *.tex))
IMAGE_FILES := $(TEX_FILES:.tex=.pdf)

doc: images
	pdflatex Answer.tex
	bibtex Answer.aux
	pdflatex Answer.tex
	pdflatex Answer.tex
	xdg-open Answer.pdf
	make clean

images: $(IMAGE_FILES)

%.pdf: %.tex
	pdflatex "$<"

clean:
	find . -type f ! -name "Answer.pdf" ! -name "*.tex" ! -name "makefile" ! -name "references.bib" -exec rm -f {} \;

.PHONY:clean doc images