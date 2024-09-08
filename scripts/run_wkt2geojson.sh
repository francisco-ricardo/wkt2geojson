#!/bin/bash

# "I have been crucified with Christ and I no longer live,
# but Christ lives in me. The life I now live in the body,
# I live by faith in the Son of God, who loved me and
# gave himself for me." Galatians 2:20 (NIV)


# Function to print usage information
print_help() {
    echo "Usage: $0 <full_path_to_wkt_file>"
    echo
    echo "This script facilitates the execution of the 'wkt2geojson' program"
    echo "inside a Docker container. It allows users to specify the absolute or"
    echo "relative path to an input file, which is then processed by the"
    echo "'wkt2geojson' command. The script dynamically determines the project"
    echo "directory and mounts both the project directory and the directory"
    echo "containing the input file into the Docker container. It ensures that"
    echo "the input file is accessible within the container and executes the"
    echo "'wkt2geojson' program with the '-i' option for the input file."
    echo
    echo "Options:"
    echo "  -h    Show this help message and exit"
    echo
    echo "Arguments:"
    echo "  full_path_to_wkt_file    Absolute or relative path to the input file"
    echo
    echo "Requirements:"
    echo "  Docker"
    echo "  'wkt2geojson' Docker image"
    echo
    echo "Example:"
    echo "  ./run-wkt2geojson.sh /absolute/path/to/file"
}


# Check for help option
if [ "$#" -eq 1 ] && [ "$1" == "-h" ]; then
    print_help
    exit 0
fi


# Check if the input file was provided
if [ "$#" -ne 1 ]; then
    echo "Error: Input file path is required."
    print_help
    exit 1
fi

FILE_PATH=$1

# Check if the input file exists
if [ ! -f "$FILE_PATH" ]; then
    echo "Error: File $FILE_PATH not found."
    exit 1
fi

# Absolute path to the directory where the script is located
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_DIR="$(dirname "$SCRIPT_DIR")"

# Directory containing the input file
INPUT_DIR="$(dirname "$FILE_PATH")"
INPUT_FILE="$(basename "$FILE_PATH")"

# Execute the command in the container
docker run --rm \
    -v "${PROJECT_DIR}:/app" \
    -v "$INPUT_DIR:/data" \
    -w /data \
    wkt2geojson /app/application/bin/wkt2geojson -i "/data/${INPUT_FILE}"

# EOF
