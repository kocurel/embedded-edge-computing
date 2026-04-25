## WIP: Distributed Swarm Simulation: ESP32 & RISC-V Cluster

A project focused on offloading spatial navigation logic to a hardware cluster. The core idea is to simulate "autonomous agents" (Boids) where the heavy lifting is done by low-power microcontrollers.

**Current Goals**

- **Dual-Core Concurrency**: Implement the Boids algorithm in C, utilizing FreeRTOS tasks to manage flock logic and networking separately.
    
- **Networking**: Stream real-time agent data over UDP to a PC for visualization (SFML).
    
- **Hardware Scaling**: Offload sector-specific calculations to a cluster of CH32V003 (RISC-V) nodes over SPI to explore edge-computing patterns.
    
- **Algorithmic Optimization**: Implement a Quad Tree spatial partitioning structure enabling efficient distribution of computation across the RISC-V cluster.
    
**Roadmap**
- [X] **Core Math**: Implement a custom Q16.16 fixed-point library (Deterministic behavior across RISC-V and Xtensa).
- [ ] **Swarm Logic**: Implement the Boids algorithm (Cohesion, Alignment, Separation).
- [ ] **Networking**: Establish UDP telemetry between ESP32 and PC (SFML-based HMI).
- [ ] **Visualizer**: Create an SFML C++ application to render real-time Boid positions and telemetry.
- [ ] **Spatial Optimization**: Implement a Quadtree data structure for efficient neighbor searching (O(nlogn)).
- [ ] **Inter-chip Comm:** Design and implement a lightweight SPI protocol for ESP32 (Master) to CH32 (Cluster) communication.
- [ ] **Hardware Porting**: Port and optimize the Boids logic for the CH32V003 (RISC-V). This includes memory footprint reduction (fitting into 2KB RAM) and offloading specific Quadtree leaf calculations to the cluster nodes.
- [ ] **Hardware**: Design a KiCad schematic for the cluster backplane and power delivery.

**Update 1: Deterministic Fixed-Point Arithmetic**

To ensure high performance on MCUs without a Hardware Floating Point Unit (FPU) and to maintain identical behavior across different architectures (ESP32 vs. CH32), I implemented a custom Q16.16 fixed-point arithmetic library.
