# University of Minnesota Package Delivery Simulation

This project simulates the University of Minnesota campus using a backend written in C++ and a frontend powered by TypeScript. The simulation supports various entities like drones, helicopters, humans, robots, and packages. It uses different search strategies to schedule and manage deliveries effectively. The frontend renders the simulation at `127.0.0.1:8081`.

## Features

- **Simulated Entities**: Includes drones, helicopters, humans, robots, and packages.
- **Delivery Scheduling**: Employs search strategies to schedule package pickups and drop-offs.
- **Backend**: Developed in C++ with an extensible factory pattern for creating entities.
- **Frontend**: A TypeScript-based web server that visualizes the simulation.
- **Communication**: Backend sends `JsonObject`s to the frontend for rendering and updates.
- **Modular Architecture**: Entity factories and customizable delivery strategies.

## Code Structure

### Backend (C++)

- **Entity Factories**: Factories for creating different entities (`DroneFactory`, `HumanFactory`, etc.).
- **SimulationModel**: Core simulation logic, including:
  - Entity creation and management
  - Delivery scheduling
  - State updates
  - Notifications to the frontend

### Frontend (TypeScript)

- Renders the simulation on a local web server.
- Visualizes the campus, entities, and ongoing deliveries.

## Getting Started

### Prerequisites

- C++ compiler supporting C++11 or later
- Node.js and npm for the frontend
- Web browser for accessing the visualization at `127.0.0.1:8081`

### Installation

1. **Clone the Repository**
   ```bash
   git clone https://github.com/ejhover/PackageDeliverySystem.git
   cd PackageDeliverySystem

## Usage

```bash
   make run
   visit 127.0.0.1:8081
