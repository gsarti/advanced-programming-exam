# C++ Part - BinarySearchTree Class

The folder includes our simple implementation of a templated binary search tree, complete with iterators.

## Folder structure

The `docs` folder includes the Doxyfile used to generate the documentation. When generated, the Doxygen documentation will be contained in the subfolders `html` and `latex`.

The `include` folder contains the implementation of the class BinarySearchTree, along with its nested subclasses and implemented methods. For clarity and readability's sake, the declaration of functions and member variables was put in `BinarySearchTree.h`, subclasses along with their defined methods were put in `BinarySearchTreeSubclasses.hxx` and the defined methods of BinarySearchTree were put inside `BinarySearchTreeMethods.hxx`.

The `test` folder includes tests made to ensure a correct behavior for the BinarySearchTree class, which are contained in the `BinarySearchTreeTests.cpp` file, alongside the code used to assess the performances of our tree, inside `BinarySearchTreeBenchmark.cpp`. In the subfolder `benchmark_results` performance plots are available alongside the data used to create them (to generate it, see the section below).

## Execution steps

The `Makefile` is used to compile automatically our project in its various steps.

The command `make test.o` generates a `test.o` executable that encompasses all the tests we performed on the BinarySearchTree class.

The command `make benchmark.o` generates a `benchmark.o` executable that, if run, produces the whole benchmark data in the form of file textes inside the benchmark_results folder. **Disclaimer:** The execution is serial and it may take a long time.

The command `make docs` generates the documentation inside the docs folder. Adding the `DEFINES=PTREE` argument after any of those commands makes tree printing in console the default.

To execute all the commands listed above, simply use `make`. To remove all the files created that way except for benchmarks data, which takes a long time to be recreated and should be deleted manually if needed, use `make clean`.