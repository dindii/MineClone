# MineClone

Learning purposes project.

-------------------
 @-The Minecraft map clone is in the src folder inside SandBox folder. 

 @-Images and videos below.

-------------------
Briefing:
  This kind of framework was made in order to make a Minecraft map clone, therefore, the tools were implemented to accomplish this goal. 

  The idea was to make a program where the user can easily set (render, maybe?) a block and this block would be spawned with all optimizations (bit packing, greedy algorithm           meshing,   culling etc) but letting a lot of stuff to the user, thus, giving it a finer granularity.

  This program has two minor bugs (chunk divisions and greedy meshing) that i would love to fix it but unfortunately i want to study the graphics area and this project would take     some   time to start the graphics part and it would not have room for a lot of techniques, that's why i'm also stopping the development of it for now.

-------------------
Features:
  Greedy Meshing Algorithm. (naive approach, it really needs a remake more related to the articles)
  
  Texture, Normals, Postions and data for texture tilling factor are all packed, thus leading at 4 bytes per vertex.
  
  Easy to set a voxel with texture, to make a terrain using noise, to remove or place blocks using Trace functions etc.
  
  Clean user workflow.
  
  Easy to add ImGui code for debugging or so.
  
-------------------
Compatibility:

  Windows/OpenGL

-------------------

Dependencies: 
  Glad,
  
  Imgui,
  
  stbi.

-------------------
HOW TO BUILD:

  For now, you just need to have premake (https://github.com/premake/premake-core) and execute premake5.exe with your configuration. 

  e.g in a .bat file for visual studio 2017: call vendor\bin\premake\premake5.exe vs2017

-------------------
Controls:
  
  F1 - Wireframe mode
  
  F2 - Lock/Unlock mouse
  
-------------------

IMAGES:
![The greedy is applied to the whole terrain](https://i.imgur.com/UWpI43O.png)

![Two types of voxels using greedy](https://i.imgur.com/BgL1c8g.png)

![Greedy rearranging after block removed](https://i.imgur.com/mGiRmv3.png)

-------------------
VIDEOS:

[![Minecraft Terrain Clone Overview](http://img.youtube.com/vi/9Lc9JFJrxwg/0.jpg)](http://www.youtube.com/watch?v=9Lc9JFJrxwg "Minecraft Terrain Clone Overview")

[![Minecraft Terrain Clone Overview](http://img.youtube.com/vi/mjCKv8ObIYM/0.jpg)](http://www.youtube.com/watch?v=mjCKv8ObIYM "Minecraft Terrain Clone Overview")
