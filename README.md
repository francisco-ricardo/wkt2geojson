# WKT to GEOJSON Converter

Welcome to the WKT to GEOJSON Converter repository!

This project aims to convert Well-Known Text (WKT) files into GEOJSON format using lexical and syntactical analysis techniques. The implementation leverages the C programming language along with Flex and Bison for efficient parsing and translation. **Please note that this project is still in development and not yet complete.**

## Project Overview

### What is WKT?

Well-Known Text (WKT) is a text markup language used for representing geometric objects. It is commonly used in geographic information systems (GIS) and spatial databases.

### What is GEOJSON?

GEOJSON is a format for encoding a variety of geographic data structures using JavaScript Object Notation (JSON). It is widely used for web mapping and spatial data applications.

### Features (Planned)

- **Lexical Analysis**: To use Flex for scanning and tokenizing WKT input.
- **Syntactical Analysis**: To employ Bison for parsing and constructing GEOJSON output.
- **C Implementation**: Written in C for performance and efficiency.
- **Conversion Accuracy**: Aiming to convert WKT geometries accurately into GEOJSON format.

## Current Status

**This project is currently under development and is not yet complete.** We are actively working on implementing the conversion features and refining the parsing process. Updates and improvements are ongoing.

## Research Context

This converter project was utilized during the research for the master's thesis of Francisco Ricardo Taborda Aguiar at the Federal University of Paraná. The thesis is titled **"Overcoming Synchronization Challenges in Machining Digital Twins: Transpiling Legacy NC Dialects to Enhance Interoperability."** The project played a role in addressing synchronization and interoperability issues by providing a tool for converting spatial data formats.

## Getting Started

### Prerequisites

- C compiler (e.g., GCC)
- Flex
- Bison

### Installation

1. **Clone the Repository:**

   ```bash

   git clone https://github.com/yourusername/wkt2geojson.git
   cd wkt2geojson

   docker-compose -f compose-prod.yaml up --build

   ```

2. **Build the Project:**

  ```bash
  make
  ```

3. **Run the converter:**

  ```bash
  ./wkt2geojson input.wkt output.geojson
  ```

Replace input.wkt with your WKT file and output.geojson with the desired output GEOJSON file.

Note: As the project is still in development, the functionality may be incomplete or subject to changes.

## Usage

Once the project is complete, you will be able to use the wkt2geojson executable to convert WKT files to GEOJSON. The command-line interface will accept an input WKT file and produce a GEOJSON file.

Example:

```bash
./wkt2geojson example.wkt example.geojson
```

## Project Structure

- features.c: entry point
- features.l: scanner
- features.y: parser
- lex.yy.c: FSA generated from scanner
- features.tab.c: LR Parser generated from the parser
- features.tab.h: LR Parser header
- Makefile: targets

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## TODO

{
"type": "FeatureCollection",
"features": []
}

- detalhar sobre wkt
- detalhar sobre geojson
- detalhar sobre flex, bison e algoritmos lr
- acrescentar referencias
- considerar dissertacao
- considerar arquivo cobem
- instrucoes para clonar o repo
- diferenca entre dev e prod
- instrucoes para build a imagem
- instrucoes para subir o container (se desejado)
- instrucoes para executar a partir do container
- instrucoes para executar a partir do host com o uso do script
  - nesse caso nao necessita do container, apenas da imagem
- instrucoes para
- considerar pipeline com jq
- considerar logrotate
- enfatizar que e multiplataorma (linux, windows, mac)
- enfatizar que necessita somente do docker
- deixar claro para uque o usuario clone e execute
- deve ter todas as secoes recomendadas para um bom portfolio
- considerar que sera avaliado por recrutadores
