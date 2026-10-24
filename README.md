# Intelligent Robotics — Lab Assignments

ROS 2 lab exercises for the **Intelligent Robotics** course at the **Department of Information Engineering (DEI), University of Padova (Unipd)**.

All packages are developed in C++ or Python for **ROS 2 (Jazzy Jalisco)** and built using `colcon`.

## Repository Structure

```
.
├── .gitignore
├── README.md
└── src/
    ├── exercise_1/
    │   └── temp_pkg/           # Temperature monitoring publisher &amp; subscriber
    ├── exercise_2/
    │   ├── vacuum_int/         # Custom message definition (.msg) for robot status
    │   └── vacuum_pkg/         # Autonomous vacuuming robot telemetry nodes
    └── exercise_3/
        ├── check_target_int/   # Custom service definition (.srv) for position checking
        └── target_pkg/         # Target server &amp; client C++ nodes

```

## Prerequisites

* **OS:** Ubuntu 24.04 LTS (or WSL2)
* **ROS Distribution:** ROS 2 Jazzy Jalisco
* **Build System:** `colcon` with `ament_cmake`

## Running the Nodes

### Exercise 1: Temperature Monitoring System

```
# Terminal 1: Publisher
ros2 run temp_pkg temp_publisher

# Terminal 2: Subscriber
ros2 run temp_pkg temp_subscriber

```

### Exercise 2: Autonomous Vacuum Robot Telemetry

```
# Terminal 1: Robot Publisher
ros2 run vacuum_pkg vacuum_publisher

# Terminal 2: Charging Base Subscriber
ros2 run vacuum_pkg vacuum_subscriber

```

### Exercise 3: Target Position Verification Service

```
# Terminal 1: Server Node
ros2 run target_pkg target_server

# Terminal 2: Client Node
ros2 run target_pkg target_client

```

## Author

* **Elia De Rossi**
* Department of Information Engineering (DEI), University of Padova
* Student Email: `elia.derossi.1@studenti.unipd.it`
