##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Release
ProjectName            :=SSVStart
ConfigurationName      :=Release
WorkspacePath          := "D:\Vee\Software\GitHub\OHWorkspace"
ProjectPath            := "D:\Vee\Software\GitHub\OHWorkspace\SSVStart"
IntermediateDirectory  :=./Release
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=Vittorio
Date                   :=09/02/2013
CodeLitePath           :="C:\Program Files (x86)\CodeLite"
LinkerName             :=g++
SharedObjectLinkerName :=g++ -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.o.i
DebugSwitch            :=-gstab
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
OutputFile             :=$(IntermediateDirectory)/$(ProjectName).dll
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E 
ObjectsFileList        :="SSVStart.txt"
PCHCompileFlags        :=
MakeDirCommand         :=makedir
RcCmpOptions           := 
RcCompilerName         :=windres
LinkOptions            :=  -shared
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). $(IncludeSwitch)D:/Vee/Software/GitHub/OHWorkspace/SFML/include 
IncludePCH             := 
RcIncludePath          := 
Libs                   := $(LibrarySwitch)sfml-system $(LibrarySwitch)sfml-window $(LibrarySwitch)sfml-audio $(LibrarySwitch)sfml-graphics 
ArLibs                 :=  "sfml-system" "sfml-window" "sfml-audio" "sfml-graphics" 
LibPath                := $(LibraryPathSwitch). $(LibraryPathSwitch)../SSVStart/Release $(LibraryPathSwitch)../SSVEntitySystem/Release $(LibraryPathSwitch)../SSVLuaWrapper/Release $(LibraryPathSwitch)./Release $(LibraryPathSwitch)D:/Vee/Software/GitHub/OHWorkspace/SFML/build2/lib $(LibraryPathSwitch)D:/Vee/Software/GitHub/OHWorkspace/jsoncpp/libs/mingw $(LibraryPathSwitch)c:/lua 

##
## Common variables
## AR, CXX, CC, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := ar rcus
CXX      := g++
CC       := gcc
CXXFLAGS :=  -W -pedantic -O3 -Wextra -std=c++11 -Wall $(Preprocessors)
CFLAGS   :=   $(Preprocessors)


##
## User defined environment variables
##
CodeLiteDir:=C:\Program Files (x86)\CodeLite
UNIT_TEST_PP_SRC_DIR:=C:\UnitTest++-1.3
Objects0=$(IntermediateDirectory)/GameSystem_GWProperties$(ObjectSuffix) $(IntermediateDirectory)/GameSystem_GameState$(ObjectSuffix) $(IntermediateDirectory)/GameSystem_GameWindow$(ObjectSuffix) $(IntermediateDirectory)/Timeline_Command$(ObjectSuffix) $(IntermediateDirectory)/Timeline_Do$(ObjectSuffix) $(IntermediateDirectory)/Timeline_Timeline$(ObjectSuffix) $(IntermediateDirectory)/Timeline_Wait$(ObjectSuffix) $(IntermediateDirectory)/Timeline_Go$(ObjectSuffix) $(IntermediateDirectory)/Utils_Utils$(ObjectSuffix) $(IntermediateDirectory)/Camera_Camera$(ObjectSuffix) \
	$(IntermediateDirectory)/Log_Log$(ObjectSuffix) $(IntermediateDirectory)/Assets_AssetManager$(ObjectSuffix) $(IntermediateDirectory)/Assets_AssetFolder$(ObjectSuffix) $(IntermediateDirectory)/FileSystem_FileSystem$(ObjectSuffix) $(IntermediateDirectory)/Input_InputManager$(ObjectSuffix) $(IntermediateDirectory)/Input_InputCombination$(ObjectSuffix) $(IntermediateDirectory)/Tileset$(ObjectSuffix) 

Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild
all: $(OutputFile)

