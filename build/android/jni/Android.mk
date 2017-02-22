CPGF_PATH := /projects/cpgf
SFML_PATH := /source/SFML-2.4.1


LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := gincu

ROOT_PATH := E:\projects\gincu
#ROOT_PATH := $(LOCAL_PATH)\..\..\..\..
SRC_PATH := $(ROOT_PATH)\src
TESTS_PATH := $(ROOT_PATH)\tests

LOCAL_CFLAGS += -O3 -fexceptions -std=c++11 \
#	-DGINCU_LOG_LEVEL=G_LOG_LEVEL_DEBUG \
#	-DGINCU_ENTITY_STORAGE_POLICY=mixedArray \
#	-DGINCU_ENTITY_STORAGE_POLICY_INITIAL_SIZE=componentTypeId_PrimaryCount \
#	-DGINCU_MEMORY_POOL_ALIGNMENT=64 \
#	-DGINCU_MEMORY_POOL_BLOCK_COUNT_PER_TRUNK=256 \
#	-DGINCU_MEMORY_POOL_PURGE_STRATEGY=onSceneSwitched \

LOCAL_C_INCLUDES += \
	$(ROOT_PATH)/include \
	$(TESTS_PATH)/application \
	$(CPGF_PATH)/include \
	$(SFML_PATH)/include \
	$(ROOT_PATH)/thirdparty \

LOCAL_SRC_FILES := \
	$(CPGF_PATH)/src/gexception.cpp \
	$(CPGF_PATH)/src/glifecycle.cpp \
	$(CPGF_PATH)/src/gmemorypool.cpp \
	$(CPGF_PATH)/src/tween/gtimeline.cpp \
	$(CPGF_PATH)/src/tween/gtween.cpp \
	$(CPGF_PATH)/src/tween/gtweencommon.cpp \
	$(CPGF_PATH)/src/tween/gtweenlist.cpp \
	$(TESTS_PATH)/application/main.cpp \
	$(TESTS_PATH)/application/uiutil.cpp \
	$(TESTS_PATH)/application/mainapplication.cpp \
	$(TESTS_PATH)/application/scenelogo.cpp \
	$(TESTS_PATH)/application/scenemenu.cpp \
	$(TESTS_PATH)/application/matchthree/componentchess.cpp \
	$(TESTS_PATH)/application/matchthree/matchthreeboard.cpp \
	$(TESTS_PATH)/application/matchthree/matchthreechess.cpp \
	$(TESTS_PATH)/application/matchthree/matchthreeinfoview.cpp \
	$(TESTS_PATH)/application/matchthree/scenematchthree.cpp \
	$(TESTS_PATH)/application/matchthree/statecheckdeadboard.cpp \
	$(TESTS_PATH)/application/matchthree/stateerasematches.cpp \
	$(TESTS_PATH)/application/matchthree/stateinitializenewround.cpp \
	$(TESTS_PATH)/application/matchthree/statemainloop.cpp \
	$(TESTS_PATH)/application/matchthree/stateresult.cpp \
	$(TESTS_PATH)/application/matchthree/stateswapchesses.cpp \
	$(TESTS_PATH)/application/testbed/scenetestbed.cpp \
	$(TESTS_PATH)/application/testbed/scenetestcase.cpp \
	$(TESTS_PATH)/application/testbed/testbed.cpp \
	$(TESTS_PATH)/application/testbed/testcase.cpp \
	$(TESTS_PATH)/application/testbed/testcases/testcase_animation.cpp \
	$(TESTS_PATH)/application/testbed/testcases/testcase_benchmark.cpp \
	$(TESTS_PATH)/application/testbed/testcases/testcase_camera.cpp \
	$(TESTS_PATH)/application/testbed/testcases/testcase_flip.cpp \
	$(TESTS_PATH)/application/testbed/testcases/testcase_scenegraph.cpp \
	$(SRC_PATH)/gerrorhandler.cpp \
	$(SRC_PATH)/gcolor.cpp \
	$(SRC_PATH)/gframeanimation.cpp \
	$(SRC_PATH)/gatlas.cpp \
	$(SRC_PATH)/gatlasrender.cpp \
	$(SRC_PATH)/grenderanchor.cpp \
	$(SRC_PATH)/sfml/gengineutil.cpp \
	$(SRC_PATH)/sfml/gsfmldevicecontext.cpp \
	$(SRC_PATH)/sfml/gsfmlrendercontext.cpp \
	$(SRC_PATH)/gimage.cpp \
	$(SRC_PATH)/gtransform.cpp \
	$(SRC_PATH)/ecs/gcomponent.cpp \
	$(SRC_PATH)/ecs/gcomponentanchor.cpp \
	$(SRC_PATH)/ecs/gcomponentanimation.cpp \
	$(SRC_PATH)/ecs/gcomponentcamera.cpp \
	$(SRC_PATH)/ecs/gcomponentframeanimation.cpp \
	$(SRC_PATH)/ecs/gcomponentlocaltransform.cpp \
	$(SRC_PATH)/ecs/gcomponentmanager.cpp \
	$(SRC_PATH)/ecs/gcomponenttouchhandler.cpp \
	$(SRC_PATH)/ecs/gcomponenttransform.cpp \
	$(SRC_PATH)/ecs/gcomponentrender.cpp \
	$(SRC_PATH)/ecs/gentity.cpp \
	$(SRC_PATH)/ecs/gentitypolicy.cpp \
	$(SRC_PATH)/ecs/gentityutil.cpp \
	$(SRC_PATH)/transition/gtransition.cpp \
	$(SRC_PATH)/transition/gtransitionmovein.cpp \
	$(SRC_PATH)/transition/gtransitionfadeinout.cpp \
	$(SRC_PATH)/gapplication.cpp \
	$(SRC_PATH)/gcamera.cpp \
	$(SRC_PATH)/gdevicecontext.cpp \
	$(SRC_PATH)/gevent.cpp \
	$(SRC_PATH)/geventqueue.cpp \
	$(SRC_PATH)/gfont.cpp \
	$(SRC_PATH)/gfileinputstream.cpp \
	$(SRC_PATH)/gheappool.cpp \
	$(SRC_PATH)/gobjectfactory.cpp \
	$(SRC_PATH)/gresourcemanager.cpp \
	$(SRC_PATH)/gscene.cpp \
	$(SRC_PATH)/gscenemanager.cpp \
	$(SRC_PATH)/gstate.cpp \
	$(SRC_PATH)/gstatemachine.cpp \
	$(SRC_PATH)/gtextrender.cpp \
	$(SRC_PATH)/gtexture.cpp \
	$(SRC_PATH)/gutil.cpp \
	$(SRC_PATH)/gvertexarray.cpp \
	$(SRC_PATH)/gvertexarrayrender.cpp \
	$(SRC_PATH)/gworker.cpp \
	$(ROOT_PATH)/thirdparty/zf_log.cpp \

LOCAL_SHARED_LIBRARIES := sfml-system
LOCAL_SHARED_LIBRARIES += sfml-window
LOCAL_SHARED_LIBRARIES += sfml-graphics
LOCAL_SHARED_LIBRARIES += sfml-audio
LOCAL_SHARED_LIBRARIES += sfml-network
LOCAL_WHOLE_STATIC_LIBRARIES := sfml-main

include $(BUILD_SHARED_LIBRARY)

$(call import-module,sfml)

