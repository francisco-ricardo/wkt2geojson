# WKT2GeoJSON

**WKT2GeoJSON** is a lightweight, command-line tool designed to convert Well-Known Text (WKT) data into GeoJSON format. This project includes a WKT parser written in C, developed using Flex and Bison. The tool is containerized for ease of use, allowing users to execute it within a Docker environment without manually handling dependencies.

## Key Features

- **Efficient Parsing**: Translates WKT geometry data into valid GeoJSON format.
- **Lightweight**: Minimal dependencies, optimized for performance.
- **Dockerized**: Can be run easily in a Docker container, simplifying environment setup.
- **Cross-Platform**: Works on Linux, macOS, and Windows with bash or batch script support.
- **Extensible**: Can be extended to support additional spatial data formats in the future.

## What are WKT and GeoJSON?

- **Well-Known Text (WKT)** is a text markup language used to represent vector geometry objects, as defined by the Open Geospatial Consortium (OGC) ([Wikipedia, 2024](https://en.wikipedia.org/wiki/Well-known_text)).
- **GeoJSON** is a standard format, based on JSON, for encoding a variety of geographic data structures, including simple geographical features and their non-spatial attributes ([Wikipedia, 2024](https://en.wikipedia.org/wiki/GeoJSON)).

## Applications

The methodology used in this project has been applied in several contexts, including:

- **Master's Dissertation**: *Overcoming Synchronization Challenges in Machining Digital Twins: Transpiling Legacy NC Dialects to Enhance Interoperability* by Francisco Ricardo Taborda Aguiar. [Available here](https://doi.org/10.13140/RG.2.2.27115.76322).
- **COBEM 2021 Article**: *Transpilation from NC Files to Canonical Machining Functions*. [Available here](https://www.researchgate.net/publication/357079212_TRANSPILATION_FROM_NC_FILES_TO_CANONICAL_MACHINING_FUNCTIONS).

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

```bash
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

Start the development container with:

```bash
docker-compose -f compose-dev.yaml up --build --detach
```

Connect to the container with:

```bash
docker exec -it wkt2geojson bash
```

Enter to the app directory:

```bash
cd /app
```

#### Building the Project

Use the following command to build the project:

```bash
make build
```

This will clean old build files, compile the lexer and parser using Flex and Bison, and output the executable binary wkt2geojson.

#### Running Tests

A basic test is included, which compiles a test program and runs it under Valgrind to check for memory leaks:

```bash
make test
```

This will run the tests on the example WKT files under the samples directory.

#### Usage examples:

```bash
./wkt2geojson -i input.wkt -o output.geojson
./wkt2geojson < input.wkt > output.geojson
```
This command reads WKT data from `input.wkt` and writes the corresponding GeoJSON to `output.geojson`.
If any of the file options are omitted, the program defaults to using `stdin` and `stdout`.

The getopt function is used to parse the command-line options. The available options are:

- -i: Specifies the input file path.
- -o: Specifies the output file path.
- -h: Prints the help message and exits.

The program flow is as follows:

1. Command-line arguments are processed using `getopt`.
2. The input file is opened (or stdin is used if no file is provided).
3. The output file is opened (or stdout is used if no file is provided).
4. The parser is invoked to transpile the WKT data into GeoJSON.
5. After processing, the input and output files are closed (if they were opened).

#### Error handling

- If the input file cannot be opened, an error message is printed, and the program exits with a status of 1.
- If the output file cannot be opened, an error message is printed, and the program exits with a status of 1.

The output GeoJSON file is valid but may not be formatted for readability. To format the output in a more readable way, it can be piped through a JSON beautifier tool, such as `jq` or `json_pp`. For example:

```bash
./wkt2geojson < input.wkt | jq . > output.geojson
```
