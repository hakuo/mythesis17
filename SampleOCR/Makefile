APP=Sample_OCR

CPP=g++
CC=gcc

CFLAGS+=-O3 -Wall -fmessage-length=0 -std=c++11 -DUSE_STD_NAMESPACE -DHAVE_TESSERACT

LIB_DIRS+=-L/usr/local/lib

LIBS+=-llept \
	-ltesseract \
	-lopencv_imgproc \
	-lopencv_core \
	-lopencv_highgui \
	-lopencv_ml \
	-lopencv_imgcodecs \
	-lopencv_dnn \

INCS+=-I./include \

SRCS+=main.cpp \
	ocr_utils/erfilter.cpp \
	ocr_utils/ocr_holistic.cpp \
	ocr_utils/text_detectorCNN.cpp \
	ocr_utils/ocr_beamsearch_decoder.cpp \
	ocr_utils/ocr_tesseract.cpp \
	ocr_utils/ocr_hmm_decoder.cpp \
	ocr_utils/precomp.hpp \

OBJS = $(SRCS:.cpp=.o)

%.o: %.cpp $(DEPS)
	$(CPP) -c -o $@ $< $(CFLAGS) $(INCS) 

$(APP): $(OBJS)
	$(CPP) -o $@ $^ $(CFLAGS) $(LDFLAGS) $(INCS) ${LIB_DIRS} ${LIBS}

.PHONY: clean

clean:
	find . -name *.o -exec rm -f {} \; 
	rm -f ${APP}

