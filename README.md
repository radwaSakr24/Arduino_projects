# Arduino & Embedded Systems Projects

A collection of embedded software projects developed for Arduino microcontrollers, focusing on hardware interfacing, serial communication and display integration. 
---

## Repository Structure

| Project Directory | File Name | Hardware Used |
| :--- | :--- | :--- |
| **[`/xo_game`](./xo_game)** | `XO_2player.ino` | Arduino, 20x4 I2C LCD 

---

## Featured Project: Serial Tic-Tac-Toe (`/xo_game`)

An interactive two-player game rendered on a **20x4 character LCD** via the PCF8574 I2C adapter, driven by move inputs sent over the **Arduino Serial Monitor**.

### Grid Coordinate System
Moves are entered via Serial as array indices (`0` through `8`), which dynamically update the 20x4 LCD grid:

```text
 0 | 1 | 2
---+---+---
 3 | 4 | 5
---+---+---
 6 | 7 | 8
