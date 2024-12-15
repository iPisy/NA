all: build run report

build: dirs
	cd build && cmake ..
	cd build && make

buildInDebug: dirs
	cd build && cmake -DCMAKE_BUILD_TYPE=Debug ..
	cd build && make

run: build src/run.sh
	cp src/run.sh bin/
	chmod +x bin/run.sh
	clear
	cd bin && ./run.sh

runTest: build src/run.sh
	cp src/run.sh bin/test
	chmod +x bin/test/run.sh
	clear
	cd bin/test && ./run.sh

simpleTest:
	cd test && g++ -I/usr/include/eigen3 -o test class.cpp test.cpp && ./test

report: run doxygen LaTex
	xdg-open doc/html/index.html
	xdg-open doc/report.pdf
	xdg-open doc/design.pdf

doxygen: dirs Doxyfile
	doxygen Doxyfile

LaTex: dirs doc/report.tex
	@for file in bin/*.tex; do \
		mv "$$file" figure/; \
	done
	
	cp doc/A_convergence_rate.tex "doc/BezierSpline, m=10.tex" "doc/BezierSpline, m=40.tex" "doc/BezierSpline, m=160.tex" figure/

	@for file in figure/*.tex; do \
		pdf_file=$${file%.tex}.pdf; \
		if [ ! -f "$$pdf_file" ]; then \
			pdflatex -output-directory=figure "$$file"; \
		fi; \
	done

	cd figure \
	&& find . -maxdepth 1 -type f ! -name "*.pdf" -exec rm -f {} \;

	cd doc \
	&& pdflatex design.tex \
	&& bibtex design.aux \
	&& pdflatex design.tex \
	&& pdflatex design.tex \
	&& pdflatex report.tex \
	&& bibtex report.aux \
	&& pdflatex report.tex \
	&& pdflatex report.tex \
	&& find . -maxdepth 1 -type f ! -name "*.pdf" ! -name "*.tex" ! -name "references.bib" -exec rm -f {} \;

dirs:
	mkdir -p build
	mkdir -p figure

clean:
	rm -rf build
	rm -rf bin
	rm -rf figure

.PHONY: all build buildInDebug run runTest simpleTest report doxygen LaTex dirs clean