$(OutputFile): $(IntermediateDirectory)/.d $(Objects) 
	@$(MakeDirCommand) $(@D)
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(SharedObjectLinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)
	@$(MakeDirCommand) "D:\Vee\Software\GitHub\OHWorkspace/.build-release"
	@echo rebuilt > "D:\Vee\Software\GitHub\OHWorkspace/.build-release/SSVStart"

$(IntermediateDirectory)/.d:
	@$(MakeDirCommand) "./Release"

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/GameSystem_GWProperties$(ObjectSuffix): GameSystem/GWProperties.cpp $(IntermediateDirectory)/GameSystem_GWProperties$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "D:/Vee/Software/GitHub/OHWorkspace/SSVStart/GameSystem/GWProperties.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/GameSystem_GWProperties$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/GameSystem_GWProperties$(DependSuffix): GameSystem/GWProperties.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/GameSystem_GWProperties$(ObjectSuffix) -MF$(IntermediateDirectory)/GameSystem_GWProperties$(DependSuffix) -MM "GameSystem/GWProperties.cpp"

$(IntermediateDirectory)/GameSystem_GWProperties$(PreprocessSuffix): GameSystem/GWProperties.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/GameSystem_GWProperties$(PreprocessSuffix) "GameSystem/GWProperties.cpp"

$(IntermediateDirectory)/GameSystem_GameState$(ObjectSuffix): GameSystem/GameState.cpp $(IntermediateDirectory)/GameSystem_GameState$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "D:/Vee/Software/GitHub/OHWorkspace/SSVStart/GameSystem/GameState.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/GameSystem_GameState$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/GameSystem_GameState$(DependSuffix): GameSystem/GameState.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/GameSystem_GameState$(ObjectSuffix) -MF$(IntermediateDirectory)/GameSystem_GameState$(DependSuffix) -MM "GameSystem/GameState.cpp"

$(IntermediateDirectory)/GameSystem_GameState$(PreprocessSuffix): GameSystem/GameState.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/GameSystem_GameState$(PreprocessSuffix) "GameSystem/GameState.cpp"

$(IntermediateDirectory)/GameSystem_GameWindow$(ObjectSuffix): GameSystem/GameWindow.cpp $(IntermediateDirectory)/GameSystem_GameWindow$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "D:/Vee/Software/GitHub/OHWorkspace/SSVStart/GameSystem/GameWindow.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/GameSystem_GameWindow$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/GameSystem_GameWindow$(DependSuffix): GameSystem/GameWindow.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/GameSystem_GameWindow$(ObjectSuffix) -MF$(IntermediateDirectory)/GameSystem_GameWindow$(DependSuffix) -MM "GameSystem/GameWindow.cpp"

$(IntermediateDirectory)/GameSystem_GameWindow$(PreprocessSuffix): GameSystem/GameWindow.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/GameSystem_GameWindow$(PreprocessSuffix) "GameSystem/GameWindow.cpp"

$(IntermediateDirectory)/Timeline_Command$(ObjectSuffix): Timeline/Command.cpp $(IntermediateDirectory)/Timeline_Command$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "D:/Vee/Software/GitHub/OHWorkspace/SSVStart/Timeline/Command.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Timeline_Command$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Timeline_Command$(DependSuffix): Timeline/Command.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Timeline_Command$(ObjectSuffix) -MF$(IntermediateDirectory)/Timeline_Command$(DependSuffix) -MM "Timeline/Command.cpp"

$(IntermediateDirectory)/Timeline_Command$(PreprocessSuffix): Timeline/Command.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Timeline_Command$(PreprocessSuffix) "Timeline/Command.cpp"

$(IntermediateDirectory)/Timeline_Do$(ObjectSuffix): Timeline/Do.cpp $(IntermediateDirectory)/Timeline_Do$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "D:/Vee/Software/GitHub/OHWorkspace/SSVStart/Timeline/Do.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Timeline_Do$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Timeline_Do$(DependSuffix): Timeline/Do.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Timeline_Do$(ObjectSuffix) -MF$(IntermediateDirectory)/Timeline_Do$(DependSuffix) -MM "Timeline/Do.cpp"

