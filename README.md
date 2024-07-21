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
   ```

2. **Build the Project:**

  ```bash
  make

3. **Run the converter:**

  ```bash
  ./wkt2geojson input.wkt output.geojson
  ```

Replace input.wkt with your WKT file and output.geojson with the desired output GEOJSON file.

Note: As the project is still in development, the functionality may be incomplete or subject to changes.

### CRIACAO DA IMAGEM

A rotina abaixo descreve o processo para as intalacoes dos softwares e a criacao da imagem.

```bash

cd /workspace
git clone [URL] 
cd /workspace/wkt2geojson

# Dirs
sudo ./scripts/host/create_dirs.pl

# Criacao da imagem
docker build -t wkt2geojson:latest .

# Sobe o container
make run
make post_install

# Log: logrotate
sudo cp ./etc/logrotate.d/wkt2geojson /etc/logrotate.d/
sudo chmod 0644 /etc/logrotate.d/wkt2geojson
sudo logrotate -d /etc/logrotate.d/wkt2geojson
sudo logrotate /etc/logrotate.d/wkt2geojson

# Grava a imagem
docker commit --message='Set Timezone' `docker ps -aqf "name=wkt2geojson"` wkt2geojson:latest

```

## SOURCE CODE ORGANIZATION

- features.c: entry point
- features.l: scanner
- features.y: parser
- lex.yy.c: FSA generated from scanner
- features.tab.c: LR Parser generated from the parser
- features.tab.h: LR Parser header
- Makefile: targets
