# Course Catalog Manager Using a Binary Search Tree (BST)

This is a command-line C++ tool that lets academic advisors load, explore, and maintain a university course catalog. Courses are imported from a CSV file into an in‐memory BST keyed by course code. You can then add, remove, search, list, and export courses—all in average O(log n) time.

___________________________________________________________________________________________________

## Features

• CSV Import & Export
  – Load a startup catalog from a standard CSV (course code, title, credits, prereqs).
  – Save the current catalog and back out to CSV after edits.

• BST Operations
  –  Insert new courses or delete existing ones.
  – Search by course code in logarithmic time.
  – In‐order traversal prints all courses sorted alphabetically.

• Prerequisite Handling
  –  Store and display prerequisite lists for each course.
  – Validate prerequisite chains upon insertion.

• Console-Based Menu
  – Interactive text menu for all core CRUD actions, CSV reload, and export.
  – Input validation and clear on-screen prompts.

• Testing & Debugging Support
  – Manual test suite covering edge cases (empty tree, duplicates, leaf/internal deletions).
  – Easy to step through with Visual Studio’s debugger.

___________________________________________________________________________________________________

## Technology Stack

• C++17
• Visual Studio 2022 (solution and project files included)
• Standard Library: <fstream>, <string>, pointer-based data structures
• Git & GitHub for version control

___________________________________________________________________________________________________

## Repository Structure

- .vs/ # VS internal files
- x64/ # Build output folder
- ProjectTwo.sln # Visual Studio solution
- ProjectTwo.vcxproj # VS C++ project
- ProjectTwo.vcxproj.filters # VS project filters
- ProjectTwo.vcxproj.user # VS user settings
- ProjectTwo.cpp # Main C++ source implementing BST + UI
- CS 300 ABCU_Advising_Program_Input.csv
  - docs/ # (optional) UML diagrams, design report, test report

___________________________________________________________________________________________________

## Getting Started

1. Clone the repository
  - git clone https://github.com/Coutmeout/project-two.git

2. Open the Visual Studio solution
  - Launch ProjectTwo.sln in Visual Studio 2022

3. Use Build → Build Solution (Ctrl+Shift+B).
  - The executable will appear in x64\Debug\ProjectTwo.exe or x64\Release\ProjectTwo.exe if you switch configurations.

4. Prepare a CSV file
  - Ensure CS 300 ABCU_Advising_Program_Input.csv is in the repository root (already provided).
  - Format:
    - CourseCode,Title,Credits,Prereq1;Prereq2;…
    - CS101,Introduction to Computer Science,3,
    - CS201,Data Structures and Algorithms,4,CS101

5. Run the application
  - From Visual Studio: Start with debugging (F5) or without (Ctrl+F5)
  - Or from the command line:
    - .\Debug\CourseCatalogManager.exe
  
6. Use the menu to import, add, delete, search, list, and export courses.

___________________________________________________________________________________________________

## Usage Examples

– Import a catalog:
    - choose “1. Load Catalog from CSV” and enter data/input.csv
– Add a course:
    - choose “2. Add Course” and enter code/title/credits/prereqs
– Search for CS201:
    - choose “4. Search Course” and enter CS201
– Print full catalog: 
    - choose “5. Print All Courses”
– Export catalog:
    - choose “6. Export to CSV” and enter data/output.csv

___________________________________________________________________________________________________

## Project Structure

• '/src' – C++ source files ('.cpp' & '.h')
• '/data' – Sample CSVs for input/output
• '/docs' – UML sketches, design, and test report (PDF)
• 'ProjectTwo.sln' – Visual Studio solution

## Contributing

- Fork the repository
- Create a feature branch (git checkout -b feature/XYZ)
- Commit your changes (git commit -m "Add awesome feature")
- Push to the branch (git push origin feature/XYZ)
- Open a Pull Request

## License
This project is licensed under the MIT License – see the LICENSE file for details.