$(IntermediateDirectory)/Timeline_Do$(PreprocessSuffix): Timeline/Do.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Timeline_Do$(PreprocessSuffix) "Timeline/Do.cpp"

$(IntermediateDirectory)/Timeline_Timeline$(ObjectSuffix): Timeline/Timeline.cpp $(IntermediateDirectory)/Timeline_Timeline$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "D:/Vee/Software/GitHub/OHWorkspace/SSVStart/Timeline/Timeline.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Timeline_Timeline$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Timeline_Timeline$(DependSuffix): Timeline/Timeline.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Timeline_Timeline$(ObjectSuffix) -MF$(IntermediateDirectory)/Timeline_Timeline$(DependSuffix) -MM "Timeline/Timeline.cpp"

$(IntermediateDirectory)/Timeline_Timeline$(PreprocessSuffix): Timeline/Timeline.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Timeline_Timeline$(PreprocessSuffix) "Timeline/Timeline.cpp"

$(IntermediateDirectory)/Timeline_Wait$(ObjectSuffix): Timeline/Wait.cpp $(IntermediateDirectory)/Timeline_Wait$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "D:/Vee/Software/GitHub/OHWorkspace/SSVStart/Timeline/Wait.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Timeline_Wait$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Timeline_Wait$(DependSuffix): Timeline/Wait.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Timeline_Wait$(ObjectSuffix) -MF$(IntermediateDirectory)/Timeline_Wait$(DependSuffix) -MM "Timeline/Wait.cpp"

$(IntermediateDirectory)/Timeline_Wait$(PreprocessSuffix): Timeline/Wait.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Timeline_Wait$(PreprocessSuffix) "Timeline/Wait.cpp"

$(IntermediateDirectory)/Timeline_Go$(ObjectSuffix): Timeline/Go.cpp $(IntermediateDirectory)/Timeline_Go$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "D:/Vee/Software/GitHub/OHWorkspace/SSVStart/Timeline/Go.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Timeline_Go$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Timeline_Go$(DependSuffix): Timeline/Go.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Timeline_Go$(ObjectSuffix) -MF$(IntermediateDirectory)/Timeline_Go$(DependSuffix) -MM "Timeline/Go.cpp"

$(IntermediateDirectory)/Timeline_Go$(PreprocessSuffix): Timeline/Go.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Timeline_Go$(PreprocessSuffix) "Timeline/Go.cpp"

$(IntermediateDirectory)/Utils_Utils$(ObjectSuffix): Utils/Utils.cpp $(IntermediateDirectory)/Utils_Utils$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "D:/Vee/Software/GitHub/OHWorkspace/SSVStart/Utils/Utils.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Utils_Utils$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Utils_Utils$(DependSuffix): Utils/Utils.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Utils_Utils$(ObjectSuffix) -MF$(IntermediateDirectory)/Utils_Utils$(DependSuffix) -MM "Utils/Utils.cpp"

$(IntermediateDirectory)/Utils_Utils$(PreprocessSuffix): Utils/Utils.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Utils_Utils$(PreprocessSuffix) "Utils/Utils.cpp"

$(IntermediateDirectory)/Camera_Camera$(ObjectSuffix): Camera/Camera.cpp $(IntermediateDirectory)/Camera_Camera$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "D:/Vee/Software/GitHub/OHWorkspace/SSVStart/Camera/Camera.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Camera_Camera$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Camera_Camera$(DependSuffix): Camera/Camera.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Camera_Camera$(ObjectSuffix) -MF$(IntermediateDirectory)/Camera_Camera$(DependSuffix) -MM "Camera/Camera.cpp"

$(IntermediateDirectory)/Camera_Camera$(PreprocessSuffix): Camera/Camera.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Camera_Camera$(PreprocessSuffix) "Camera/Camera.cpp"

