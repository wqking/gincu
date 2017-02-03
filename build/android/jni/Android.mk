CPGF_PATH := /projects/cpgf
SFML_PATH := /source/SFML-2.4.1


LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := gincu

ROOT_PATH := E:\projects\gincu
#ROOT_PATH := $(LOCAL_PATH)\..\..\..\..
SRC_PATH := $(ROOT_PATH)\src

LOCAL_CFLAGS += -fexceptions -std=c++11

#PRODUCT_COPY_FILES += $(ROOT_PATH)/bin/resources/arialbd.ttf

LOCAL_C_INCLUDES += \
	$(SRC_PATH)/ \
	$(SRC_PATH)/application \
	$(CPGF_PATH)/include \
	$(SFML_PATH)/include \

LOCAL_SRC_FILES := \
	$(CPGF_PATH)/src/gexception.cpp \
	$(CPGF_PATH)/src/glifecycle.cpp \
	$(CPGF_PATH)/src/gmemorypool.cpp \
	$(CPGF_PATH)/src/tween/gtimeline.cpp \
	$(CPGF_PATH)/src/tween/gtween.cpp \
	$(CPGF_PATH)/src/tween/gtweencommon.cpp \
	$(CPGF_PATH)/src/tween/gtweenlist.cpp \
	$(SRC_PATH)/main.cpp \
	$(SRC_PATH)/application/mainapplication.cpp \
	$(SRC_PATH)/application/scenelogo.cpp \
	$(SRC_PATH)/application/scenemenu.cpp \
	$(SRC_PATH)/application/matchthree/componentchess.cpp \
	$(SRC_PATH)/application/matchthree/matchthreeboard.cpp \
	$(SRC_PATH)/application/matchthree/matchthreechess.cpp \
	$(SRC_PATH)/application/matchthree/matchthreeinfoview.cpp \
	$(SRC_PATH)/application/matchthree/scenematchthree.cpp \
	$(SRC_PATH)/application/matchthree/statecheckdeadboard.cpp \
	$(SRC_PATH)/application/matchthree/stateerasematches.cpp \
	$(SRC_PATH)/application/matchthree/stateinitializenewround.cpp \
	$(SRC_PATH)/application/matchthree/statemainloop.cpp \
	$(SRC_PATH)/application/matchthree/stateresult.cpp \
	$(SRC_PATH)/application/matchthree/stateswapchesses.cpp \
	$(SRC_PATH)/engine/errorhandler.cpp \
	$(SRC_PATH)/engine/gamecolor.cpp \
	$(SRC_PATH)/engine/renderanchor.cpp \
	$(SRC_PATH)/engine/sfml/engineutil.cpp \
	$(SRC_PATH)/engine/sfml/gameeventprocessor.cpp \
	$(SRC_PATH)/engine/sfml/gamefont.cpp \
	$(SRC_PATH)/engine/sfml/gameimage.cpp \
	$(SRC_PATH)/engine/sfml/gametext.cpp \
	$(SRC_PATH)/engine/sfml/gametransform.cpp \
	$(SRC_PATH)/engine/sfml/rectrender.cpp \
	$(SRC_PATH)/engine/sfml/renderengine.cpp \
	$(SRC_PATH)/engine/sfml/resourcemanager.cpp \
	$(SRC_PATH)/framework/component.cpp \
	$(SRC_PATH)/framework/componentanchor.cpp \
	$(SRC_PATH)/framework/componentrender.cpp \
	$(SRC_PATH)/framework/componentsbuffer.cpp \
	$(SRC_PATH)/framework/componenttouchhandler.cpp \
	$(SRC_PATH)/framework/componenttransform.cpp \
	$(SRC_PATH)/framework/entity.cpp \
	$(SRC_PATH)/framework/entitypolicy.cpp \
	$(SRC_PATH)/framework/entityutil.cpp \
	$(SRC_PATH)/framework/gameapplication.cpp \
	$(SRC_PATH)/framework/memorypool.cpp \
	$(SRC_PATH)/framework/scene.cpp \
	$(SRC_PATH)/framework/scenemanager.cpp \
	$(SRC_PATH)/framework/state.cpp \
	$(SRC_PATH)/framework/statemachine.cpp \
	$(SRC_PATH)/framework/util.cpp \

LOCAL_SHARED_LIBRARIES := sfml-system
LOCAL_SHARED_LIBRARIES += sfml-window
LOCAL_SHARED_LIBRARIES += sfml-graphics
LOCAL_SHARED_LIBRARIES += sfml-audio
LOCAL_SHARED_LIBRARIES += sfml-network
LOCAL_WHOLE_STATIC_LIBRARIES := sfml-main

include $(BUILD_SHARED_LIBRARY)

$(call import-module,sfml)

