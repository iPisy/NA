.PHONY: clean report run

oList=output/Function.o output/Interpolator_NewtonFormula.o output/Polynomial.o output/EquationSolver.o output/Interpolator_HermiteProblem_NewtonFormula.o output/Curve.o output/CubicBezierSpline.o output/CubicBezierCurve.o output/BernsteinPolynomial.o

run: output/B output/C output/D output/E output/F
	@echo "\033[0;34m----------------------------------------\033[0m"
	./output/B
	@echo "\033[0;34m----------------------------------------\033[0m"
	./output/C
	@echo "\033[0;34m----------------------------------------\033[0m"
	./output/D
	@echo "\033[0;34m----------------------------------------\033[0m"
	./output/E
	@echo "\033[0;34m----------------------------------------\033[0m"
	./output/F
	@echo "\033[0;34m----------------------------------------\033[0m"
	@cd output && rm -f *.o

report: output/report.pdf output/html/index.html
	xdg-open output/report.pdf
	xdg-open output/html/index.html

output/report.pdf: src/report.tex src/references.bib | output
	cd src && xelatex report.tex
	cd src && bibtex report
	cd src && xelatex report.tex
	cd src && xelatex report.tex
	mv src/report.pdf output/report.pdf
	cd src && rm -f *.aux *.bbl *.bcf *.blg *.log *.out *.run.xml *.toc *.synctex.gz report-blx.bib

clean:
	rm -rf output

output/B: output/B.o $(oList) | output
	g++ -o output/B output/B.o $(oList)

output/C: output/C.o $(oList) | output
	g++ -o output/C output/C.o $(oList)

output/D: output/D.o $(oList) | output
	g++ -g -o output/D output/D.o $(oList)

output/E: output/E.o $(oList) | output
	g++ -g -o output/E output/E.o $(oList)

output/B.o: src/B.cpp | output
	g++ -c src/B.cpp -o output/B.o

output/C.o: src/C.cpp | output
	g++ -c src/C.cpp -o output/C.o

output/D.o: src/D.cpp | output
	g++ -c src/D.cpp -o output/D.o

output/E.o: src/E.cpp | output
	g++ -c src/E.cpp -o output/E.o	

output/F.o: src/F.cpp | output
	g++ -c src/F.cpp -o output/F.o		

output/Function.o: lib/Function.cpp | output
	g++ -c lib/Function.cpp -o output/Function.o

output/Interpolator_NewtonFormula.o: lib/Interpolator_NewtonFormula.cpp | output
	g++ -c lib/Interpolator_NewtonFormula.cpp -o output/Interpolator_NewtonFormula.o

output/Polynomial.o: lib/Polynomial.cpp lib/Function.cpp lib/EquationSolver.cpp | output
	g++ -c lib/Polynomial.cpp -o output/Polynomial.o

output/EquationSolver.o: lib/EquationSolver.cpp lib/Function.cpp | output
	g++ -c lib/EquationSolver.cpp -o output/EquationSolver.o

output/Interpolator_HermiteProblem_NewtonFormula.o: lib/Interpolator_HermiteProblem_NewtonFormula.cpp | output
	g++ -c lib/Interpolator_HermiteProblem_NewtonFormula.cpp -o output/Interpolator_HermiteProblem_NewtonFormula.o

output/Curve.o: lib/Curve.cpp | output
	g++ -c lib/Curve.cpp lib/Function.cpp -o output/Curve.o

output/CubicBezierSpline.o: lib/CubicBezierSpline.cpp | output
	g++ -c lib/CubicBezierSpline.cpp -o output/CubicBezierSpline.o

output/CubicBezierCurve.o: lib/CubicBezierCurve.cpp | output
	g++ -c lib/CubicBezierCurve.cpp -o output/CubicBezierCurve.o

output/BernsteinPolynomial.o: lib/BernsteinPolynomial.cpp | output
	g++ -c lib/BernsteinPolynomial.cpp -o output/BernsteinPolynomial.o

output/html/index.html | output: Doxyfile
	doxygen Doxyfile

output:
	mkdir -p output