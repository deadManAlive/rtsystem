# Self-Service Train Ticketing System
A console C program that simulates train ticketing system. Language is Indonesian.
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
	use clang (or gcc): `clang -o rtsystem.exe rtsystem.c order.c simulation.c`
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