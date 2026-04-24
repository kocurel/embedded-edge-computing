## Status: WIP

## Boids algorithm (flock simulation) implementation on the dual core ESP32 using two cores for concurrency

### The goals for the project
The main goals:
    - Implement the boids algorithm in C
    - Learn more about FreeRTOS Task concurrency and shared state
    - Send the Boids data over UDP to the PC and render the graphic interface

### Update 1: Fixed point arithmetic
For a higher performance and deterministic behaviour, I have decided to use a custom Q16.16 fixed point arithmetic

