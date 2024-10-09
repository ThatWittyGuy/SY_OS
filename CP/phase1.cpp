// About:
// This program simulates a simple OS that can read commands from a file, execute them, and manage a block of physical memory. 
// The OS can perform basic operations like loading data, executing instructions, and managing input/output through file streams.

#include <iostream>
#include <fstream>
using namespace std;


// Purpose: This class encapsulates the OS's data structures and methods for managing memory and executing commands.
class OS {
    private:
        char M[100][4];     // Physical Memory (100 blocks of 4 bytes each)
        char IR[4];         // Instruction Register (holds current instruction)
        char R[4];          // General Purpose Register (holds data)
        int IC;             // Instruction Counter (points to the current instruction)
        int SI;             // Interrupt (indicates the type of operation)
        bool C;             // Condition flag (used for branching)
        char buffer[40];    // Buffer for reading data

    public:
        void init();        // Initializes OS
        void LOAD();        // Loads data into memory
        void Execute();     // Executes instructions
        void MOS();         // Master Operating System function
        void ReadData();    // Reads data into memory
        void WriteData();   // Writes data from memory
        void Terminate();   // Terminates OS or process
        void LoadInstruction(); // Loads instruction into register
        void StoreInstruction(); // Stores instruction into memory
        void CompareRegisters(); // Compares register values
        void BranchIfTrue(); // Branches based on comparison
        void ClearBuffer();  // Clears input/output buffer
        void PrintMemory();  // Displays memory contents


        fstream infile;     // Input file stream
        fstream outfile;    // Output file stream
};


// Purpose: Resets the physical memory and registers to a default state, preparing the OS for operation.
void OS::init() {
    for(int i = 0; i < 100; i++) {    
        for(int j = 0; j < 4; j++) {  
            M[i][j] = ' ';  // Initialize memory to spaces
        }
    }    
    IR[0] = {' '};  // Initialize instruction register
    R[0] = {' '};   // Initialize general-purpose register
    C = false;      // Initialize condition flag
}

// Purpose: Clear the buffer
void OS::ClearBuffer() {
    for (int i = 0; i < 40; i++) {
        buffer[i] = '\0';
    }
}

// Purpose: Print the memory
void OS::PrintMemory() {
    for (int i = 0; i < 100; i++) {
        cout << "M[" << i << "]\t";
        for (int j = 0; j < 4; j++) {
            cout << M[i][j];
        }
        cout << endl;
    }
}

// Purpose: Handles different types of operations based on the value of the interrupt (SI). It reads from the input file, writes to the output file, or terminates the program.
void OS::MOS() {
    ClearBuffer();
    if (SI == 1) { // Read Mode
        infile.getline(buffer, 40);
        ReadData(); // Read data from input file and store in memory
    } else if (SI == 2) { // Write Mode
        WriteData(); // Write data from memory to output file
    } else if (SI == 3) { // Terminate
        Terminate(); // Handle termination of the program
    }
}

// Read data into memory
void OS::ReadData() {
    int k = 0;
    int i = (IR[2] - '0') * 10;

    for (int l = 0; l < 10; ++l) {
        for (int j = 0; j < 4; ++j) {
            M[i][j] = buffer[k++];
        }
        if (k == 40) break;
        i++;
    }
    PrintMemory();
}

// Write data from memory to output
void OS::WriteData() {
    ClearBuffer();
    int k = 0;
    int i = (IR[2] - '0') * 10;

    for (int l = 0; l < 10; ++l) {
        for (int j = 0; j < 4; ++j) {
            buffer[k] = M[i][j];
            outfile << buffer[k++];
        }
        if (k == 40) break;
        i++;
    }
    outfile << "\n";
    PrintMemory();
}

// Terminate the program
void OS::Terminate() {
    outfile << "\n\n";
}

// Purpose: Continuously fetches and executes instructions from memory until a termination command is encountered.
void OS::Execute() {}


// Purpose: Reads commands and data from an input file, initializing the OS and loading data into memory as specified by the commands.
void OS::LOAD() {}

// Purpose: Initializes the OS, opens the input and output files, and starts the loading process to execute the program.

int main() { 
    OS os;  // Create an instance of the OS class

    os.infile.open("input.txt", ios::in);  // Open input file
    os.outfile.open("output.txt", ios::out);  // Open output file

    if(!os.infile) {
        cout << "Failure" << endl;  // Check if the input file opened successfully
    } else {
        cout << "File Exist" << endl;
    }
      
    os.LOAD();  // Load data and execute commands

    return 0;
}
// File Handling: The code demonstrates basic file handling in C++ using fstream.
// It checks for the existence of the input file before proceeding.

// Class Structure: The OS class encapsulates the properties and methods relevant to a virtual operating system,
// allowing for modular design.

// Initialization: The init() method is crucial for setting up the system's state before executing any operations,
// ensuring that all memory and registers are in a known state.

// Unimplemented Functions: The LOAD(), Execute(), and MOS() methods are placeholders that would need to be
// implemented to provide functionality for loading data, executing instructions, and managing I/O operations.
