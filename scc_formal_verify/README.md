# Kosaraju's SCC Algorithm - Formal Verification

Implementation of Kosaraju's algorithm for finding strongly connected components (SCCs) with formal verification using TLA+ and Z3.

## Overview

This project demonstrates:
- **C++ implementation** of Kosaraju's SCC algorithm
- **TLA+ formal specification** with invariants and properties
- **Z3 SAT solver** for verification

## Quick Start

```bash
# Run everything (build, test, verify)
./run.sh

# Or manually:
make test          # Build and test C++ implementation
tlc2.TLC Kosaraju  # Run TLA+ verification with Z3
```

## Prerequisites

- **C++ compiler** (g++ with C++17 support)
- **TLA+ Toolbox** or **tlc2.TLC** command-line tool
- **Z3 SMT solver** (for TLA+ verification)

### Installation

**Ubuntu/Debian:**
```bash
sudo apt-get install g++ z3
sudo snap install tlaplus  # GUI toolbox only
# For command-line tlc2.TLC, download from Microsoft website
```

## Algorithm

Kosaraju's algorithm finds SCCs in two passes:

1. **First Pass**: DFS on original graph to compute finishing order
2. **Second Pass**: DFS on transpose graph in reverse finishing order

## Formal Verification

The TLA+ specification (`Kosaraju.tla`) includes:

- **Type invariants** ensuring data structure correctness
- **Algorithm invariants** maintaining algorithm properties
- **Safety properties** verifying SCC count bounds
- **Liveness properties** ensuring termination

### Verified Properties

- `Property1`: SCC count ≥ 1
- `Property2`: SCC count ≤ number of nodes  
- `Property3`: Components count equals SCC count

## Testing

The C++ implementation includes comprehensive tests:

- Triangle graph (1 SCC)
- Two separate cycles (2 SCCs)
- Empty graph (0 SCCs)
- Single node (1 SCC)

## Verification Results

When you run `./run.sh`, you should see:

```
[info] Building C++ implementation...
[info] ✓ C++ tests passed
[info] Running TLA+ verification with Z3...
[info] ✓ TLA+ verification completed successfully
[info] All verification passed!
```

## Manual Verification

```bash
# Test C++ implementation
make test

# Run TLA+ verification manually
tlc2.TLC -workers 4 Kosaraju

# Run with Z3 solver specifically
tlc2.TLC -solver z3 Kosaraju
```

## Project Structure

```
.
├── kosaraju.cpp      # C++ implementation
├── Kosaraju.tla      # TLA+ specification  
├── Kosaraju.cfg      # TLA+ configuration
├── Makefile          # Build system
├── run.sh           # One-command runner
└── README.md        # This file
```

## License

MIT License - feel free to use for educational and research purposes.