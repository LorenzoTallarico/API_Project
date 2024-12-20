# Algorithms and Principles of Computer Science project

Welcome to the **Vehicle Station Management System**!

This project serves as the final assignment for the **Algorithms and Principles of Computer Science** course at **Politecnico di Milano** for the **Academic Year 2022/23**. It was evaluated with a top grade of **30 cum laude**.

Designed to efficiently manage vehicle stations, vehicles, and their routes, this application employs a robust binary tree structure. It offers essential functionalities for adding and removing stations and vehicles, as well as planning optimized routes based on vehicle autonomy.

## Table of Contents
- [Features](#features)
- [Getting Started](#getting-started)
- [Project Specification](#project-specification)
- [Usage](#usage)
- [Functionality Overview](#functionality-overview)
- [Technologies Used](#technologies-used)
- [Documentation](#documentation)
- [License](#license)

## Features
- **Station Management**: Easily add or remove stations.
- **Vehicle Management**: Add and remove vehicles associated with each station.
- **Route Planning**: Plan routes based on ascending or descending station IDs, ensuring optimal vehicle usage.
- **Memory Management**: Automatic cleanup of resources to avoid memory leaks.

## Getting Started
To get started with this project, clone the repository and compile the source code. Follow these steps:

### Clone the repository:
```bash
git clone https://github.com/LorenzoTallarico/API_Project.git
cd API_Project
```

### Compile the code:
```bash
make API_Tallarico
```
### Run the application:
```bash
./API_Tallarico < path_input_file.txt > output_file.txt
```
## Project Specification
For further information on the project context and requirements, please refer to the detailed project document, available in both English and Italian:

- [English version](./Instructions_ENG.pdf)
- [Italian version](./Instructions_ITA.pdf)

## Usage
You can interact with the application by providing commands through an input file. The available commands include:

- **aggiungi-stazione**: Add a new station.
- **demolisci-stazione**: Remove an existing station.
- **aggiungi-auto**: Add a new vehicle to a station.
- **rottama-auto**: Remove a vehicle from a station.
- **pianifica-percorso**: Plan a route between two stations.

After running the application, you can check the output against the expected results using the `diff` command:
```bash
diff ./public_output ./program_output
```
This command will help you verify that the output generated by your application matches the expected output.

## Functionality Overview
This project leverages advanced data structures, specifically binary trees, to intricately manage the relationships between vehicle stations and their corresponding vehicles. Key functionalities include:

- **Recursive Traversals**: Implement sophisticated recursive algorithms that optimize tree traversal, enabling seamless addition and removal of stations and vehicles with minimal time complexity.

- **Intelligent Route Planning Algorithms**: Utilize cutting-edge algorithms to determine optimal routes based on vehicle autonomy and station IDs, ensuring efficient resource allocation and maximizing operational effectiveness.

- **Balanced Tree Management**: Employ advanced techniques for maintaining balanced binary trees, ensuring efficient search, insertion, and deletion operations, which contribute to improved performance across large datasets.

- **Linked List Handling**: Integrate dynamic linked lists to efficiently manage vehicle routes, utilizing pointers and recursive functions to manipulate data structures fluidly, enhancing the flexibility and scalability of the application.

- **Robust Memory Management**: Incorporate advanced memory management techniques to dynamically allocate and deallocate memory, preventing memory leaks and ensuring the application runs efficiently and reliably.

## Technologies Used
- **C Programming Language**
- **Doxygen** for documentation

## Documentation
For detailed documentation, [click here](https://lorenzotallarico.github.io/API_Project/Doc/index.html).
In case of any display issues, you can access the complete documentation in PDF format, [click here](./Doc/CompleteDocumentation.pdf).

## License
This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
