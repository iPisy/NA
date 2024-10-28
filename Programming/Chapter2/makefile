.PHONY: clean report run

oList=output/Function.o output/Interpolator.o output/Polynomial.o output/EquationSolver.o

run: output/B output/C output/D
	./output/B
	./output/C
	./output/D

report: src/report.tex
	pdflatex -output-directory=output src/report.tex

clean:
	rm -rf output

output/B: output/B.o $(oList) | output
	g++ -o output/B output/B.o $(oList)

output/C: output/C.o $(oList) | output
	g++ -o output/C output/C.o $(oList)

output/D: output/D.o $(oList) | output
	g++ -g -o output/D output/D.o $(oList)

output/B.o: src/B.cpp | output
	g++ -c src/B.cpp -o output/B.o

output/C.o: src/C.cpp | output
	g++ -c src/C.cpp -o output/C.o

output/D.o: src/D.cpp | output
	g++ -c src/D.cpp -o output/D.o

output/Function.o: lib/Function.cpp | output
	g++ -c lib/Function.cpp -o output/Function.o

output/Interpolator.o: lib/Interpolator.cpp | output
	g++ -c lib/Interpolator.cpp -o output/Interpolator.o

output/Polynomial.o: lib/Polynomial.cpp lib/Function.cpp lib/EquationSolver.cpp | output
	g++ -c lib/Polynomial.cpp -o output/Polynomial.o

output/EquationSolver.o: lib/EquationSolver.cpp lib/Function.cpp | output
	g++ -c lib/EquationSolver.cpp -o output/EquationSolver.o

output:
	mkdir -p output