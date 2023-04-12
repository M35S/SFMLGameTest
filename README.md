# SFMLGame - Side Scrolling Shooter

## Contents
- Classes: Relationships
- Classes: Individual View
- Classes: Object View
- Data Structures: Containers Used
- Data Structure: Vector
- Data Structure: Map
- Program Flow: Application Start
- Program Flow: Gameplay Loop
- Program Flow: Time Per Frame (Delta Time)
- Processes: Animation Setup
- Processes: Controls Setup
- Maths: Enemy Motion Types

![gameplayPic.png](https://github.com/M35S/SFMLGameTest/blob/main/SFML%20Github%20images/gameplayPic.png)

This was one of 2D games I worked on during my time at university. I decided to revisit this project and break it down to see how everything works together.

## Classes: Relationships

Below is a UML class diagram that sums up the game's main classes:

![classRelationshipDiagram.png](https://github.com/M35S/SFMLGameTest/blob/main/SFML%20Github%20images/classRelationshipDiagram.PNG)

Just to refresh what each relationship stands for:
- Inheritance: Is a kind of... 
- Aggregation: Has a reference of...
- Composition: Consists of...
- Association: Is associated with...
- Directed Association: Is an input to...

For the most part, our class relationship diagram mainly consists of compositions & directed associations.

## Classes: Individual View

One of the many classes used is the Player class. Below is a UML class view table:

![playerClass.png](https://github.com/M35S/SFMLGameTest/blob/main/SFML%20Github%20images/playerClass.PNG)

## Classes: Object View

We can go into more detail of what values each member stores. This can be visualised like this:

![playerInstance1.png](https://github.com/M35S/SFMLGameTest/blob/main/SFML%20Github%20images/playerInstance1.PNG)

![playerInstance2.png](https://github.com/M35S/SFMLGameTest/blob/main/SFML%20Github%20images/playerInstance2.PNG)

Doing this means we can exactly see what each class / data structure holds.

## Data Structures : Containers Used

This project uses C++'s containers such as:
- Vectors: Used for containing game objects such as Players, Enemies, Bullets & Background (for parallax images).
- Maps: Used for containing the game's resources (e.g. fonts, sprites & colours).

### Data Structure: Vector
Vector's are a popular choice for good reasons such as:
- Number crunching: Good for removing & adding the last element as well as sorting.
- Fast iteration: Fast for linear searching from beginning to end.
- Dynamic resizing: Unlike standard arrays, vectors can shrink & increase memory size.

The cons however are:
- Reallocation: Can be an expensive operation.
- Large-scale data: Performance takes a toll, performs better with small data.

#### Suitable choices
As we never know how many bullets the player will fire, a vector is a good container to use. 

![bulletVectContainer.png](https://github.com/M35S/SFMLGameTest/blob/main/SFML%20Github%20images/bulletVectContainer.PNG)

### Data Structure: Map
It is best to use Maps for:
- Data access: Fast access to the values using keys.
- Ordered: Each element is uniquely key ordered.

However, the cons are:
- Large-scale iteration: Traversing to every element from beginning to end is time consuming. 

#### Suitable choices
With the above in mind, searching for a resource value such as a text font or sprite texture (i.e. value) can be done using enums (i.e. key).

![spriteResourceInstance.png](https://github.com/M35S/SFMLGameTest/blob/main/SFML%20Github%20images/spriteResourceInstance.PNG)

![spriteFontInstance.png](https://github.com/M35S/SFMLGameTest/blob/main/SFML%20Github%20images/spriteFontInstance.PNG)

## Program Flow: Application Start
As well as having a grasp of the game's data structures, it is important to know the flow of the program. 
To do this, I designed a call graph diagram that illustrates what happens with certain pre & post conditions:

![callGraphFlowDiagram.png](https://github.com/M35S/SFMLGameTest/blob/main/SFML%20Github%20images/callGraphFlowDiagram.PNG)

Producing these diagrams has enabled me to understand the current stack view of the game. 

So as you can see, "game_t" is an object of "Game" from the file "Game.cpp". 
Within "game_t", we have it's members "settings_m" and "gameWorld_m". 
Again, we can see that "gameWorld_m" is an object of "GameState" from the file "GameState.cpp" that also contains the member "cameraControl_m".

## Program Flow: Gameplay Loop

![gameLoopFlow.png](https://github.com/M35S/SFMLGameTest/blob/main/SFML%20Github%20images/gameLoopFlow.PNG)

### Initialise function

We set the game window's name, dimensions (width & height) and mode type (full-screen / windowed). 

### Load Content function

First, we enter the "Create" function. It is here that the game world's data such as gameplay's score, time & lives are set up. Next, the game world's bounds are stored for help setting up the HUD locations as well as the game's camera target area. Finally, the game's assets are stored into the map container; that is the font types, sprite sheets & colour indexes. Here, the background sprite is added to the vector container and the HUD is created. 

Second, we enter the "Setup Player" function. Everything about the Player avatar is set up here; the x & y position, sprite sheet animation frames, scale size and mapped controls. All of these Player's data attributes are then passed into the vector container. 

Third, we enter the "Setup Aliens" function. Similar to the Player avatar, all alien's data attributes are setup with one exception; the input controls, which are Player specific. After the alien's data attributes are setup, each alien enemy is passed into the vector container. Lastly, each alien is assigned a motion type; linear, circular, sinusoidal & quadratic. This will be detailed later on. 

### Handle Events function

Here is our first visited method within the main gameplay loop. It is here we poll for Keyboard Key pressed events. 

### Update function

Next, after handling input events we update game objects such as Players, Enemies, Bullets, Background & HUD. We also process any logic based collision detections and perform any cleanup for redundant or no longer visible game objects such as dead enemies and parallax scrolling. 

### Render function

Last but not least is drawing all of our game objects to the screen. We firstly clear the buffer, then we go through all of the visible game objects and draw them onto our gameplay screen. 

After rendering our game objects, we then repeat the looping process again from "Handle Events" function. 

## Program Flow: Time Per Frame, TPF (Delta Time)

![deltaTimeDiagram.png](https://github.com/M35S/SFMLGameTest/blob/main/SFML%20Github%20images/deltaTimeDiagram.PNG)

One of the important concepts to be at least aware of is the TPF. This helps keep everything in sync with the game's frame rate such as the sprite animations & calculating positions. In the above picture, we have t1, t2 & t3; all of these are frames. In between say t1 & t2 is the TPF. In most game loops the TPF is incorporated, see the below code snippet:

```
previousTime = clock.restart();      // t1
while( window_is_open )
      totalTime = getElapsedTime();      // t2
      timePerFrame = totalTime - previousTime      // t2 - t1
      previousTime = getElapsedTime();      // t1 = t2
      
      ...
      update( timePerFrame );      // t2 i.e. delta time
      ...
```

Essentially what we are doing is finding the difference between t2 & t1. We are then using t2 (i.e. TPF) for use in our sprite animations and mathematical calculations (which will be discussed later). 

## Processes: Animation Setup

![addFrameProcess.png](https://github.com/M35S/SFMLGameTest/blob/main/SFML%20Github%20images/addFrameProcess.PNG)

During the "Setup Player" we mentioned setting up the Player sprite's animated frames. Within the "Add Frame" function we are storing the rectangle dimensions of each sprite's animated frame. These are pushed into the vector container. 

## Processes: Controls Setup

Below, we set up the camera's control scheme using actions & flags. The map container type is used to store these actions & flags. In a map container, we have a pair of attributes; a key value and a mapped value. With a map, like any container, we can store data. Accessing these mapped values can be done using the key value. 

![actionsMapView.png](https://github.com/M35S/SFMLGameTest/blob/main/SFML%20Github%20images/actionsMapView.PNG)

In the actions data member, for the Keyboard Key we use SFML's Keyboard data type. For the Camera Action, we use our enum data type which is used for the flags data member. In short, the key value = Keyboard Key & the mapped value = enum.

![flagsMapView.png](https://github.com/M35S/SFMLGameTest/blob/main/SFML%20Github%20images/flagsMapView.PNG)

In the flags data member, as mentioned earlier our enum type is used. For the other type, we use the boolean type. Note that all of the boolean values are set to false, meaning the camera action key has not be triggered. So, our key value = enum & the mapped value = boolean. 

![actionsFlagsMapView.png](https://github.com/M35S/SFMLGameTest/blob/main/SFML%20Github%20images/actionsFlagsMapView.PNG)

When we put these actions and flags together, we get this whole control scheme concept. Lets quickly go over a pre & post condition. 

#### Pre-Condition: We press the "A" Keyboard Key.
#### Post-Condition: We move the game's camera to the left.
#### Process Flow: Game::handleEvents()->Game::handleInput() ... 
#### Process Flow: Game::update(tpf)->GameState::update(tpf, ttotal)

Within the "Handle Events" function, we poll for any key pressed events which then takes us to the "Handle Input" function. Then, within the "Set Flag" we search our map container type "actions" member for the keyboard key pressed (i.e. key value). Once the key value has been found, we then refer to our map container type "flags" member returning the enum action type (again, key value) and then set the boolean value to true (the mapped value). This signals that the camera control action has been recognised. Next, we eventually lead into GameState's "Update" function, it is here we check map container's "flags" member for any true boolean values. Any value that is true means we change the camera's position value; in this case, we set camera's x coordinate value to a minus value (e.g. cameraGame.Move( -200 * tpf ) ).

## Maths: Enemy Motion Types

With all of the below motion types, with our calculations we must include the delta time (i.e. TPF). This is a key variable where it helps keep all animations and calculations in sync with the game's frame rate. 

### Linear Motion Type

![linearMotion.png](https://github.com/M35S/SFMLGameTest/blob/main/SFML%20Github%20images/linearMotion.PNG)

Enemies move in a straight line by simply using the following vector addition formula;

```
Vx' = Vx + Tx
```

Where 

```
Vx' = New vector x position
Vx = Current vector x position
Tx = Translation vector x
```

Note: Since this is a real-time application, we need our values to change as time progresses. This is where we add the TPF value within our calculations. Now we know about calculating the x coordinate, should we wish to calculate the y coordinate to implement a slope, we can use the linear equation formula y = mx + b.

Example: y = 2x + 1

![linearGraph1.png](https://github.com/M35S/SFMLGameTest/blob/main/SFML%20Github%20images/linearGraph1.PNG)

|    x   |    y   |
| ------ | ------ |
|   -1   |    -1  |
|   0    |    1   |
|   1    |    3   |
|   2    |    5   |
|   3    |    7   |

Example: y = 2 - (x / 2)

![linearGraph2.png](https://github.com/M35S/SFMLGameTest/blob/main/SFML%20Github%20images/linearGraph2.PNG)

|    x   |    y   |
| ------ | ------ |
|   -2   |    3   |
|   -1   |    2.5 |
|   0    |    2   |
|   1    |    1.5 |
|   2    |    1   |

Note: If we want a steeper slope, y needs a bigger value change per iteration. If we want a slighty steeper slope, y needs to have a smaller value change per iteration. 

### Circular Motion Type

![circularMotion.png](https://github.com/M35S/SFMLGameTest/blob/main/SFML%20Github%20images/circularMotion.PNG)

Enemies move in a circular pattern by simply using the following sine & cosine formulas;

```
Vx = cos( theta ) * Vr
Vy = sin( theta ) * Vr
```

Where

```
Vx = Vector x component
Vy = Vector y component
theta = angle
Vr = Vector's radius
```

![circularDiagram2.png](https://github.com/M35S/SFMLGameTest/blob/main/SFML%20Github%20images/circularDiagram2.PNG)

Note: radius in the above diagram = 1.

Lets go over an example:

Example: 
x = cos( degrees ) * radius and 
y = sin( degrees ) * radius

Where 

radius = 1

|    x           |    y           |
| -------------- | -------------- |
|   0 = 1        |    0 = 0       |
|   45 = 0.7     |    45 = 0.7.   |
|   90 = 0       |    90 = 1      |
|   135 = -0.7   |    135 = 0.7.  |
|   180 = -1     |    180 = 0     |
|   225 = -0.7   |    225 = -0.7  |
|   270 = 0      |    270 = -1    |
|   315 = 0.7    |    315 = -0.7  |
|   360 = 1      |    360 = 0     |

### Sinusoidal Motion Type

![sinusoidalMotion.png](https://github.com/M35S/SFMLGameTest/blob/main/SFML%20Github%20images/sinusoidalMotion.PNG)

sdfsdfds

### Quadratic Motion Type

![quadraticMotion.png](https://github.com/M35S/SFMLGameTest/blob/main/SFML%20Github%20images/quadraticMotion.PNG)

sdfsdfs
