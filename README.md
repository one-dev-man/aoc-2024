<h1 style="display: flex; align-items: start;">
    <a href="https://adventofcode.com/">
        <img src="assets/aoc-text-icon.svg" width="35%" alt="Advent Of C++">
    </a>
</h1>

Personal repository of my work on the <span class="aoc-colored">[`Advent Of Code`](https://adventofcode.com/)</span> 2024 in `C++`.

### How to use

First, you need to build the project with `make` by launching `make all`.
You can clean generated objects with `make clean`.

Then you'll need to add the input of days you want to solve in a new file `resources/days/<day number>/input.txt`.

Finally, just run the program: `build/aoc -d<day number>`.
After the puzzle is solved, it will print you the answer.