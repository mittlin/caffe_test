#-------------------------------------------------
#
# Project created by QtCreator 2015-08-13T15:41:41
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = caffe_test
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

# 添加头文件路径
#CV_INC = /usr/local/include
CUDA_PATH = /usr/local/cuda
BLAS_PATH = /opt/OpenBLAS
# 添加lib文件路径
CV_LIB = /usr/local/lib

DESTDIR = $${PWD}/build

INCLUDEPATH += $${PWD}/include \
               $${CUDA_PATH}/include \
               $${BLAS_PATH}/include

LIBS += -L$${BLAS_PATH}/lib -lopenblas \
        -lglog \
        -L$${PWD}/lib -lcaffe \
        -L$${CV_LIB} -lopencv_ml -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_video -lopencv_legacy

SOURCES += src/main.cpp \
    src/Classifier.cpp \
#    src/blob.cpp \
#    src/common.cpp \
#    src/data_transformer.cpp \
#    src/internal_thread.cpp \
#    src/layer_factory.cpp \
#    src/net.cpp \
#    src/solver.cpp \
#    src/syncedmem.cpp

HEADERS += \
    include/Classifier.h \
#    include/caffe/util/benchmark.hpp \
#    include/caffe/util/cudnn.hpp \
#    include/caffe/util/db.hpp \
#    include/caffe/util/db_leveldb.hpp \
#    include/caffe/util/db_lmdb.hpp \
#    include/caffe/util/device_alternate.hpp \
#    include/caffe/util/hdf5.hpp \
#    include/caffe/util/im2col.hpp \
#    include/caffe/util/insert_splits.hpp \
#    include/caffe/util/io.hpp \
#    include/caffe/util/math_functions.hpp \
#    include/caffe/util/mkl_alternate.hpp \
#    include/caffe/util/rng.hpp \
#    include/caffe/util/upgrade_proto.hpp