$(IntermediateDirectory)/Log_Log$(ObjectSuffix): Log/Log.cpp $(IntermediateDirectory)/Log_Log$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "D:/Vee/Software/GitHub/OHWorkspace/SSVStart/Log/Log.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Log_Log$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Log_Log$(DependSuffix): Log/Log.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Log_Log$(ObjectSuffix) -MF$(IntermediateDirectory)/Log_Log$(DependSuffix) -MM "Log/Log.cpp"

$(IntermediateDirectory)/Log_Log$(PreprocessSuffix): Log/Log.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Log_Log$(PreprocessSuffix) "Log/Log.cpp"

$(IntermediateDirectory)/Assets_AssetManager$(ObjectSuffix): Assets/AssetManager.cpp $(IntermediateDirectory)/Assets_AssetManager$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "D:/Vee/Software/GitHub/OHWorkspace/SSVStart/Assets/AssetManager.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Assets_AssetManager$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Assets_AssetManager$(DependSuffix): Assets/AssetManager.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Assets_AssetManager$(ObjectSuffix) -MF$(IntermediateDirectory)/Assets_AssetManager$(DependSuffix) -MM "Assets/AssetManager.cpp"

$(IntermediateDirectory)/Assets_AssetManager$(PreprocessSuffix): Assets/AssetManager.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Assets_AssetManager$(PreprocessSuffix) "Assets/AssetManager.cpp"

$(IntermediateDirectory)/Assets_AssetFolder$(ObjectSuffix): Assets/AssetFolder.cpp $(IntermediateDirectory)/Assets_AssetFolder$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "D:/Vee/Software/GitHub/OHWorkspace/SSVStart/Assets/AssetFolder.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Assets_AssetFolder$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Assets_AssetFolder$(DependSuffix): Assets/AssetFolder.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Assets_AssetFolder$(ObjectSuffix) -MF$(IntermediateDirectory)/Assets_AssetFolder$(DependSuffix) -MM "Assets/AssetFolder.cpp"

$(IntermediateDirectory)/Assets_AssetFolder$(PreprocessSuffix): Assets/AssetFolder.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Assets_AssetFolder$(PreprocessSuffix) "Assets/AssetFolder.cpp"

$(IntermediateDirectory)/FileSystem_FileSystem$(ObjectSuffix): FileSystem/FileSystem.cpp $(IntermediateDirectory)/FileSystem_FileSystem$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "D:/Vee/Software/GitHub/OHWorkspace/SSVStart/FileSystem/FileSystem.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/FileSystem_FileSystem$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/FileSystem_FileSystem$(DependSuffix): FileSystem/FileSystem.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/FileSystem_FileSystem$(ObjectSuffix) -MF$(IntermediateDirectory)/FileSystem_FileSystem$(DependSuffix) -MM "FileSystem/FileSystem.cpp"

$(IntermediateDirectory)/FileSystem_FileSystem$(PreprocessSuffix): FileSystem/FileSystem.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/FileSystem_FileSystem$(PreprocessSuffix) "FileSystem/FileSystem.cpp"

$(IntermediateDirectory)/Input_InputManager$(ObjectSuffix): Input/InputManager.cpp $(IntermediateDirectory)/Input_InputManager$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "D:/Vee/Software/GitHub/OHWorkspace/SSVStart/Input/InputManager.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Input_InputManager$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Input_InputManager$(DependSuffix): Input/InputManager.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Input_InputManager$(ObjectSuffix) -MF$(IntermediateDirectory)/Input_InputManager$(DependSuffix) -MM "Input/InputManager.cpp"

$(IntermediateDirectory)/Input_InputManager$(PreprocessSuffix): Input/InputManager.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Input_InputManager$(PreprocessSuffix) "Input/InputManager.cpp"

