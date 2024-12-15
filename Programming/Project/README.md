# Compilation instructions 
Open your terminal at the root directory of the project at first. 
- `make run` Run all binary files to test the project. <!-- It relies on `run.sh` in `src/`. Modify it if needed and change `make runTest` part in makefile.-->
- `make report` Generate report(at least a report with doxygen) of this project. All report will lie in `doc/` and will be opened by `makefile`, all figures will lie in `figure/`.
- `make clean` Clean all generated files.