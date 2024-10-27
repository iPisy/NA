.PHONY: clean report run

oList=output/Function.o output/Interpolator.o output/Polynomial.o

run: output/B output/C
	./output/B
	./output/C

report: src/report.tex
	pdflatex -output-directory=output src/report.tex

clean:
	rm -rf output

output/B: output/B.o $(oList) | output
	g++ -o output/B output/B.o $(oList)

output/C: output/C.o $(oList) | output
	g++ -o output/C output/C.o $(oList)

output/B.o: src/B.cpp | output
	g++ -c src/B.cpp -o output/B.o

output/C.o: src/C.cpp | output
	g++ -c src/C.cpp -o output/C.o

output/Function.o: lib/Function.cpp | output
	g++ -c lib/Function.cpp -o output/Function.o

output/Interpolator.o: lib/Interpolator.cpp | output
	g++ -c lib/Interpolator.cpp -o output/Interpolator.o

output/Polynomial.o: lib/Polynomial.cpp | output
	g++ -c lib/Polynomial.cpp -o output/Polynomial.o

output:
	mkdir -p output