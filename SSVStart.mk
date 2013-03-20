##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Release
ProjectName            :=SSVStart
ConfigurationName      :=Release
WorkspacePath          := "D:\Vee\Software\GitHub\OHWorkspace"
ProjectPath            := "D:\Vee\Software\GitHub\OHWorkspace\SSVStart"
IntermediateDirectory  :=./_INTERMEDIATE
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=vittorio.romeo
Date                   :=20/03/2013
CodeLitePath           :="C:\Program Files (x86)\CodeLite"
LinkerName             :=g++
SharedObjectLinkerName :=g++ -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.o.i
DebugSwitch            :=-g 
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
OutputFile             :=./_RELEASE/$(ProjectName).dll
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E
ObjectsFileList        :="SSVStart.txt"
PCHCompileFlags        :=
MakeDirCommand         :=makedir
RcCmpOptions           := 
RcCompilerName         :=windres
LinkOptions            :=  
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch)../SSVUtils/include $(IncludeSwitch)../SFML/include $(IncludeSwitch)D:/Vee/Software/Repos/sparsehash/build/built/include $(IncludeSwitch)../jsoncpp/include 
IncludePCH             := 
RcIncludePath          := 
Libs                   := $(LibrarySwitch)SSVUtils $(LibrarySwitch)sfml-system $(LibrarySwitch)sfml-window $(LibrarySwitch)sfml-audio $(LibrarySwitch)sfml-graphics $(LibrarySwitch)sfml-network 
ArLibs                 :=  "SSVUtils" "sfml-system" "sfml-window" "sfml-audio" "sfml-graphics" "sfml-network" 
LibPath                := $(LibraryPathSwitch). $(LibraryPathSwitch)../SSVUtils/_RELEASE $(LibraryPathSwitch)../SFML/build2/lib $(LibraryPathSwitch)c:/lua 

##
## Common variables
## AR, CXX, CC, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := ar rcus
CXX      := g++
CC       := gcc
CXXFLAGS :=  -W -s -pedantic -O3 -Wextra -std=c++11 -Wall $(Preprocessors)
CFLAGS   :=   $(Preprocessors)


##
## User defined environment variables
##
CodeLiteDir:=C:\Program Files (x86)\CodeLite
UNIT_TEST_PP_SRC_DIR:=C:\UnitTest++-1.3
WXWIN:=C:\wxWidgets-2.9.4
WXCFG:=gcc_dll\mswu
Objects0=$(IntermediateDirectory)/GameSystem_GWProperties$(ObjectSuffix) $(IntermediateDirectory)/GameSystem_GameState$(ObjectSuffix) $(IntermediateDirectory)/GameSystem_GameWindow$(ObjectSuffix) $(IntermediateDirectory)/Utils_Utils$(ObjectSuffix) $(IntermediateDirectory)/Camera_Camera$(ObjectSuffix) $(IntermediateDirectory)/Assets_AssetManager$(ObjectSuffix) $(IntermediateDirectory)/Assets_AssetFolder$(ObjectSuffix) $(IntermediateDirectory)/Input_Trigger$(ObjectSuffix) $(IntermediateDirectory)/Input_Combo$(ObjectSuffix) $(IntermediateDirectory)/Input_Manager$(ObjectSuffix) \
	$(IntermediateDirectory)/Tileset_Tileset$(ObjectSuffix) 

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
	$(SharedObjectLinkerName) $(OutputSwitch)$(OutputFile) $(Objects) $(LibPath) $(Libs) $(LinkOptions)
	@$(MakeDirCommand) "D:\Vee\Software\GitHub\OHWorkspace/.build-release"
	@echo rebuilt > "D:\Vee\Software\GitHub\OHWorkspace/.build-release/SSVStart"

$(IntermediateDirectory)/.d:
	@$(MakeDirCommand) "./_INTERMEDIATE"

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

