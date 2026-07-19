# Note

This project was made during the Course Object Oriented Programming in C++. Strictly speaking, this project didn't require OOP; instead it can be made purely using Programming Fundamentals concepts too. However, as a requirement for OOP course, OOP concepts were used.

# Custom Loan Management System

A low-level file handling application developed in C++ that provides full administrative control over system balances, user records, and cryptographic access control. Built without relying on standard container libraries or smart pointers, this project demonstrates manual memory tracking, heap allocations, and pure file stream manipulation.

## Core Features

- **Dynamic Memory Management:** Uses raw arrays and manual pointer tracking (`new` and `delete[]`) to capture and parse text streams safely without relying on `std::vector` or external string structures.
- **File Stream Infrastructure:** Processes database records using custom string comparison and copy algorithms to parse multi-column fields line by line.
- **Cryptographic Access Control:** Implements a bitwise XOR rotation algorithm to securely encrypt and decrypt administrative passwords stored inside flat text files.
- **Automated Backup Cycles:** Seamlessly marshals active structural records into a raw binary state (`.bin`) upon logout, offering automated restoration mechanisms in the event of active workspace corruption.
- **Operational Audit Logging:** Maintains an append-only transaction history file (`history.txt`) tracking all structural updates, including balance shifts, liquidations, and data modifications.

## Architectural Structure

The records within this architecture use a manual layout tracking the dynamic entities below:

- `id`: An unsigned short integer serving as a unique system identifier.
- `cnic`: A character pointer managing unique identification strings.
- `loanAmount`: An unsigned integer tracking total financial allocations.
- `name`: A heap-allocated character pointer storing long-form string fields.

## Supported Operations

The administrative console parses case-sensitive command strings to perform core database operations:

- `addRecord`: Integrates a new loan entry into the database after validating overall system balance and threshold limits.
- `addBalance`: Allocates additional operating funds directly to the master ledger file.
- `showLoans`: Parses and renders all valid file rows sequentially.
- `showById` / `showByCnic`: Executes precise linear table scans matching search filters.
- `removeById` / `removeByCnic`: Performs stream-skipping file writes to purge targets cleanly without leaving empty fragments.
- `returnInstallment`: Debits active loan entries while scaling down specific dynamic records.
- `changePassword`: Runs verification cycles on administrative passwords before writing updated keys back to storage.
- `showSummary`: Compiles mathematical aggregates, identifying minimal, maximal, and outstanding system investments.
- `restoreBackup` / `showBackup`: Swaps the active text stream with a binary backup or previews backup details safely.
- `showHistory`: Pipes raw stream logs directly into the terminal window.

## Compilation and Execution

Compile the source file using any standard C++ compiler:

```bash
g++ -o loan_system main.cpp
./loan_system
```

On your initial execution, the application prompts you to configure an encrypted administrative password and fund the opening system balance. Subsequent startups enforce a rigorous authentication sequence limited to three attempts.