##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=evo
ConfigurationName      :=Debug
WorkspaceConfiguration := $(ConfigurationName)
WorkspacePath          :=G:/projects/c++/workspace/evo
ProjectPath            :=G:/projects/c++/workspace/evo/evo
IntermediateDirectory  :=../build-$(ConfigurationName)/evo
OutDir                 :=../build-$(ConfigurationName)/evo
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=Kyle
Date                   :=09/04/2020
CodeLitePath           :=G:/CodeLite
LinkerName             :=G:/msys64/mingw64/bin/g++.exe
SharedObjectLinkerName :=G:/msys64/mingw64/bin/g++.exe -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.i
DebugSwitch            :=-g 
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
OutputFile             :=..\build-$(ConfigurationName)\bin\$(ProjectName)
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E
ObjectsFileList        :=$(IntermediateDirectory)/ObjectsList.txt
PCHCompileFlags        :=
RcCmpOptions           := 
RcCompilerName         :=G:/msys64/mingw64/bin/windres.exe
LinkOptions            :=  
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch)include $(IncludeSwitch). 
IncludePCH             := 
RcIncludePath          := 
Libs                   := 
ArLibs                 :=  
LibPath                := $(LibraryPathSwitch). 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := G:/msys64/mingw64/bin/ar.exe rcu
CXX      := G:/msys64/mingw64/bin/g++.exe
CC       := G:/msys64/mingw64/bin/gcc.exe
CXXFLAGS := -std=c++2a -Werror=return-type  -g -O0 -Wall $(Preprocessors)
CFLAGS   :=  -g -O0 -Wall $(Preprocessors)
ASFLAGS  := 
AS       := G:/msys64/mingw64/bin/as.exe


##
## User defined environment variables
##
CodeLiteDir:=G:\CodeLite
Objects0=../build-$(ConfigurationName)/evo/src_fmt_os.cc$(ObjectSuffix) ../build-$(ConfigurationName)/evo/src_neat_mutator.cpp$(ObjectSuffix) ../build-$(ConfigurationName)/evo/src_neat__internal.cpp$(ObjectSuffix) ../build-$(ConfigurationName)/evo/src_Simulation.cpp$(ObjectSuffix) ../build-$(ConfigurationName)/evo/src_neat_brain.cpp$(ObjectSuffix) ../build-$(ConfigurationName)/evo/src_Link.cpp$(ObjectSuffix) ../build-$(ConfigurationName)/evo/src_Brain.cpp$(ObjectSuffix) ../build-$(ConfigurationName)/evo/src_Genome.cpp$(ObjectSuffix) ../build-$(ConfigurationName)/evo/main.cpp$(ObjectSuffix) ../build-$(ConfigurationName)/evo/src_fmt_format.cc$(ObjectSuffix) \
	../build-$(ConfigurationName)/evo/src_neat_genome.cpp$(ObjectSuffix) 



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild MakeIntermediateDirs
all: MakeIntermediateDirs $(OutputFile)

$(OutputFile): ../build-$(ConfigurationName)/evo/.d $(Objects) 
	@if not exist "..\build-$(ConfigurationName)\evo" mkdir "..\build-$(ConfigurationName)\evo"
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(LinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)

MakeIntermediateDirs:
	@if not exist "..\build-$(ConfigurationName)\evo" mkdir "..\build-$(ConfigurationName)\evo"
	@if not exist ""..\build-$(ConfigurationName)\bin"" mkdir ""..\build-$(ConfigurationName)\bin""

../build-$(ConfigurationName)/evo/.d:
	@if not exist "..\build-$(ConfigurationName)\evo" mkdir "..\build-$(ConfigurationName)\evo"

PreBuild:


##
## Objects
##
../build-$(ConfigurationName)/evo/src_fmt_os.cc$(ObjectSuffix): src/fmt/os.cc ../build-$(ConfigurationName)/evo/src_fmt_os.cc$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "G:/projects/c++/workspace/evo/evo/src/fmt/os.cc" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_fmt_os.cc$(ObjectSuffix) $(IncludePath)
../build-$(ConfigurationName)/evo/src_fmt_os.cc$(DependSuffix): src/fmt/os.cc
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT../build-$(ConfigurationName)/evo/src_fmt_os.cc$(ObjectSuffix) -MF../build-$(ConfigurationName)/evo/src_fmt_os.cc$(DependSuffix) -MM src/fmt/os.cc

../build-$(ConfigurationName)/evo/src_fmt_os.cc$(PreprocessSuffix): src/fmt/os.cc
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) ../build-$(ConfigurationName)/evo/src_fmt_os.cc$(PreprocessSuffix) src/fmt/os.cc