$(IntermediateDirectory)/Input_Trigger$(ObjectSuffix): Input/Trigger.cpp $(IntermediateDirectory)/Input_Trigger$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "D:/Vee/Software/GitHub/OHWorkspace/SSVStart/Input/Trigger.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Input_Trigger$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Input_Trigger$(DependSuffix): Input/Trigger.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Input_Trigger$(ObjectSuffix) -MF$(IntermediateDirectory)/Input_Trigger$(DependSuffix) -MM "Input/Trigger.cpp"

$(IntermediateDirectory)/Input_Trigger$(PreprocessSuffix): Input/Trigger.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Input_Trigger$(PreprocessSuffix) "Input/Trigger.cpp"

$(IntermediateDirectory)/Input_Combo$(ObjectSuffix): Input/Combo.cpp $(IntermediateDirectory)/Input_Combo$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "D:/Vee/Software/GitHub/OHWorkspace/SSVStart/Input/Combo.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Input_Combo$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Input_Combo$(DependSuffix): Input/Combo.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Input_Combo$(ObjectSuffix) -MF$(IntermediateDirectory)/Input_Combo$(DependSuffix) -MM "Input/Combo.cpp"

$(IntermediateDirectory)/Input_Combo$(PreprocessSuffix): Input/Combo.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Input_Combo$(PreprocessSuffix) "Input/Combo.cpp"

$(IntermediateDirectory)/Input_Manager$(ObjectSuffix): Input/Manager.cpp $(IntermediateDirectory)/Input_Manager$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "D:/Vee/Software/GitHub/OHWorkspace/SSVStart/Input/Manager.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Input_Manager$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Input_Manager$(DependSuffix): Input/Manager.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Input_Manager$(ObjectSuffix) -MF$(IntermediateDirectory)/Input_Manager$(DependSuffix) -MM "Input/Manager.cpp"

$(IntermediateDirectory)/Input_Manager$(PreprocessSuffix): Input/Manager.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Input_Manager$(PreprocessSuffix) "Input/Manager.cpp"

$(IntermediateDirectory)/Tileset_Tileset$(ObjectSuffix): Tileset/Tileset.cpp $(IntermediateDirectory)/Tileset_Tileset$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "D:/Vee/Software/GitHub/OHWorkspace/SSVStart/Tileset/Tileset.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Tileset_Tileset$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Tileset_Tileset$(DependSuffix): Tileset/Tileset.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Tileset_Tileset$(ObjectSuffix) -MF$(IntermediateDirectory)/Tileset_Tileset$(DependSuffix) -MM "Tileset/Tileset.cpp"

$(IntermediateDirectory)/Tileset_Tileset$(PreprocessSuffix): Tileset/Tileset.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Tileset_Tileset$(PreprocessSuffix) "Tileset/Tileset.cpp"


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
	$(RM) $(IntermediateDirectory)/Utils_Utils$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Utils_Utils$(DependSuffix)
	$(RM) $(IntermediateDirectory)/Utils_Utils$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/Camera_Camera$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Camera_Camera$(DependSuffix)
	$(RM) $(IntermediateDirectory)/Camera_Camera$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/Assets_AssetManager$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Assets_AssetManager$(DependSuffix)
	$(RM) $(IntermediateDirectory)/Assets_AssetManager$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/Assets_AssetFolder$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Assets_AssetFolder$(DependSuffix)
	$(RM) $(IntermediateDirectory)/Assets_AssetFolder$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/Input_Trigger$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Input_Trigger$(DependSuffix)
	$(RM) $(IntermediateDirectory)/Input_Trigger$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/Input_Combo$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Input_Combo$(DependSuffix)
	$(RM) $(IntermediateDirectory)/Input_Combo$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/Input_Manager$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Input_Manager$(DependSuffix)
	$(RM) $(IntermediateDirectory)/Input_Manager$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/Tileset_Tileset$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Tileset_Tileset$(DependSuffix)
	$(RM) $(IntermediateDirectory)/Tileset_Tileset$(PreprocessSuffix)
	$(RM) $(OutputFile)
	$(RM) $(OutputFile)
	$(RM) "../.build-release/SSVStart"


