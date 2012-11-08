##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=SSVStart
ConfigurationName      :=Debug
WorkspacePath          := "D:\Vee\Software\WIP\CL\WorkspaceOH\OH"
ProjectPath            := "D:\Vee\Software\WIP\CL\WorkspaceOH\OH\SSVStart"
IntermediateDirectory  :=./Debug
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=Vittorio
Date                   :=11/08/12
CodeLitePath           :="c:\Program Files (x86)\CodeLite"
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
ObjectsFileList        :="D:\Vee\Software\WIP\CL\WorkspaceOH\OH\SSVStart\SSVStart.txt"
PCHCompileFlags        :=
MakeDirCommand         :=makedir
RcCmpOptions           := 
RcCompilerName         :=windres
LinkOptions            :=  -shared
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch)D:/Vee/Software/WIP/SFMLMinGW/include 
IncludePCH             := 
RcIncludePath          := 
Libs                   := $(LibrarySwitch)sfml-system-d $(LibrarySwitch)sfml-window-d $(LibrarySwitch)sfml-audio-d $(LibrarySwitch)sfml-graphics-d 
ArLibs                 :=  "sfml-system-d" "sfml-window-d" "sfml-audio-d" "sfml-graphics-d" 
LibPath                := $(LibraryPathSwitch). $(LibraryPathSwitch)"D:/Vee/Software/WIP/SFMLMinGW/lib" 

##
## Common variables
## AR, CXX, CC, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := ar rcus
CXX      := g++
CC       := gcc
CXXFLAGS :=  -pedantic -Wall -O0 -g3 -c -fmessage-length=0 -std=c++11 $(Preprocessors)
CFLAGS   :=  -g $(Preprocessors)


##
## User defined environment variables
##
CodeLiteDir:=c:\Program Files (x86)\CodeLite
WXWIN:=C:\wxWidgets
UNIT_TEST_PP_SRC_DIR:=C:\UnitTest++-1.3
WXCFG:=gcc_dll\mswu
Objects=$(IntermediateDirectory)/GameSystem_Game$(ObjectSuffix) $(IntermediateDirectory)/GameSystem_GameWindow$(ObjectSuffix) $(IntermediateDirectory)/Timeline_Command$(ObjectSuffix) $(IntermediateDirectory)/Timeline_Do$(ObjectSuffix) $(IntermediateDirectory)/Timeline_Goto$(ObjectSuffix) $(IntermediateDirectory)/Timeline_Timeline$(ObjectSuffix) $(IntermediateDirectory)/Timeline_Wait$(ObjectSuffix) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild
all: $(OutputFile)

$(OutputFile): $(IntermediateDirectory)/.d $(Objects) 
	@$(MakeDirCommand) $(@D)
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects) > $(ObjectsFileList)
	$(SharedObjectLinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)
	@$(MakeDirCommand) "D:\Vee\Software\WIP\CL\WorkspaceOH\OH\.build-debug"
	@echo rebuilt > "D:\Vee\Software\WIP\CL\WorkspaceOH\OH\.build-debug\SSVStart"

$(IntermediateDirectory)/.d:
	@$(MakeDirCommand) "./Debug"

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/GameSystem_Game$(ObjectSuffix): GameSystem/Game.cpp $(IntermediateDirectory)/GameSystem_Game$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "D:/Vee/Software/WIP/CL/WorkspaceOH/OH/SSVStart/GameSystem/Game.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/GameSystem_Game$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/GameSystem_Game$(DependSuffix): GameSystem/Game.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/GameSystem_Game$(ObjectSuffix) -MF$(IntermediateDirectory)/GameSystem_Game$(DependSuffix) -MM "D:/Vee/Software/WIP/CL/WorkspaceOH/OH/SSVStart/GameSystem/Game.cpp"

$(IntermediateDirectory)/GameSystem_Game$(PreprocessSuffix): GameSystem/Game.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/GameSystem_Game$(PreprocessSuffix) "D:/Vee/Software/WIP/CL/WorkspaceOH/OH/SSVStart/GameSystem/Game.cpp"

$(IntermediateDirectory)/GameSystem_GameWindow$(ObjectSuffix): GameSystem/GameWindow.cpp $(IntermediateDirectory)/GameSystem_GameWindow$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "D:/Vee/Software/WIP/CL/WorkspaceOH/OH/SSVStart/GameSystem/GameWindow.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/GameSystem_GameWindow$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/GameSystem_GameWindow$(DependSuffix): GameSystem/GameWindow.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/GameSystem_GameWindow$(ObjectSuffix) -MF$(IntermediateDirectory)/GameSystem_GameWindow$(DependSuffix) -MM "D:/Vee/Software/WIP/CL/WorkspaceOH/OH/SSVStart/GameSystem/GameWindow.cpp"

$(IntermediateDirectory)/GameSystem_GameWindow$(PreprocessSuffix): GameSystem/GameWindow.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/GameSystem_GameWindow$(PreprocessSuffix) "D:/Vee/Software/WIP/CL/WorkspaceOH/OH/SSVStart/GameSystem/GameWindow.cpp"

$(IntermediateDirectory)/Timeline_Command$(ObjectSuffix): Timeline/Command.cpp $(IntermediateDirectory)/Timeline_Command$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "D:/Vee/Software/WIP/CL/WorkspaceOH/OH/SSVStart/Timeline/Command.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Timeline_Command$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Timeline_Command$(DependSuffix): Timeline/Command.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Timeline_Command$(ObjectSuffix) -MF$(IntermediateDirectory)/Timeline_Command$(DependSuffix) -MM "D:/Vee/Software/WIP/CL/WorkspaceOH/OH/SSVStart/Timeline/Command.cpp"

