CXX=g++

CXXFLAGS =	-O2 -g -Wall -fopenmp

SRCS = SpecModel.cpp HIModel.cpp GAModel.cpp CGFRModel.cpp CGFDModel.cpp LatData.cpp Utils.cpp Param.cpp AdmixInfer.cpp

OBJS = $(SRCS:.cpp=.o)

LIBS = 

TARGET = AdmixInfer

$(TARGET):	$(OBJS)
	$(CXX) -fopenmp -o $(TARGET) $(OBJS) $(LIBS) 

all:	$(TARGET)

.cpp.o:
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
