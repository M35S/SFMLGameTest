# SFMLGame - Side Scrolling Shooter
![gameplayPic.PNG](https://github.com/M35S/SFMLGameTest/tree/main/SFML%20Github%20images/gameplayPic.PNG)
This was one of 2D games I worked on during my time at university. I decided to revisit this project and break it down to see how everything works together.

Below is a UML class diagram that sums up the game's main classes:
![classRelationshipDiagram.PNG](https://github.com/M35S/SFMLGameTest/tree/main/SFML%20Github%20images/classRelationshipDiagram.PNG)

This project uses C++'s containers such as:
- Vectors: Used for containing game objects such as Players, Enemies, Bullets & Background (for parallax images).
- Maps: Used for containing the game's resources (e.g. fonts, sprites & colours).

## Data Structures : Containers

### Vector
Vector's are a popular choice for good reasons such as:
- Number crunching: Good for removing & adding the last element as well as sorting.
- Fast iteration: Fast for linear searching from beginning to end.
- Dynamic resizing: Unlike standard arrays, vectors can shrink & increase memory size.

The cons however are:
- Reallocation: Can be an expensive operation.
- Large-scale data: Performance takes a toll, performs better with small data.

#### Suitable choices
As we never know how many bullets the player will fire, a vector is a good container to use. 

### Map
It is best to use Maps for:
- Data access: Fast access to the values using keys.
- Ordered: Each element is uniquely key ordered.

However, the cons are:
- Large-scale iteration: Traversing to every element from beginning to end is time consuming. 

#### Suitable choices
With the above in mind, searching for a resource value such as a text font or sprite texture (i.e. value) can be done using enums (i.e. key).

## Data Structures : Classes
One of the many classes used is the Player class. Below is a UML class view table:
![playerClass.PNG](https://github.com/M35S/SFMLGameTest/tree/main/SFML%20Github%20images/playerClass.PNG)
We can go into more detail of what values each member stores. This can be visualised like this:
![playerInstance1.PNG](https://github.com/M35S/SFMLGameTest/tree/main/SFML%20Github%20images/playerInstance1.PNG)
![playerInstance2.PNG](https://github.com/M35S/SFMLGameTest/tree/main/SFML%20Github%20images/playerInstance2.PNG)
Doing this means we can exactly see what each class / data structure holds. 

## Program Flow
As well as having a grasp of the game's data structures, it is important to know the flow of the program. 
To do this, I designed a call graph diagram that illustrates what happens with certain pre & post conditions:
![callGraphFlowDiagram.PNG](https://github.com/M35S/SFMLGameTest/tree/main/SFML%20Github%20images/callGraphFlowDiagram.PNG)
Producing these diagrams has enabled me to understand the current stack view of the game. 

So as you can see, "game_t" is an object of "Game" from the file "Game.cpp". 
Within "game_t", we have it's members "settings_m" and "gameWorld_m". 
Again, we can see that "gameWorld_m" is an object of "GameState" from the file "GameState.cpp" that also contains the member "cameraControl_m".
