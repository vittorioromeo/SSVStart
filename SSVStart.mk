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
Date                   :=21/03/2013
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
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch)./include/ $(IncludeSwitch)../SSVUtils/include/ $(IncludeSwitch)../SFML/include/ $(IncludeSwitch)D:/Vee/Software/Repos/sparsehash/build/built/include/ $(IncludeSwitch)../jsoncpp/include/ 
IncludePCH             := 
RcIncludePath          := 
Libs                   := $(LibrarySwitch)SSVUtils $(LibrarySwitch)sfml-system $(LibrarySwitch)sfml-window $(LibrarySwitch)sfml-audio $(LibrarySwitch)sfml-graphics $(LibrarySwitch)sfml-network 
ArLibs                 :=  "SSVUtils" "sfml-system" "sfml-window" "sfml-audio" "sfml-graphics" "sfml-network" 
LibPath                := $(LibraryPathSwitch). $(LibraryPathSwitch)../SSVUtils/_RELEASE $(LibraryPathSwitch)../SFML/build2/lib 

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
Objects0=$(IntermediateDirectory)/GameSystem_GameState$(ObjectSuffix) $(IntermediateDirectory)/GameSystem_GameWindow$(ObjectSuffix) $(IntermediateDirectory)/GameSystem_GWProperties$(ObjectSuffix) $(IntermediateDirectory)/Utils_Utils$(ObjectSuffix) $(IntermediateDirectory)/Camera_Camera$(ObjectSuffix) $(IntermediateDirectory)/Assets_AssetFolder$(ObjectSuffix) $(IntermediateDirectory)/Assets_AssetManager$(ObjectSuffix) $(IntermediateDirectory)/Input_Combo$(ObjectSuffix) $(IntermediateDirectory)/Input_Manager$(ObjectSuffix) $(IntermediateDirectory)/Input_Trigger$(ObjectSuffix) \
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
$(IntermediateDirectory)/GameSystem_GameState$(ObjectSuffix): src/SSVStart/GameSystem/GameState.cpp $(IntermediateDirectory)/GameSystem_GameState$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "D:/Vee/Software/GitHub/OHWorkspace/SSVStart/src/SSVStart/GameSystem/GameState.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/GameSystem_GameState$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/GameSystem_GameState$(DependSuffix): src/SSVStart/GameSystem/GameState.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/GameSystem_GameState$(ObjectSuffix) -MF$(IntermediateDirectory)/GameSystem_GameState$(DependSuffix) -MM "src/SSVStart/GameSystem/GameState.cpp"

$(IntermediateDirectory)/GameSystem_GameState$(PreprocessSuffix): src/SSVStart/GameSystem/GameState.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/GameSystem_GameState$(PreprocessSuffix) "src/SSVStart/GameSystem/GameState.cpp"

$(IntermediateDirectory)/GameSystem_GameWindow$(ObjectSuffix): src/SSVStart/GameSystem/GameWindow.cpp $(IntermediateDirectory)/GameSystem_GameWindow$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "D:/Vee/Software/GitHub/OHWorkspace/SSVStart/src/SSVStart/GameSystem/GameWindow.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/GameSystem_GameWindow$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/GameSystem_GameWindow$(DependSuffix): src/SSVStart/GameSystem/GameWindow.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/GameSystem_GameWindow$(ObjectSuffix) -MF$(IntermediateDirectory)/GameSystem_GameWindow$(DependSuffix) -MM "src/SSVStart/GameSystem/GameWindow.cpp"

$(IntermediateDirectory)/GameSystem_GameWindow$(PreprocessSuffix): src/SSVStart/GameSystem/GameWindow.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/GameSystem_GameWindow$(PreprocessSuffix) "src/SSVStart/GameSystem/GameWindow.cpp"

$(IntermediateDirectory)/GameSystem_GWProperties$(ObjectSuffix): src/SSVStart/GameSystem/GWProperties.cpp $(IntermediateDirectory)/GameSystem_GWProperties$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "D:/Vee/Software/GitHub/OHWorkspace/SSVStart/src/SSVStart/GameSystem/GWProperties.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/GameSystem_GWProperties$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/GameSystem_GWProperties$(DependSuffix): src/SSVStart/GameSystem/GWProperties.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/GameSystem_GWProperties$(ObjectSuffix) -MF$(IntermediateDirectory)/GameSystem_GWProperties$(DependSuffix) -MM "src/SSVStart/GameSystem/GWProperties.cpp"

