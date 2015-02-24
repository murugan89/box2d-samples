# Copyright (C) 2009 The Android Open Source Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := libgl2jni
LOCAL_CFLAGS    := -Werror\
				   -DANDROID_NDK\
				   -DANDROID\
			       -DOS_ANDROID\
				
INCLUDE_STL		:=  C:/Users/murugan/Software/android-ndk-r8b/sources/cxx-stl/stlport/stlport
INCLUDE_PATH	:=	$(LOCAL_PATH)/../../Include

#include folders
LOCAL_C_INCLUDES := $(INCLUDE_PATH) \
					$(INCLUDE_STL)
				
SRC_PATH 	:= ../../Source
LOCAL_SRC_FILES := gl_code.cpp \
		$(SRC_PATH)/Arbiter.cpp \
		$(SRC_PATH)/World.cpp \
		$(SRC_PATH)/Body.cpp \
		$(SRC_PATH)/Collide.cpp \
		$(SRC_PATH)/Joint.cpp \
		$(SRC_PATH)/MatrixManager.cpp \
		$(SRC_PATH)/ShaderLoader.cpp \
		$(SRC_PATH)/Graphics.cpp \
		$(SRC_PATH)/Application.cpp
		
		


LOCAL_LDLIBS    := -llog -lGLESv2

include $(BUILD_SHARED_LIBRARY)
