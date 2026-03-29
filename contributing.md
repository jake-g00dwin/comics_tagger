# Contributing

Okay so you've read the `README.md` file and decided that you want to work on
maintain or do some hacking on the project.

Here's the low down on what you'll want to do before making any kinds of pull
requests.

## Project Directory Layout


### Modules

Okay so the project is split into "modules" which are all held in the `src/` 
directory.

This allows us to compile the project in chunks and makes the build process a 
lot faster.

We also benefit from begin able to better scope information that the consumer
of a module doesn't need to have access to.

For example the `cvectors.h` module provides a `typedef` for a structure called
`cvec_t` but does not define it publicly.

This helps to prevent simple bugs/errors such as modifying the vector's 
capacity or size fields possibly resulting in dangling pointers, and segmentation
faults.

Each of these modules contains at minimum:
- module_name.h / module_name.hpp
- module_name.c / module_name.cpp
- CMakeLists.txt

The next part that makes the modules useful is their test suites; these are
located in the `./tests/module_name/` sub-directories like so:

- CMakeLists.txt:: cmake unit tests configuration.
- test_module_name.cpp:: Source for the unit tests themselves.
- mocks:: Directory to hold all mocks used exclusively for this module.
- fakes:: Directory to hold all fakes used exclusively for this module.
- stubs:: Directory to hold all stubs used exclusively for this module.

### External Libraries

For external libraries they should be installed or linked from the system 
where possible by using the CMAKE pkg_find feature.

The secondary option is using the git sub modules feature.


## Suggested Development cycle

For working on the project I really suggest you sit down and read through the
`otto.sh` shell script and get to know how it works.

You can use it to automatically add new modules, delete old modules and run the
unit tests for the project.

It greatly simplifies the development cycle so that you don't have to dig into
the cmake build configuration, makefile scripts or module linkage to a large
degree.

It also runs system tools to generate tag files for editors, automatically
apply code formatting standards and more.

### TDD red/green
1. Write Failing tests for current module.
2. Run tests using `otto.sh` and menu option 1.
4. Confirm test runs and is able to fail.
3. Git Commit tests
5. Write code to pass test(s).
3. Git Commit code.
6. Repeat.

### Pull Requests

1. Fork the repository.
2. make needed changes.
3. Open pull-request.

