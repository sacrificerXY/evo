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
Date                   :=11/04/2020
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
Objects0=../build-$(ConfigurationName)/evo/src_Random.cpp$(ObjectSuffix) ../build-$(ConfigurationName)/evo/src_fmt_format.cc$(ObjectSuffix) ../build-$(ConfigurationName)/evo/src_fmt_os.cc$(ObjectSuffix) ../build-$(ConfigurationName)/evo/src_GenomeLinkIdGenerator.cpp$(ObjectSuffix) ../build-$(ConfigurationName)/evo/src_Brain.cpp$(ObjectSuffix) ../build-$(ConfigurationName)/evo/src_Genome.cpp$(ObjectSuffix) ../build-$(ConfigurationName)/evo/main.cpp$(ObjectSuffix) 



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
../build-$(ConfigurationName)/evo/src_Random.cpp$(ObjectSuffix): src/Random.cpp ../build-$(ConfigurationName)/evo/src_Random.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "G:/projects/c++/workspace/evo/evo/src/Random.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_Random.cpp$(ObjectSuffix) $(IncludePath)
../build-$(ConfigurationName)/evo/src_Random.cpp$(DependSuffix): src/Random.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT../build-$(ConfigurationName)/evo/src_Random.cpp$(ObjectSuffix) -MF../build-$(ConfigurationName)/evo/src_Random.cpp$(DependSuffix) -MM src/Random.cpp

../build-$(ConfigurationName)/evo/src_Random.cpp$(PreprocessSuffix): src/Random.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) ../build-$(ConfigurationName)/evo/src_Random.cpp$(PreprocessSuffix) src/Random.cpp

../build-$(ConfigurationName)/evo/src_fmt_format.cc$(ObjectSuffix): src/fmt/format.cc ../build-$(ConfigurationName)/evo/src_fmt_format.cc$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "G:/projects/c++/workspace/evo/evo/src/fmt/format.cc" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_fmt_format.cc$(ObjectSuffix) $(IncludePath)
../build-$(ConfigurationName)/evo/src_fmt_format.cc$(DependSuffix): src/fmt/format.cc
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT../build-$(ConfigurationName)/evo/src_fmt_format.cc$(ObjectSuffix) -MF../build-$(ConfigurationName)/evo/src_fmt_format.cc$(DependSuffix) -MM src/fmt/format.cc

../build-$(ConfigurationName)/evo/src_fmt_format.cc$(PreprocessSuffix): src/fmt/format.cc
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) ../build-$(ConfigurationName)/evo/src_fmt_format.cc$(PreprocessSuffix) src/fmt/format.cc

../build-$(ConfigurationName)/evo/src_fmt_os.cc$(ObjectSuffix): src/fmt/os.cc ../build-$(ConfigurationName)/evo/src_fmt_os.cc$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "G:/projects/c++/workspace/evo/evo/src/fmt/os.cc" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_fmt_os.cc$(ObjectSuffix) $(IncludePath)
../build-$(ConfigurationName)/evo/src_fmt_os.cc$(DependSuffix): src/fmt/os.cc
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT../build-$(ConfigurationName)/evo/src_fmt_os.cc$(ObjectSuffix) -MF../build-$(ConfigurationName)/evo/src_fmt_os.cc$(DependSuffix) -MM src/fmt/os.cc

../build-$(ConfigurationName)/evo/src_fmt_os.cc$(PreprocessSuffix): src/fmt/os.cc
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) ../build-$(ConfigurationName)/evo/src_fmt_os.cc$(PreprocessSuffix) src/fmt/os.cc

../build-$(ConfigurationName)/evo/src_GenomeLinkIdGenerator.cpp$(ObjectSuffix): src/GenomeLinkIdGenerator.cpp ../build-$(ConfigurationName)/evo/src_GenomeLinkIdGenerator.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "G:/projects/c++/workspace/evo/evo/src/GenomeLinkIdGenerator.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_GenomeLinkIdGenerator.cpp$(ObjectSuffix) $(IncludePath)
../build-$(ConfigurationName)/evo/src_GenomeLinkIdGenerator.cpp$(DependSuffix): src/GenomeLinkIdGenerator.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT../build-$(ConfigurationName)/evo/src_GenomeLinkIdGenerator.cpp$(ObjectSuffix) -MF../build-$(ConfigurationName)/evo/src_GenomeLinkIdGenerator.cpp$(DependSuffix) -MM src/GenomeLinkIdGenerator.cpp

../build-$(ConfigurationName)/evo/src_GenomeLinkIdGenerator.cpp$(PreprocessSuffix): src/GenomeLinkIdGenerator.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) ../build-$(ConfigurationName)/evo/src_GenomeLinkIdGenerator.cpp$(PreprocessSuffix) src/GenomeLinkIdGenerator.cpp

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


-include ../build-$(ConfigurationName)/evo//*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r $(IntermediateDirectory)