$(IntermediateDirectory)/GameSystem_GWProperties$(PreprocessSuffix): src/SSVStart/GameSystem/GWProperties.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/GameSystem_GWProperties$(PreprocessSuffix) "src/SSVStart/GameSystem/GWProperties.cpp"

$(IntermediateDirectory)/Utils_Utils$(ObjectSuffix): src/SSVStart/Utils/Utils.cpp $(IntermediateDirectory)/Utils_Utils$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "D:/Vee/Software/GitHub/OHWorkspace/SSVStart/src/SSVStart/Utils/Utils.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Utils_Utils$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Utils_Utils$(DependSuffix): src/SSVStart/Utils/Utils.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Utils_Utils$(ObjectSuffix) -MF$(IntermediateDirectory)/Utils_Utils$(DependSuffix) -MM "src/SSVStart/Utils/Utils.cpp"

$(IntermediateDirectory)/Utils_Utils$(PreprocessSuffix): src/SSVStart/Utils/Utils.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Utils_Utils$(PreprocessSuffix) "src/SSVStart/Utils/Utils.cpp"

$(IntermediateDirectory)/Camera_Camera$(ObjectSuffix): src/SSVStart/Camera/Camera.cpp $(IntermediateDirectory)/Camera_Camera$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "D:/Vee/Software/GitHub/OHWorkspace/SSVStart/src/SSVStart/Camera/Camera.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Camera_Camera$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Camera_Camera$(DependSuffix): src/SSVStart/Camera/Camera.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Camera_Camera$(ObjectSuffix) -MF$(IntermediateDirectory)/Camera_Camera$(DependSuffix) -MM "src/SSVStart/Camera/Camera.cpp"

$(IntermediateDirectory)/Camera_Camera$(PreprocessSuffix): src/SSVStart/Camera/Camera.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Camera_Camera$(PreprocessSuffix) "src/SSVStart/Camera/Camera.cpp"

$(IntermediateDirectory)/Assets_AssetFolder$(ObjectSuffix): src/SSVStart/Assets/AssetFolder.cpp $(IntermediateDirectory)/Assets_AssetFolder$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "D:/Vee/Software/GitHub/OHWorkspace/SSVStart/src/SSVStart/Assets/AssetFolder.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Assets_AssetFolder$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Assets_AssetFolder$(DependSuffix): src/SSVStart/Assets/AssetFolder.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Assets_AssetFolder$(ObjectSuffix) -MF$(IntermediateDirectory)/Assets_AssetFolder$(DependSuffix) -MM "src/SSVStart/Assets/AssetFolder.cpp"

$(IntermediateDirectory)/Assets_AssetFolder$(PreprocessSuffix): src/SSVStart/Assets/AssetFolder.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Assets_AssetFolder$(PreprocessSuffix) "src/SSVStart/Assets/AssetFolder.cpp"

$(IntermediateDirectory)/Assets_AssetManager$(ObjectSuffix): src/SSVStart/Assets/AssetManager.cpp $(IntermediateDirectory)/Assets_AssetManager$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "D:/Vee/Software/GitHub/OHWorkspace/SSVStart/src/SSVStart/Assets/AssetManager.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Assets_AssetManager$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Assets_AssetManager$(DependSuffix): src/SSVStart/Assets/AssetManager.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Assets_AssetManager$(ObjectSuffix) -MF$(IntermediateDirectory)/Assets_AssetManager$(DependSuffix) -MM "src/SSVStart/Assets/AssetManager.cpp"

$(IntermediateDirectory)/Assets_AssetManager$(PreprocessSuffix): src/SSVStart/Assets/AssetManager.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Assets_AssetManager$(PreprocessSuffix) "src/SSVStart/Assets/AssetManager.cpp"

$(IntermediateDirectory)/Input_Combo$(ObjectSuffix): src/SSVStart/Input/Combo.cpp $(IntermediateDirectory)/Input_Combo$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "D:/Vee/Software/GitHub/OHWorkspace/SSVStart/src/SSVStart/Input/Combo.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Input_Combo$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Input_Combo$(DependSuffix): src/SSVStart/Input/Combo.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Input_Combo$(ObjectSuffix) -MF$(IntermediateDirectory)/Input_Combo$(DependSuffix) -MM "src/SSVStart/Input/Combo.cpp"

$(IntermediateDirectory)/Input_Combo$(PreprocessSuffix): src/SSVStart/Input/Combo.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Input_Combo$(PreprocessSuffix) "src/SSVStart/Input/Combo.cpp"

