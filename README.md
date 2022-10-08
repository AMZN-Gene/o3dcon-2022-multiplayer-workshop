# o3dcon-2022-multiplayer-workshop
A repository with code to complement 2022 O3DCon Multiplayer Workspace

Multiplayer Workshop Walkthrough:
This walkthrough will roughly outline each step of the process in making this multiplayer demo.
Each branch of this repository will have an updated README.md so that the code contained in the branch matches up to the last step of the walkthrough.

Step 1: Project creation using project template (20 minutes)
1. Create a new game called MyMultiplayerGame using Project Manager's Remote Template System
    a. Open Project Manager (Aka O3DE.exe)
    b. Select "New Project..." > "Create New Project"
    c. Click the "Add Remote Template Button" and provide the O3DE-extra's git URL: https://github.com/o3de/o3de-extras.git
    d. Select the Multiplayer Template and "Download Template"
    e. Once downloaded you can proceed to use Multiplayer Template to create a new game called "MyMultiplayerGame"
2. Compile using the "Build Now" option in Project Manager
3. Open Editor and let Asset Processor finish (this will take about 15 minutes)
4. Play around with the demo level
    a. Notice that pressing CTRL+G shows network connection status
    b. The server is automatically spawned and hidden by default, expose it by setting cvars:
        i. editorsv_hidden false 
        ii. editorsv_rhi_override ""
    c. The Editor CTRL+G experience can only spawn one player. Try spawning multiple players, by spawning a server and 2 clients by hand
        i. Use the cmd files at the root of your project. launch_server.cmd (1x) and launch_client.cmd (2x) 

Step 2: Create a new mutliplayer component
1. Create a new Multiplayer Component under Gem/Code/Source/AutoGen called O3DConPlayer.AutoComponent.xml
<?xml version="1.0"?>
<Component
    Name="O3DConPlayer" 
    Namespace="NewProject" 
    OverrideComponent="false"
    OverrideController="false" 
    OverrideInclude=""
    xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
    xsi:noNamespaceSchemaLocation="MultiplayerAutoComponentSchema.xsd">
    
    <NetworkInput Type="int" Name="ButtonsMashed" Init="0" />    
</Component>
2. Add the XML to Gem/Code/MyMultiplayerGame_files.cmake
3. Compile and open Editor

Step 3: Open Editor and make a new player
1. Open editor
2. Create a new level called O3DConLevel
3. Add a new entity called O3DConPlayer
4. Add our new multiplayer component O3DEConPlayer component
5. Add the missing required components
  a. Local Predicition Play Input
  b. Network Binding
6. Save out the O3DConPlayer prefab
7. Add at least 2 PlayerSpawner.prefabs to the level
8. CTRL+G and make sure the O3DConPlayer spawns
   Important Note: Use network.spawnable not .spawnables
9. Notice the player position is still at <0,0,0> and not where you've placed the PlayerSpawner
10. Add NetworkTransformComponent to O3DConPlayer.prefab and now the player position is fixed

Step 4: Adding a custom multiplayer controller code File
1. Update O3DConPlayer.AutoComponent.xml to enable custom controller logic
<Component
    Name="O3DConPlayer" 
    OverrideController="true" 
    OverrideInclude="Source/Components/O3DConPlayer.h"
    
2. Compile. Notice compiler error.
    Cannot open include file: 'Source/Components/O3DConPlayer.h': No such file or directory
    This is because we never made that file!
4. Open Visual Studio and find the generated multiplayer base class code
   a. Solution Explorer > Project.Static > GeneratedFiles > O3DConPlayer.AutoComponent.h
5. The generated auto-component comes with boilerplate code that's commented out for you to use inside of your new MyMultiplayerGame\Gem\Code\Source\Components\O3DConPlayer.cpp/.h files.
   a. Copy and paste the "Place in your .h" section and "Place in your .cpp" section into your .h and .cpp respectively
6. Update MyMultiplayerGame_files.cmake with the new .cpp/.h files
7. Compile successfully