$(IntermediateDirectory)/Timeline_Command$(PreprocessSuffix): Timeline/Command.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Timeline_Command$(PreprocessSuffix) "D:/Vee/Software/WIP/CL/WorkspaceOH/OH/SSVStart/Timeline/Command.cpp"

$(IntermediateDirectory)/Timeline_Do$(ObjectSuffix): Timeline/Do.cpp $(IntermediateDirectory)/Timeline_Do$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "D:/Vee/Software/WIP/CL/WorkspaceOH/OH/SSVStart/Timeline/Do.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Timeline_Do$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Timeline_Do$(DependSuffix): Timeline/Do.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Timeline_Do$(ObjectSuffix) -MF$(IntermediateDirectory)/Timeline_Do$(DependSuffix) -MM "D:/Vee/Software/WIP/CL/WorkspaceOH/OH/SSVStart/Timeline/Do.cpp"

$(IntermediateDirectory)/Timeline_Do$(PreprocessSuffix): Timeline/Do.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Timeline_Do$(PreprocessSuffix) "D:/Vee/Software/WIP/CL/WorkspaceOH/OH/SSVStart/Timeline/Do.cpp"

$(IntermediateDirectory)/Timeline_Goto$(ObjectSuffix): Timeline/Goto.cpp $(IntermediateDirectory)/Timeline_Goto$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "D:/Vee/Software/WIP/CL/WorkspaceOH/OH/SSVStart/Timeline/Goto.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Timeline_Goto$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Timeline_Goto$(DependSuffix): Timeline/Goto.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Timeline_Goto$(ObjectSuffix) -MF$(IntermediateDirectory)/Timeline_Goto$(DependSuffix) -MM "D:/Vee/Software/WIP/CL/WorkspaceOH/OH/SSVStart/Timeline/Goto.cpp"

$(IntermediateDirectory)/Timeline_Goto$(PreprocessSuffix): Timeline/Goto.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Timeline_Goto$(PreprocessSuffix) "D:/Vee/Software/WIP/CL/WorkspaceOH/OH/SSVStart/Timeline/Goto.cpp"

$(IntermediateDirectory)/Timeline_Timeline$(ObjectSuffix): Timeline/Timeline.cpp $(IntermediateDirectory)/Timeline_Timeline$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "D:/Vee/Software/WIP/CL/WorkspaceOH/OH/SSVStart/Timeline/Timeline.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Timeline_Timeline$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Timeline_Timeline$(DependSuffix): Timeline/Timeline.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Timeline_Timeline$(ObjectSuffix) -MF$(IntermediateDirectory)/Timeline_Timeline$(DependSuffix) -MM "D:/Vee/Software/WIP/CL/WorkspaceOH/OH/SSVStart/Timeline/Timeline.cpp"

$(IntermediateDirectory)/Timeline_Timeline$(PreprocessSuffix): Timeline/Timeline.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Timeline_Timeline$(PreprocessSuffix) "D:/Vee/Software/WIP/CL/WorkspaceOH/OH/SSVStart/Timeline/Timeline.cpp"

$(IntermediateDirectory)/Timeline_Wait$(ObjectSuffix): Timeline/Wait.cpp $(IntermediateDirectory)/Timeline_Wait$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "D:/Vee/Software/WIP/CL/WorkspaceOH/OH/SSVStart/Timeline/Wait.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Timeline_Wait$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Timeline_Wait$(DependSuffix): Timeline/Wait.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Timeline_Wait$(ObjectSuffix) -MF$(IntermediateDirectory)/Timeline_Wait$(DependSuffix) -MM "D:/Vee/Software/WIP/CL/WorkspaceOH/OH/SSVStart/Timeline/Wait.cpp"

$(IntermediateDirectory)/Timeline_Wait$(PreprocessSuffix): Timeline/Wait.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Timeline_Wait$(PreprocessSuffix) "D:/Vee/Software/WIP/CL/WorkspaceOH/OH/SSVStart/Timeline/Wait.cpp"


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) $(IntermediateDirectory)/GameSystem_Game$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/GameSystem_Game$(DependSuffix)
	$(RM) $(IntermediateDirectory)/GameSystem_Game$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/GameSystem_GameWindow$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/GameSystem_GameWindow$(DependSuffix)
	$(RM) $(IntermediateDirectory)/GameSystem_GameWindow$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/Timeline_Command$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Timeline_Command$(DependSuffix)
	$(RM) $(IntermediateDirectory)/Timeline_Command$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/Timeline_Do$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Timeline_Do$(DependSuffix)
	$(RM) $(IntermediateDirectory)/Timeline_Do$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/Timeline_Goto$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Timeline_Goto$(DependSuffix)
	$(RM) $(IntermediateDirectory)/Timeline_Goto$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/Timeline_Timeline$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Timeline_Timeline$(DependSuffix)
	$(RM) $(IntermediateDirectory)/Timeline_Timeline$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/Timeline_Wait$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Timeline_Wait$(DependSuffix)
	$(RM) $(IntermediateDirectory)/Timeline_Wait$(PreprocessSuffix)
	$(RM) $(OutputFile)
	$(RM) $(OutputFile)
	$(RM) "D:\Vee\Software\WIP\CL\WorkspaceOH\OH\.build-debug\SSVStart"


