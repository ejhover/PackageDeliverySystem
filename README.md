# University of Minnesota Package Delivery Simulation

This simulation simulates Drone Delivery on the University of Minnesota Campus. Drones, humans, and helicopters move around the map. The drones follow a route specified by the user, picking up and then delivering packages to Robots. The humans and helicopters move randomly around the map to show if the movement is working correctly. The user can create more drones, both normal and cooled or humans. The drones have a battery life, which depletes as it moves. There are also cooled drones, which also have a battery as well as a cooling system. Both of these drones must visit recharge stations before delivery if they are too low on battery, and cooled drones must visit cooling stations to refresh their cooling when that gets low. When the drones complete a job, they celebrate according to the pathing strategy used to deliver the package. The celebrations are a mixture of jumping and spinning. During the simulation, the weather will change randomly as time passes. The types of weather are 'Normal', 'Heatwave', 'Rain', and 'Snow'. These weathers will change how quickly the drone moves and how quickly the cooling changes. As the simulation runs, data will be collected by a Data Collector and will be printed to a CSV file when the simulation is stopped.

## Features (integrated with an Agile Development Lifecycle)

- **Simulated Entities**: Includes drones(regular and cooled), helicopters, humans, robots, recharge stations, cooling stations, and packages.
- **Delivery Scheduling**: Employs search strategies(A*, BFS, DFS, Beeline) to schedule package pickups and drop-offs.
- **Backend**: Developed in C++ with an extensible factory pattern for creating entities.
- **Frontend**: A TypeScript-based web server that visualizes the simulation.
- **Communication**: Backend sends `JsonObject`s to the frontend for rendering and updates.
- **Modular Architecture**: Entity factories and customizable delivery strategies.
- **Battery Extension**: Allows for drones to have batteries that deplete while flying and integrate logic into delivery strategies to visit recharge stations when a recharge is needed to successfully make the trip.
- **Cooling Extention**: Allows for cooled drones that can hold packages that need to be cooled. When the drone needs to re-cool its contained, it can visit cooling stations (similar to recharge stations).
- **Weather Extension**: Simulates the random changing of weather (normal, heatwave, rain, snow) which affects the cooling of the packages and the speed of the drones.

## Code Structure

### Backend (C++)

- **Entity Factories**: Factories for creating different entities (`DroneFactory`, `HumanFactory`, etc.).
- **SimulationModel**: Core simulation logic, including:
  - Entity creation and management
  - Delivery Scheduling
  - State updates
  - Notifications to the frontend

### Frontend (TypeScript)

- Renders the simulation on a local web server.
- Visualizes the campus, entities, and ongoing deliveries.

## Prerequisites

- C++ compiler supporting C++11 or later
- Node.js and npm for the frontend
- Web browser for accessing the visualization at `127.0.0.1:8081`

## Instructions: 
Clone the Repository:
  ```bash
   git clone https://github.com/ejhover/PackageDeliverySystem.git
   cd PackageDeliverySystem
  ```
To clean the Makefile build for the simulation, execute:
```bash
   make clean
```
To build the simulation, execute:
```bash
   make -j
```
To run the simulation, execute:
```bash
   make run
```
To view the simulation in your browser, search:
```bash
   http://127.0.0.1:8081/
```

## [Docker Image](https://hub.docker.com/repository/docker/emmethover/team-033-finalproject/general)
Pull the image from the link above and execute this command to run:
```bash
  docker run --rm -it -p 8081:8081 emmethover/team-033-finalproject
```

## UML Diagram
![Final UML](/UML.jpeg)
