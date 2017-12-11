APP=VieOCR

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
	-lpthread

INCS+=-I. \

SRCS_DIR=. \

SRCS+=${SRCS_DIR}/main.cpp \
	${SRCS_DIR}/ocr_utils/erfilter.cpp \
	${SRCS_DIR}/ocr_utils/ocr_holistic.cpp \
	${SRCS_DIR}/ocr_utils/text_detectorCNN.cpp \
	${SRCS_DIR}/ocr_utils/ocr_beamsearch_decoder.cpp \
	${SRCS_DIR}/ocr_utils/ocr_tesseract.cpp \
	${SRCS_DIR}/ocr_utils/ocr_hmm_decoder.cpp \
	${SRCS_DIR}/thread/thread.cpp \
	${SRCS_DIR}/dl_tool/dl_tool.cpp \
	${SRCS_DIR}/ocr_tool/ocr_tool.cpp \
	${SRCS_DIR}/tts_tool/thread.cpp \
	${SRCS_DIR}/comm_mgr/comm_mgr.cpp \

OBJS = $(SRCS:.cpp=.o)

%.o: %.cpp $(DEPS)
	$(CPP) -o $@ $< $(CFLAGS) $(INCS) 

all: ${APP}

$(APP): $(OBJS)
	$(CPP) -o $@ $^ $(CFLAGS) $(LDFLAGS) $(INCS) ${LIB_DIRS} ${LIBS}

.PHONY: clean

clean:
	find . -name *.o -exec rm -f {} \; 
	rm -f ${APP}

