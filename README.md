# WKT2GeoJSON

**WKT2GeoJSON** is a lightweight, command-line tool designed to convert Well-Known Text (WKT) data into GeoJSON format. This project includes a WKT parser written in C, developed using Flex and Bison. The tool is containerized for ease of use, allowing users to execute it within a Docker environment without manually handling dependencies.

## Key Features

- **Efficient Parsing**: Translates WKT geometry data into valid GeoJSON format.
- **Lightweight**: Minimal dependencies, optimized for performance.
- **Dockerized**: Can be run easily in a Docker container, simplifying environment setup.
- **Cross-Platform**: Works on Linux, macOS, and Windows with bash or batch script support.
- **Extensible**: Can be extended to support additional spatial data formats in the future.

## Key Concepts and Technologies

- **Well-Known Text (WKT)** is a text markup language used to represent vector geometry objects, as defined by the Open Geospatial Consortium (OGC) ([Wikipedia, 2024](https://en.wikipedia.org/wiki/Well-known_text)).

- **GeoJSON** is a standard format, based on JSON, for encoding a variety of geographic data structures, including simple geographical features and their non-spatial attributes ([Wikipedia, 2024](https://en.wikipedia.org/wiki/GeoJSON)).

- **Lexical Analysis** is the process of dividing input text into lexical units called tokens. It is the first phase of a compiler or interpreter where the input is transformed into a sequence of tokens representing basic elements of the code. In the WKT2GeoJSON project, the lexical analyzer is generated using Flex, which identifies and classifies tokens from the WKT input.
  - **Reference:** Aho, A. V., Sethi, R., & Ullman, J. D. (2006). *Compilers: Principles, Techniques, and Tools* (2nd ed.). Addison-Wesley.

- **Syntax Analysis** involves analyzing the grammatical structure of the token input, verifying that the token sequence follows the defined grammar. A parser is used to construct a syntax tree that represents the hierarchical structure of the code. In WKT2GeoJSON, syntax analysis is performed using Bison, which builds a parse tree from the tokens produced by the lexical analysis.
  - **Reference:** Grune, D., & Jacobs, C. J. (2007). *Parsing Techniques: A Practical Guide*. Springer.

- **LR Algorithms** are a class of parsing algorithms that use an efficient technique for syntax analysis of context-free grammars. The LR algorithm is used to handle more complex grammars and is capable of parsing most syntactical structures used in programming languages. In WKT2GeoJSON, Bison generates the parser using the LR approach to process the WKT grammar.
  - **Reference:** DeRemer, F., & Pennello, J. (1982). *Efficiently Computable Parsing Tables*. ACM SIGPLAN Notices.

## Applications

The methodology utilized in this project has also been employed in the following research studies:

- **COBEM 2021 Article**: *Transpilation from NC Files to Canonical Machining Functions*
by Francisco Ricardo Taborda Aguiar. [Available here](https://www.researchgate.net/publication/357079212_TRANSPILATION_FROM_NC_FILES_TO_CANONICAL_MACHINING_FUNCTIONS).

- **Master's Dissertation**: *Interpretation of RS274-D Dialects and Temporal Data Extraction in CNC Machines*
by Francisco Ricardo Taborda Aguiar. [Available here](https://doi.org/10.13140/RG.2.2.27115.76322).

## Table of Contents

- [Installation](#installation)
- [Usage](#usage)
- [Development](#development)
- [File Structure](#file-structure)
- [Contributing](#contributing)
- [License](#license)

## Installation

### Prerequisites

- **Docker**: Ensure Docker is installed on your system. You can download Docker [here](https://www.docker.com/get-started).

### Clone the Repository

```bash
git clone https://github.com/yourusername/wkt2geojson.git
cd wkt2geojson
```

### Build the Docker Image

You can build the development or production image using the respective Docker Compose files.

#### Development Build

```bash
docker-compose -f compose-dev.yaml up --build --detach
```

#### Production Build

```bash
docker-compose -f compose-prod.yaml up --build --detach
```

### Usage

The tool provides shell and batch scripts to run wkt2geojson within a Docker container.
These scripts allow for the easy processing of WKT files by specifying the file path as an argument.

#### Running the Tool on Linux or macOS

You can run the tool using the run-wkt2geojson.sh script:

```bash
./scripts/run-wkt2geojson.sh /path/to/your/input.wkt
```

To see usage instructions, you can run:

```bash
./scripts/run-wkt2geojson.sh -h
```

#### Running the Tool on Windows

On Windows, you can use the run-wkt2geojson.bat script:

```bat
run-wkt2geojson.bat C:\path\to\your\input.wkt
```

To see usage instructions, run:

```bash
run-wkt2geojson.bat -h
```

### Development

If you're contributing or making changes to the code, the project uses a Makefile for building and testing
the C parser.

#### Docker Development Environment

The Dockerfile.dev is designed for development. It installs all necessary dependencies, including Valgrind, Flex, and Bison, ensuring you have a complete development environment in the container.

- Start the development container with:

```bash
docker-compose -f compose-dev.yaml up --build --detach
```

- Connect to the container with:

```bash
docker exec -it wkt2geojson bash
```

*This command opens a terminal session inside the Docker container named `wkt2geojson`.*

- Navigate to the source files directory:

```bash
cd /app/application/src
```

*This command changes the current directory to /app/application/src inside the container, where the source files are located.*

#### Building the Project

Use the following command to build the project:

```bash
make build
```

*This will clean old build files, compile the lexer and parser using Flex and Bison, and output the executable binary wkt2geojson.*

#### Running Tests

A basic test is included, which compiles a test program and runs it under Valgrind to check for memory leaks:

```bash
make test
```

*This will run the tests on the example WKT files under the samples directory.*

#### Usage examples:

```bash
./wkt2geojson -i input.wkt -o output.geojson
./wkt2geojson < input.wkt > output.geojson
```

These commands read WKT data from `input.wkt` and write the corresponding GeoJSON to `output.geojson`.
If the input file cannot be opened, an error message is printed, and the program exits with a status of 1.
If the output file cannot be opened, an error message is printed, and the program exits with a status of 1.
If any of the file options are omitted, the program defaults to using `stdin` and `stdout`.

The `getopt` function is used to parse the command-line options. The available options are:

- -i: Specifies the input file path.
- -o: Specifies the output file path.
- -h: Prints the help message and exits.

The output GeoJSON file is valid but may not be formatted for readability. To format the output in a more readable way, it can be piped through a JSON beautifier tool, such as `jq` or `json_pp`. For example:

```bash
./wkt2geojson < input.wkt | jq . > output.geojson
```

## File Structure

```bash
wkt2geojson/
│
├── application/
│   ├── bin/                     # Binary output of the wkt2geojson transpiler
│   ├── samples/                 # Sample WKT files
│   ├── src/                     # Source files for the project
│   │   ├── parser.y             # Bison grammar file for WKT parsing
│   │   ├── scanner.l            # Flex lexer file for tokenizing WKT
│   │   ├── wkt2geojson.c        # Main C source file for the transpiler
│   │   ├── writer.c             # Helper functions to write GeoJSON output
│   │   ├── Makefile             # Build system for the C project
│
├── scripts/                     # Helper scripts to run wkt2geojson in Docker
│   ├── run-wkt2geojson.sh       # Bash script for running the tool
│   └── run-wkt2geojson.bat      # Batch script for Windows users
│
├── Dockerfile.dev                # Dockerfile for development environment
├── Dockerfile.prod               # Dockerfile for production environment
├── compose-dev.yaml              # Docker Compose file for development
├── compose-prod.yaml             # Docker Compose file for production
└── README.md                     # This README file
```

## Contributing

We welcome contributions from the community! Feel free to fork this repository, clone it, and submit pull requests with your improvements or ideas. This project is open-source, and you are free to use, modify, and redistribute it under the terms of the license. To ensure smooth collaboration, please keep the following in mind:

- **Follow Code Style Guidelines:** Adhere to the project's coding standards and style guidelines.
- **Run Tests:** Make sure all tests pass to ensure that nothing is broken by your changes.
- **Document Changes:** Clearly document any new features or changes made.

## LICENSE

This project is released under the MIT License, meaning it is open-source and freely available for anyone to use, modify, and distribute. You are welcome to clone the repository, use it in your projects, and contribute back with improvements. See the LICENSE file for details.