../build-$(ConfigurationName)/evo/src_neat_mutator.cpp$(ObjectSuffix): src/neat/mutator.cpp ../build-$(ConfigurationName)/evo/src_neat_mutator.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "G:/projects/c++/workspace/evo/evo/src/neat/mutator.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_neat_mutator.cpp$(ObjectSuffix) $(IncludePath)
../build-$(ConfigurationName)/evo/src_neat_mutator.cpp$(DependSuffix): src/neat/mutator.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT../build-$(ConfigurationName)/evo/src_neat_mutator.cpp$(ObjectSuffix) -MF../build-$(ConfigurationName)/evo/src_neat_mutator.cpp$(DependSuffix) -MM src/neat/mutator.cpp

../build-$(ConfigurationName)/evo/src_neat_mutator.cpp$(PreprocessSuffix): src/neat/mutator.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) ../build-$(ConfigurationName)/evo/src_neat_mutator.cpp$(PreprocessSuffix) src/neat/mutator.cpp

../build-$(ConfigurationName)/evo/src_neat__internal.cpp$(ObjectSuffix): src/neat/_internal.cpp ../build-$(ConfigurationName)/evo/src_neat__internal.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "G:/projects/c++/workspace/evo/evo/src/neat/_internal.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_neat__internal.cpp$(ObjectSuffix) $(IncludePath)
../build-$(ConfigurationName)/evo/src_neat__internal.cpp$(DependSuffix): src/neat/_internal.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT../build-$(ConfigurationName)/evo/src_neat__internal.cpp$(ObjectSuffix) -MF../build-$(ConfigurationName)/evo/src_neat__internal.cpp$(DependSuffix) -MM src/neat/_internal.cpp

../build-$(ConfigurationName)/evo/src_neat__internal.cpp$(PreprocessSuffix): src/neat/_internal.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) ../build-$(ConfigurationName)/evo/src_neat__internal.cpp$(PreprocessSuffix) src/neat/_internal.cpp

../build-$(ConfigurationName)/evo/src_Simulation.cpp$(ObjectSuffix): src/Simulation.cpp ../build-$(ConfigurationName)/evo/src_Simulation.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "G:/projects/c++/workspace/evo/evo/src/Simulation.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_Simulation.cpp$(ObjectSuffix) $(IncludePath)
../build-$(ConfigurationName)/evo/src_Simulation.cpp$(DependSuffix): src/Simulation.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT../build-$(ConfigurationName)/evo/src_Simulation.cpp$(ObjectSuffix) -MF../build-$(ConfigurationName)/evo/src_Simulation.cpp$(DependSuffix) -MM src/Simulation.cpp

../build-$(ConfigurationName)/evo/src_Simulation.cpp$(PreprocessSuffix): src/Simulation.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) ../build-$(ConfigurationName)/evo/src_Simulation.cpp$(PreprocessSuffix) src/Simulation.cpp

../build-$(ConfigurationName)/evo/src_neat_brain.cpp$(ObjectSuffix): src/neat/brain.cpp ../build-$(ConfigurationName)/evo/src_neat_brain.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "G:/projects/c++/workspace/evo/evo/src/neat/brain.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_neat_brain.cpp$(ObjectSuffix) $(IncludePath)
../build-$(ConfigurationName)/evo/src_neat_brain.cpp$(DependSuffix): src/neat/brain.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT../build-$(ConfigurationName)/evo/src_neat_brain.cpp$(ObjectSuffix) -MF../build-$(ConfigurationName)/evo/src_neat_brain.cpp$(DependSuffix) -MM src/neat/brain.cpp

../build-$(ConfigurationName)/evo/src_neat_brain.cpp$(PreprocessSuffix): src/neat/brain.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) ../build-$(ConfigurationName)/evo/src_neat_brain.cpp$(PreprocessSuffix) src/neat/brain.cpp

../build-$(ConfigurationName)/evo/src_Link.cpp$(ObjectSuffix): src/Link.cpp ../build-$(ConfigurationName)/evo/src_Link.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "G:/projects/c++/workspace/evo/evo/src/Link.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_Link.cpp$(ObjectSuffix) $(IncludePath)
../build-$(ConfigurationName)/evo/src_Link.cpp$(DependSuffix): src/Link.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT../build-$(ConfigurationName)/evo/src_Link.cpp$(ObjectSuffix) -MF../build-$(ConfigurationName)/evo/src_Link.cpp$(DependSuffix) -MM src/Link.cpp

../build-$(ConfigurationName)/evo/src_Link.cpp$(PreprocessSuffix): src/Link.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) ../build-$(ConfigurationName)/evo/src_Link.cpp$(PreprocessSuffix) src/Link.cpp

