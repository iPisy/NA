# Spline Interpolation and Curve Fitting in C++

A Numerical Analysis course project at Zhejiang University, independently implemented and documented by **Wang Hao**. The project turns spline interpolation methods into a reusable C++ library, then uses separate experiment programs to study accuracy, boundary conditions, and curve parameterisation.

**Start here:** [Design and architecture](doc/design.pdf) · [Experiments and results](doc/report.pdf) · [Library source](lib/) · [Experiment programs](src/)

## Features

- **PP-form and B-form splines:** general degree-parameterised implementations with periodic boundary conditions, plus specialised linear and cubic variants.
- **Cubic boundary conditions:** complete (clamped), natural, prescribed endpoint second derivatives, not-a-knot, and periodic conditions.
- **Planar curve fitting:** cubic parametric splines with uniform or cumulative-chord-length parameterisation.
- **Spherical curve fitting:** projection to the plane, fitting with the planar component, and mapping back onto the sphere.
- **Reusable components:** functions, polynomials, piecewise polynomials, curves, and boundary-condition types.
- **Documentation and visualisation:** Doxygen interface documentation and LaTeX/PGFPlots output for numerical experiments.

The general spline classes accept a degree parameter; this does not guarantee that every choice of degree, knots, and boundary conditions yields a well-posed problem. The implementation includes a warning for higher even-degree cases.

## Design decisions

### Shared construction interface

The abstract `Spline` class organises a common process: assemble a linear system, apply boundary conditions, solve the system, and construct a piecewise polynomial. Derived classes implement the steps that depend on the spline representation. Eigen supplies the linear algebra operations used to solve the systems.

Reusable numerical components live in `lib/`, separate from the assignment-specific experiments in `src/`.

### Specialised cubic formulation

`PFS3` uses a formulation from the course material that reduces the number of unknowns from `4(N - 1)` to `N`, where `N` is the number of knots. The planar curve fitter uses this implementation and reuses the coefficient matrix between compatible coordinate-wise fits. The current code reuses the matrix, not its factorisation.

### Verification against mathematical expectations

Experiments examine both numerical error and agreement between alternative representations. Plots provide a visual comparison; sampled error calculations provide a separate quantitative check.

## Selected experiments

These results are documented in the original [project report](doc/report.pdf), rather than newly rerun benchmarks.

| Experiment | What was examined |
| --- | --- |
| Convergence (`src/A.cpp`) | Interpolation error under knot refinement; approximately fourth-order convergence is observed in this example. |
| Representation consistency (`src/C.cpp`) | PP-form and B-form cubic splines compared at 100,000 sample points under identical conditions; the reported maximum difference was close to machine precision. |
| Pointwise errors (`src/D.cpp`) | Errors for interpolation constructions discussed in the course material. |
| Curve fitting (`src/E.cpp`) | Uniform and cumulative-chord-length parameterisations, with planar and spherical examples. |
| Divided differences (`src/F.cpp`) | Tables of piecewise-polynomial divided differences. |
| Additional cases (`src/moreFunctions.cpp`) | Higher-degree splines, additional boundary conditions, and a numerical illustration of the B-spline partition-of-unity property. |

These checks describe the tested cases; they are not a general proof of numerical stability or a performance guarantee.

## Project layout

```text
Project/
├── lib/                 Reusable C++ classes and implementations
│   └── test/            Component test and demonstration programs
├── src/                 Assignment experiments and batch-run script
├── doc/                 Design/report PDFs, LaTeX sources, and references
├── figure/              Figures used in the reports
├── CMakeLists.txt       Library and executable build definitions
├── makefile             Build, run, and documentation targets
└── Doxyfile             API documentation configuration
```

Builds generate `build/` and `bin/`; component executables are placed in `bin/test/`.

## Environment and dependencies

The original workflow targets **Linux**, with **C++**, **Git**, **CMake**, **Make**, **Eigen**, **Doxygen**, and **LaTeX**.

To build and run:

- A C++ compiler supporting the features used in the source, including C++11 features.
- CMake 3.10 or newer, GNU Make, and a POSIX shell.
- Eigen headers. The current build expects `/usr/include/eigen3`; adjust `CMakeLists.txt` for other installations.

To regenerate documentation, also install Doxygen, Graphviz (`dot`), and a LaTeX distribution with `pdflatex`, BibTeX, PGFPlots, `authblk`, `biblatex`, and `subcaption`, together with their dependencies. The convenience report target uses `xdg-open` to open the outputs.

The supplied build configuration does not explicitly set a C++ language standard. Use a compiler with a suitable default or configure the standard when generating the build. The existing PDFs can be read without installing documentation tools.

## Build and run

Clone the repository and enter this project directory:

```bash
git clone https://github.com/iPisy/NA.git
cd NA/Programming/Project
```

Build the library, experiments, and component programs:

```bash
make build
```

Run all assignment experiments:

```bash
make run
```

This builds first, then runs the executables in `bin/`. Programs print results and generate `.tex` plot files in their working directory. To run only the representation-consistency experiment after building:

```bash
cd bin
./C
```

From the project root, run component programs with:

```bash
make build
make runTest
```

`make runTest` does not build its executables itself. Component programs include demonstrations and diagnostic output; they are not a comprehensive assertion-based test suite. The batch-run script is a convenience runner, not a CI pass/fail check.

## Generate documentation

From the project root, generate the HTML API reference:

```bash
make doxygen
```

Open `doc/html/index.html` to browse it. To run experiments and regenerate the API reference and PDF reports:

```bash
make report
```

This also attempts to open outputs using `xdg-open`. For a headless environment, run the stages separately:

```bash
make run
make doxygen
make LaTex
```

The LaTeX target moves generated plot sources into `figure/`, compiles figures whose PDFs do not already exist, and removes intermediate files. To refresh an existing figure after changing an experiment, remove its corresponding generated PDF before rerunning the workflow. Some results in the report sources are manually recorded; rebuilding does not automatically refresh every table or numerical statement.

`make clean` removes `build/`, `bin/`, the entire `figure/` directory, and generated HTML documentation. Preserve any figures you want to keep before using it. Plain `make` invokes the full build/run/report workflow; use `make build` when only compilation is needed.

## Authorship and references

All project implementation and documentation were completed independently by Wang Hao. Several utility classes were reused from my earlier programming assignments, as listed in the design report. Spline formulations and mathematical results follow the course material cited in [the bibliography](doc/references.bib); the numerical methods themselves are not claimed as original research. Eigen is an external linear algebra dependency.
