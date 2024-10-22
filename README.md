# 3081 Lab 6: Import Assets
_(Due: Thursday, October 17th, 2024 @ 11:59pm)_

## Accessing a Lab Machine

For this assignment, you should make sure you are using our shared CSE development environment.  As such, you should use a lab machine in ***Keller Hall 1-250*** or ***Keller Hall 1-262*** ([details](https://cse.umn.edu/cseit/classrooms-labs#cselabs)).  If you do not have physical access to one of the lab computers, you can also access a lab machine remotely using [SSH](https://github.umn.edu/umn-csci-3081w-f24-sec010/FAQ/blob/main/SSH/README.md) or a web-based service called [VOLE](https://github.umn.edu/umn-csci-3081w-f24-sec010/FAQ/blob/main/VOLE/README.md). If using VOLE, be sure to use VOLE-FX3 for full compatibility.  You will use your CSE Labs account to login to the lab machines. If you do not already have an account, create the account following these [instructions](https://wwws.cs.umn.edu/account-management).


**IMPORTANT: Inside the lab machine, only files saved to your home folder (e.g., `/home/lorim007`) will persist across sessions. If you log out, make sure your progress is pushed to GitHub or saved in the home folder.**

## Retrieve Class Materials

1. Clone your personal repository for the lab. **Replace the x500 with your personal x500.**
    ```bash
    git clone git@github.umn.edu:umn-csci-3081w-f24-sec010/x500-lab06.git
    ```
## What's in the lab06 folder?

<ul>
  <li>  <code>README.md</code>: You're reading this right now.
  <li>  <code>.gitignore</code>
  <li>  <code>dependencies</code>: A folder that contains external tools and libraries to compile and run the project.
  <li>  <code>docs</code>: Documentation files
  <li>  <code>service</code>: A folder with base code.  This contains:
    <ul>
      <li>  <code>include</code>: Header files
      <li>  <code>src</code>: Source files
    </ul>
  <li>  <code>web</code>: Front-end files
</ul>

## What You Will Do

1. Import assets into the simulation
1. Extend the Entity class hierarchy in the GOPHER simulation by creating two new classes, Helicopter and Human


# Part 0 - Required! Git Branch & Pull Requests

## Base Code Double Check ##
All base code given in labs will compile and run on machines specified in the [accessing a lab machines](#accessing-a-lab-machine) section. You should verify this by building and running the base code before you start the lab. If this code does not build and run on the given machines, please contact a teaching assistant.

## Git Branch & Pull Requests

Did you remember to create the development branch before starting last week's lab? To avoid a headache this week (or possibly repeat one, depending on how you feel about branching), start off by creating a development branch from the main branch.  Remember to make sure you've checked out the development branch locally before you start working!

# Importing Assets and Creating New Entities

In Workshop 3, we covered requirements, specifications, and design for a LightRail system. During this session, we asked you to identify various actors within the system, ranging from obvious ones like passengers and carts to less evident ones like weather conditions and routes. In the GOPHER drone delivery simulation, we identified a few actors: the drone, packages, and robots. However, what if we wanted to introduce additional actors into this system? In this lab, we will explore how to incorporate more entities, potentially enhancing the diversity of actors in the system or simply making the simulation appear more dynamic.

The goal of this lab is to teach you how to import and add entities/assets into the simulation. We are not yet fully concerned with good coding practices. We will be violating the S and O of SOLID in todays lab.

### Violating the S of SOLID
When we add helicopter and human entities into our simulation system, we're making sure that they come with movement capabilities. However, it's important to recognize that this approach breaks the Single Responsibility Principle. By embedding movement logic directly within these classes, we introduce a lack of cohesion and increase the complexity of debugging. Furthermore, should we decide to alter how entities move, we'd be compelled to modify each entity class individually, violating the principle of encapsulation.

To mitigate these concerns, a more robust solution involves encapsulating movement functionality within a dedicated `Movement` class. This approach centralizes movement logic, facilitating easier maintenance and extensibility. We anticipate exploring this concept further in an upcoming lab session (lab 8), where we'll delve into implementing the strategy design pattern to decouple movement from entity classes.

### Violating the O of SOLID
Regarding our violation of the Open/Closed Principle, we acknowledge the need for our system to be open to extension but closed to modification. Currently, the mechanism for creating entities within our SimulationModel involves an if-else block, necessitating modifications when adding new entity types. This violates the Open/Closed Principle, as it requires direct alterations to existing code.

To address this, we've devised a plan to refactor our system using a Composite Factory pattern (lab 7). By leveraging this design pattern, we'll abstract the entity creation process, ensuring that the addition of new entities doesn't necessitate modifications to existing code. The Composite Factory will serve as a versatile tool, allowing for seamless extension of our simulation system while upholding SOLID principles.


## Entity 1 (Helicopter)
**Remember to create a development branch!**

Steps:
1. Download the helicopter model from either [the class github](https://github.umn.edu/umn-csci-3081w-f24-sec010/ProjectAssets) or other sources like [sketchfab](https://sketchfab.com/)
   - *Important: File must be .glb format*
1. Place the helicopter model under `<project>/web/public/assets/model` folder.
1. Create the `Helicopter` entity class.
   - Create `Helicopter.h` in `service\include\simulationmodel\entity`
   - Create `Helicopter.cc` in `service\src\simulationmodel\entity`
   - Helicopter class inherits from IEntity
   - Define the required methods for Helicopter
      - `Helicopter(const JsonObject&)`
      - `~Helicopter()`
      - `update(double dt)`

1. **This is a big step, so read all the way through before implementing this logic.** To define the behavior of our new Helicopter entity, a majority of what we will be doing is done in the helicopter's `update(double dt)` method. This method is called at least once every time the front end sends a message to update the state of the simulation. The helicopter will move from its current position towards a randomly chosen destination. Once the helicopter reaches its destination, it will select a new random destination and repeat the process.

   One other thing we'll be paying a little bit of attention to in the Helicopter class is a (very basic) estimation of movement physics.  To wit, we want to make sure we're updating the simulation correctly by using the helicopter's speed to calculate how far it will travel in a given timeframe.  You can see this in the last few lines of the pseudocode below where we're calculating a movement vector using a time delta.  Perhaps kinematics on a Friday isn't entirely fair, but think back to your time in physics and recall that a time delta (dt or ∆t) is simply a time step with some given unit.    Now that you're in a physics frame of mind, add in what you know about computer graphics.  There isn't any actual movement in graphics or animation of course – rather, the way and position in which objects are rendered, or drawn, on the screen gives you the impression of movement.  This is where dt comes into play.

   You may have heard the term refresh rate before.  This refers to how many images can be rendered on a screen in a second.  You've likely also heard the term FPS (frames per second), which refers to how many images are being rendered in a second.  In graphics we care about refresh rate and FPS because it helps us create more realistic movement.  This is where the time delta (dt) becomes important in rendering – dt tells us how much time has elapsed since the last image was drawn.  To create a more realistic impression of movement, we take what we know about the speed of a given object and now our dt to determine what the object's new position will be when the image is redrawn.  For example, let's say we add a snail to our simulation and draw it at the rate of 1 FPS.  We intuitively know that if we redraw our snail every second its position in each image won't change very much.  In fact, our snail object might only need to be moved a few pixels over from one image to the next.  For a fast object like a helicopter, however, you can imagine that position might change quite a bit more than a handful of pixels! Incorporating the time delta in rendering helps make sure we capture this in our simulation (and makes it significantly less tedious to look at), which is why we're including it now.

   Take a look at this python/pseudo code for how the movement of the helicopter will work.
   ```python
   def update(dt):

      # if the difference between our position and destination is small
      # enough then we consider ourselves "at" the destination
      if ((position - destination).length < MIN_DISTANCE):

         # get a new random position
         destination = randomPosition()

      else: # if we are NOT at our destination

         # get the resulting vector from our position to the destination
         diff = destination - position

         # convert that difference to a unit vector
         diff_unit = diff.unit()

         # calculate how far you will move in the time delta (dt)
         # "speed in a direction scaled by difference in time is distance traveled"
         movement_vector = diff_unit * speed * dt

         # Update the position with the movement
         position = position + movement_vector
   ```
   
   Here is the section previously referenced in [Violating the S of SOLID](#violating-the-s-of-solid) where we hard code the movement logic of an entity. Additionally, what will happen when we implement the movement of humans in the next section? They will reuse much of the same linear movement logic to traverse between two locations. However, for the purposes of this lab, copying and pasting (CTRL+C, CTRL+V) will have to suffice. As mentioned earlier, we will refactor this in a subsequent lab.

   Here are a few more notes that will help you implement this in C++ for the helicopter class.
   - You will want to add a destination attribute to the helicopter class with a type of `Vector3`
   - The `Vector3` class contains the tools and formulas to implement the logic above. Take a look at the documentation and methods available to you.
   - It's best that the helicopter starts out with a target destination, so having logic in the constructor to set the destination upon creation is highly recommended.
   - The helicopter's Y position is best kept at the same height. So you will only need to generate a new X and Z position. Example:
      ```c++
      Vector3 destination = {((static_cast<double>(rand())) / RAND_MAX) * (2900) - 1400,
                 position.y,
                 ((static_cast<double>(rand())) / RAND_MAX) * (1600) - 800};
      ```
      If you have a private member variable `destination` and you copy and paste the code above, this may break the motion of the helicopter.

   - Here are the random values that the X and Z should stay within to keep the entity above or on the map.
      ```
      -1400 < x < 1500
      y = 550
      -800  < z < 800
      ```
   - The `MIN_DISTANCE` is a value that you will need to explore and see what looks right.

1. Once you are done defining the helicopter class, you will need to update the `simulationmodel` so that it can handle the creation of the new entity.

   Look in `SimulationModel.cc` for the method `createEntity`. Update the if-else block to create a new helicopter if `type == "helicopter"`. Take a look at the code already present for clues. Note how this section is in violation of the O of SOLID. Whenever we want to add a new entity to this simulation, we need to modify this code block to handle the new entity. Next week we will go over a more eloquent solution for entity creation. _Don't forget to include the helicopter header file as well at the top of SimulationModel.cc._

1. When a browser connects to the web server, it will load the `umn.json` file which can be found under `<project>/web/public/scenes/umn.json`
1. Add a new JSON object inside the umn.json file to create a helicopter at the start of the simulation with the following info (Note: replace mesh, position, and scale according to your model's choice):
   ```json
   {
      "command": "CreateEntity",
      "params": {
         "type": "helicopter",
         "name": "Helicopter",
         "mesh": "assets/model/helicopter.glb",
         "position": [x, y, z],
         "scale": [0.025, 0.025, 0.025],
         "rotation": [0, 0, 0, 0],
         "direction": [1,0,0],
         "speed": 50.0,
         "offset": [0, 1.5, 0]
      }
   }
   ```
   `mesh` = model file location<br>
   `position` = your choice as long as it's within the map <br>
   `scale` = make it look like real life size (i.e., not too small or too large)
1. If you did all of the steps above correctly, the helicopter should be created and moving around as soon as you start the webpage.

## Task 2 (Human)
Steps:
1. Download the Human model from either [the class github](https://github.umn.edu/umn-csci-3081w-f24-sec010/ProjectAssets) or other sources.
   - *Important: File must be .glb format*
1. Place the human model under `<project>/web/public/assets/model` folder.
1. Create the `Human` entity class. Like the helicopter class before, create the source and header files in the appropriate folders, define the constructor, destructor and update method.

   For the `update(double dt)` method the human entity will have a simple behavior where they continually run up and down Washington avenue. Once they reach one end of their route, they turn around and head to the other end. For the sake of this lab, there are the two destinations that the human class should be running between. _Note: These coordinates may cause the human to clip through buildings and the ground. This is expected._
   ```
   (146,265,-121)
   (-191,265,-112)
   ```

   The human will utilize the same movement math as before, but here is a reminder of the math again.
   ```
   1. Get the delta/difference vector between position and destination
   2. Convert the delta to a unit vector, and this will act as the direction of movement.
   3. Update the position with the entities speed * delta_time * direction of motion
   ```
   How you want to implement this is up to you, but here are some ideas.
   - Have two Vector3 destinations and add a boolean attribute to the Human class that flips between what destination the human is moving towards.
   - Add a destination attribute to the Human class with type Vector3.  The human can then travel towards the destination and update it once they reach it.

   **Regardless of the method you choose, your performance will be evaluated based on whether the human or multiple humans can independently follow this motion path.**

1. Update `SimulationModel::createEntity` to create human entities if `type == "human"`.
1. Add a new JSON object inside the `umn.json` to create a human at the start of the scene with the following info. Be sure to set a starting position. It may be easiest to use one of the two end locations.
      ```json
      {
         "command": "CreateEntity",
         "params": {
            "type": "human",
            "name": "Human-OG",
            "mesh": "assets/model/human.glb",
            "position": [start_X, start_Y, start_Z],
            "scale": [0.005, 0.005, 0.005],
            "rotation": [0, 0, 0, 0],
            "direction": [1,0,0],
            "speed": 10.0,
            "radius": 1.0,
            "start": 2.0,
            "duration": 2.0,
            "offset": [0, -0.5, 0]
         }
      }
      ```
      `mesh` = model file location<br>
      `position` = your choice as long as it's within the map <br>
      `scale` = make it look like real life size (i.e., not too small or too large)
1. If you did all of the steps above correctly, the `Human-OG` should be created and moving as soon as you start the webpage. You can also add more humans to the simulation by clicking the "Add Human" button in the menu on the webpage.

### Task 4 (Doxygen)
Write Doxygen-formatted documentation for all the **NEW** classes you create.  You only need to document your public methods, which for this lab are as follows:
- Helicopter
- Human

### Task 5 (Code Style)
Match your new code's style with Google Code Styling guide. For this lab, the two classes to make style compliant are as follows:
- Helicopter
- Human

## Final Submission

Before submitting, make sure that...
- Your code compiles and runs from a clean directory.
   - `make clean; make -j`
- Appropriate Doxygen documentation is generated with `make docs`
- You have NO CPP lint errors from `make lint` Updated instructions for CPPLint can be found [here](https://github.umn.edu/umn-csci-3081w-f24-sec010/FAQ/tree/main/VSCode%20CPPLint): 

To submit your lab:

1. Create a pull request from your development branch into your main branch.

   [FAQ: How to Create a Pull Request on Github](https://github.umn.edu/umn-csci-3081w-f24-sec010/FAQ/tree/main/Github%20Pull%20Requests)
   
   **JUST LIKE LAST WEEK, DO NOT MERGE THE PULL REQUEST.  LEAVE IT OPEN.**

1. Get the latest commit ID from your development branch and submit it to the Gradescope  assignment "Lab06: Import Assets" your personal repo link and the final commit ID for your submission.  Do not merge the pull request; you only need to submit the commit ID.

   [FAQ: How to get a commit ID](https://github.umn.edu/umn-csci-3081w-f24-sec010/FAQ/blob/main/Commit%20ID/README.md)

Once you have done both steps above, you have completed the lab.