../build-$(ConfigurationName)/evo/src_Brain.cpp$(ObjectSuffix): src/Brain.cpp ../build-$(ConfigurationName)/evo/src_Brain.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "G:/projects/c++/workspace/evo/evo/src/Brain.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_Brain.cpp$(ObjectSuffix) $(IncludePath)
../build-$(ConfigurationName)/evo/src_Brain.cpp$(DependSuffix): src/Brain.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT../build-$(ConfigurationName)/evo/src_Brain.cpp$(ObjectSuffix) -MF../build-$(ConfigurationName)/evo/src_Brain.cpp$(DependSuffix) -MM src/Brain.cpp

../build-$(ConfigurationName)/evo/src_Brain.cpp$(PreprocessSuffix): src/Brain.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) ../build-$(ConfigurationName)/evo/src_Brain.cpp$(PreprocessSuffix) src/Brain.cpp

../build-$(ConfigurationName)/evo/src_Genome.cpp$(ObjectSuffix): src/Genome.cpp ../build-$(ConfigurationName)/evo/src_Genome.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "G:/projects/c++/workspace/evo/evo/src/Genome.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_Genome.cpp$(ObjectSuffix) $(IncludePath)
../build-$(ConfigurationName)/evo/src_Genome.cpp$(DependSuffix): src/Genome.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT../build-$(ConfigurationName)/evo/src_Genome.cpp$(ObjectSuffix) -MF../build-$(ConfigurationName)/evo/src_Genome.cpp$(DependSuffix) -MM src/Genome.cpp

../build-$(ConfigurationName)/evo/src_Genome.cpp$(PreprocessSuffix): src/Genome.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) ../build-$(ConfigurationName)/evo/src_Genome.cpp$(PreprocessSuffix) src/Genome.cpp

../build-$(ConfigurationName)/evo/main.cpp$(ObjectSuffix): main.cpp ../build-$(ConfigurationName)/evo/main.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "G:/projects/c++/workspace/evo/evo/main.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/main.cpp$(ObjectSuffix) $(IncludePath)
../build-$(ConfigurationName)/evo/main.cpp$(DependSuffix): main.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT../build-$(ConfigurationName)/evo/main.cpp$(ObjectSuffix) -MF../build-$(ConfigurationName)/evo/main.cpp$(DependSuffix) -MM main.cpp

../build-$(ConfigurationName)/evo/main.cpp$(PreprocessSuffix): main.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) ../build-$(ConfigurationName)/evo/main.cpp$(PreprocessSuffix) main.cpp

../build-$(ConfigurationName)/evo/src_fmt_format.cc$(ObjectSuffix): src/fmt/format.cc ../build-$(ConfigurationName)/evo/src_fmt_format.cc$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "G:/projects/c++/workspace/evo/evo/src/fmt/format.cc" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_fmt_format.cc$(ObjectSuffix) $(IncludePath)
../build-$(ConfigurationName)/evo/src_fmt_format.cc$(DependSuffix): src/fmt/format.cc
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT../build-$(ConfigurationName)/evo/src_fmt_format.cc$(ObjectSuffix) -MF../build-$(ConfigurationName)/evo/src_fmt_format.cc$(DependSuffix) -MM src/fmt/format.cc

../build-$(ConfigurationName)/evo/src_fmt_format.cc$(PreprocessSuffix): src/fmt/format.cc
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) ../build-$(ConfigurationName)/evo/src_fmt_format.cc$(PreprocessSuffix) src/fmt/format.cc

../build-$(ConfigurationName)/evo/src_neat_genome.cpp$(ObjectSuffix): src/neat/genome.cpp ../build-$(ConfigurationName)/evo/src_neat_genome.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "G:/projects/c++/workspace/evo/evo/src/neat/genome.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_neat_genome.cpp$(ObjectSuffix) $(IncludePath)
../build-$(ConfigurationName)/evo/src_neat_genome.cpp$(DependSuffix): src/neat/genome.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT../build-$(ConfigurationName)/evo/src_neat_genome.cpp$(ObjectSuffix) -MF../build-$(ConfigurationName)/evo/src_neat_genome.cpp$(DependSuffix) -MM src/neat/genome.cpp

../build-$(ConfigurationName)/evo/src_neat_genome.cpp$(PreprocessSuffix): src/neat/genome.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) ../build-$(ConfigurationName)/evo/src_neat_genome.cpp$(PreprocessSuffix) src/neat/genome.cpp


-include ../build-$(ConfigurationName)/evo//*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r $(IntermediateDirectory)