$(IntermediateDirectory)/Input_Manager$(ObjectSuffix): src/SSVStart/Input/Manager.cpp $(IntermediateDirectory)/Input_Manager$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "D:/Vee/Software/GitHub/OHWorkspace/SSVStart/src/SSVStart/Input/Manager.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Input_Manager$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Input_Manager$(DependSuffix): src/SSVStart/Input/Manager.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Input_Manager$(ObjectSuffix) -MF$(IntermediateDirectory)/Input_Manager$(DependSuffix) -MM "src/SSVStart/Input/Manager.cpp"

$(IntermediateDirectory)/Input_Manager$(PreprocessSuffix): src/SSVStart/Input/Manager.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Input_Manager$(PreprocessSuffix) "src/SSVStart/Input/Manager.cpp"

$(IntermediateDirectory)/Input_Trigger$(ObjectSuffix): src/SSVStart/Input/Trigger.cpp $(IntermediateDirectory)/Input_Trigger$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "D:/Vee/Software/GitHub/OHWorkspace/SSVStart/src/SSVStart/Input/Trigger.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Input_Trigger$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Input_Trigger$(DependSuffix): src/SSVStart/Input/Trigger.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Input_Trigger$(ObjectSuffix) -MF$(IntermediateDirectory)/Input_Trigger$(DependSuffix) -MM "src/SSVStart/Input/Trigger.cpp"

$(IntermediateDirectory)/Input_Trigger$(PreprocessSuffix): src/SSVStart/Input/Trigger.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Input_Trigger$(PreprocessSuffix) "src/SSVStart/Input/Trigger.cpp"

$(IntermediateDirectory)/Tileset_Tileset$(ObjectSuffix): src/SSVStart/Tileset/Tileset.cpp $(IntermediateDirectory)/Tileset_Tileset$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "D:/Vee/Software/GitHub/OHWorkspace/SSVStart/src/SSVStart/Tileset/Tileset.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Tileset_Tileset$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Tileset_Tileset$(DependSuffix): src/SSVStart/Tileset/Tileset.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Tileset_Tileset$(ObjectSuffix) -MF$(IntermediateDirectory)/Tileset_Tileset$(DependSuffix) -MM "src/SSVStart/Tileset/Tileset.cpp"

$(IntermediateDirectory)/Tileset_Tileset$(PreprocessSuffix): src/SSVStart/Tileset/Tileset.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Tileset_Tileset$(PreprocessSuffix) "src/SSVStart/Tileset/Tileset.cpp"


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) $(IntermediateDirectory)/GameSystem_GameState$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/GameSystem_GameState$(DependSuffix)
	$(RM) $(IntermediateDirectory)/GameSystem_GameState$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/GameSystem_GameWindow$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/GameSystem_GameWindow$(DependSuffix)
	$(RM) $(IntermediateDirectory)/GameSystem_GameWindow$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/GameSystem_GWProperties$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/GameSystem_GWProperties$(DependSuffix)
	$(RM) $(IntermediateDirectory)/GameSystem_GWProperties$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/Utils_Utils$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Utils_Utils$(DependSuffix)
	$(RM) $(IntermediateDirectory)/Utils_Utils$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/Camera_Camera$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Camera_Camera$(DependSuffix)
	$(RM) $(IntermediateDirectory)/Camera_Camera$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/Assets_AssetFolder$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Assets_AssetFolder$(DependSuffix)
	$(RM) $(IntermediateDirectory)/Assets_AssetFolder$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/Assets_AssetManager$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Assets_AssetManager$(DependSuffix)
	$(RM) $(IntermediateDirectory)/Assets_AssetManager$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/Input_Combo$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Input_Combo$(DependSuffix)
	$(RM) $(IntermediateDirectory)/Input_Combo$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/Input_Manager$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Input_Manager$(DependSuffix)
	$(RM) $(IntermediateDirectory)/Input_Manager$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/Input_Trigger$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Input_Trigger$(DependSuffix)
	$(RM) $(IntermediateDirectory)/Input_Trigger$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/Tileset_Tileset$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Tileset_Tileset$(DependSuffix)
	$(RM) $(IntermediateDirectory)/Tileset_Tileset$(PreprocessSuffix)
	$(RM) $(OutputFile)
	$(RM) $(OutputFile)
	$(RM) "../.build-release/SSVStart"