$(IntermediateDirectory)/Input_InputCombination$(ObjectSuffix): Input/InputCombination.cpp $(IntermediateDirectory)/Input_InputCombination$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "D:/Vee/Software/GitHub/OHWorkspace/SSVStart/Input/InputCombination.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Input_InputCombination$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Input_InputCombination$(DependSuffix): Input/InputCombination.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Input_InputCombination$(ObjectSuffix) -MF$(IntermediateDirectory)/Input_InputCombination$(DependSuffix) -MM "Input/InputCombination.cpp"

$(IntermediateDirectory)/Input_InputCombination$(PreprocessSuffix): Input/InputCombination.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Input_InputCombination$(PreprocessSuffix) "Input/InputCombination.cpp"

$(IntermediateDirectory)/Tileset$(ObjectSuffix): Tileset.cpp $(IntermediateDirectory)/Tileset$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "D:/Vee/Software/GitHub/OHWorkspace/SSVStart/Tileset.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Tileset$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Tileset$(DependSuffix): Tileset.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Tileset$(ObjectSuffix) -MF$(IntermediateDirectory)/Tileset$(DependSuffix) -MM "Tileset.cpp"

$(IntermediateDirectory)/Tileset$(PreprocessSuffix): Tileset.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Tileset$(PreprocessSuffix) "Tileset.cpp"


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) $(IntermediateDirectory)/GameSystem_GWProperties$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/GameSystem_GWProperties$(DependSuffix)
	$(RM) $(IntermediateDirectory)/GameSystem_GWProperties$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/GameSystem_GameState$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/GameSystem_GameState$(DependSuffix)
	$(RM) $(IntermediateDirectory)/GameSystem_GameState$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/GameSystem_GameWindow$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/GameSystem_GameWindow$(DependSuffix)
	$(RM) $(IntermediateDirectory)/GameSystem_GameWindow$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/Timeline_Command$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Timeline_Command$(DependSuffix)
	$(RM) $(IntermediateDirectory)/Timeline_Command$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/Timeline_Do$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Timeline_Do$(DependSuffix)
	$(RM) $(IntermediateDirectory)/Timeline_Do$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/Timeline_Timeline$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Timeline_Timeline$(DependSuffix)
	$(RM) $(IntermediateDirectory)/Timeline_Timeline$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/Timeline_Wait$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Timeline_Wait$(DependSuffix)
	$(RM) $(IntermediateDirectory)/Timeline_Wait$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/Timeline_Go$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Timeline_Go$(DependSuffix)
	$(RM) $(IntermediateDirectory)/Timeline_Go$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/Utils_Utils$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Utils_Utils$(DependSuffix)
	$(RM) $(IntermediateDirectory)/Utils_Utils$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/Camera_Camera$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Camera_Camera$(DependSuffix)
	$(RM) $(IntermediateDirectory)/Camera_Camera$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/Log_Log$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Log_Log$(DependSuffix)
	$(RM) $(IntermediateDirectory)/Log_Log$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/Assets_AssetManager$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Assets_AssetManager$(DependSuffix)
	$(RM) $(IntermediateDirectory)/Assets_AssetManager$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/Assets_AssetFolder$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Assets_AssetFolder$(DependSuffix)
	$(RM) $(IntermediateDirectory)/Assets_AssetFolder$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/FileSystem_FileSystem$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/FileSystem_FileSystem$(DependSuffix)
	$(RM) $(IntermediateDirectory)/FileSystem_FileSystem$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/Input_InputManager$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Input_InputManager$(DependSuffix)
	$(RM) $(IntermediateDirectory)/Input_InputManager$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/Input_InputCombination$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Input_InputCombination$(DependSuffix)
	$(RM) $(IntermediateDirectory)/Input_InputCombination$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/Tileset$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Tileset$(DependSuffix)
	$(RM) $(IntermediateDirectory)/Tileset$(PreprocessSuffix)
	$(RM) $(OutputFile)
	$(RM) $(OutputFile)
	$(RM) "../.build-release/SSVStart"


