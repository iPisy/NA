#include<iostream>
#include<limits>

using namespace std;

int main(){
    cout<<numeric_limits<double>::lowest()<<endl<<numeric_limits<double>::min();
}

TEX_FILES:=$(wildcard output/*.tex)
PDF_FILES:=$(TEX_FILES:.tex=.pdf)

run: output
	cd output && ./F
	$(eval TEX_FILES := $(wildcard output/*.tex))
	$(eval PDF_FILES := $(TEX_FILES:.tex=.pdf))	

output/%.pdf: output/%.tex
	pdflatex -output-directory=output $<

report: output run $(PDF_FILES) src/report.tex
	cp src/report.tex output/report.tex
	cp src/references.bib output/references.bib
	cd src && pdflatex report.tex

output:
	mkdir -p output

.PHONY: run report output