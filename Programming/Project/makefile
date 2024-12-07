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
	cd test && g++ -o test class.cpp test.cpp && ./test

report: run doxygen LaTex
	xdg-open report/html/index.html
	xdg-open report/report.pdf


doxygen: dirs Doxyfile
	doxygen Doxyfile

LaTex: dirs src/report.tex
	for file in bin/*.tex; do \
		mv $${file} report/; \
	done

	@for file in report/*.tex; do \
		pdf_file=$${file%.tex}.pdf; \
		if [ ! -f "$$pdf_file" ]; then \
			pdflatex -output-directory=report "$$file"; \
		fi; \
	done

	cp src/report.tex src/references.bib report/
	cd report && pdflatex report.tex \
	&& bibtex report.aux \
	&& pdflatex report.tex \
	&& pdflatex report.tex \
	&& find . -maxdepth 1 -type f ! -name "*.pdf" -exec rm -f {} \;


dirs:
	mkdir -p build
	mkdir -p report

clean:
	rm -rf build
	rm -rf bin
	rm -rf report

.PHONY: all build buildInDebug run runTest simpleTest report doxygen LaTex dirs clean