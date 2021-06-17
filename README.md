# Self-Service Train Ticketing System
A console C program that simulates train ticketing system. Divided into two main parts: ordering mechanics and simulation mechanics. Ordering mechanics handle implementation of order as a struct to write, read, and process further. Simulation mechanics provide randomization to seating and schedule. Program language is Indonesian.

>This source code is made by DK02_g07 as final programming assignment in Even Semester 2020/2021 for course Basic Computer + Lab. (ENEE603014) in Undergraduate of Electrical Engineering study program, Department of Electrical Engineering, Faculty of Engineering, Universitas Indonesia.

## How To Build
Download repository as ZIP or clone with Git.
* using cmake
	Open command prompt/powershell, navigate to project folder. Then use commands:
	```
		cmake -E make_directory build
		cmake -E chdir build cmake ..
		cmake --build build
	```
	The executable (or .sln file) would be available in the `build` folder.
* directly using compiler
	use clang (or gcc): `clang -o rtsystem.exe rtsystem.c order.c simulation.c generics.c`
* Using IDE (Dev-C++)
	1. Menu `File` > `New` > `Project...`
	2. Set as `Console Application`
	3. Set project name.
	4. Set project to `C Project`
	5. `Ok` and save `.dev` file somewhere.
	6. Remove `main.c` in this new project.
	7. Menu `Project` > `Add to Project`
	8. Select all the source codes (ends with `.h` and `.c`)
	9. Compile program.

Or just download the precompiled binary on https://github.com/deadManAlive/rtsystem/releases/latest