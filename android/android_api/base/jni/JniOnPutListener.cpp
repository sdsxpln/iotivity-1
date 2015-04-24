/*
* //******************************************************************
* //
* // Copyright 2015 Intel Corporation.
* //
* //-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
* //
* // Licensed under the Apache License, Version 2.0 (the "License");
* // you may not use this file except in compliance with the License.
* // You may obtain a copy of the License at
* //
* //      http://www.apache.org/licenses/LICENSE-2.0
* //
* // Unless required by applicable law or agreed to in writing, software
* // distributed under the License is distributed on an "AS IS" BASIS,
* // WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* // See the License for the specific language governing permissions and
* // limitations under the License.
* //
* //-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
*/
#include "JniOnPutListener.h"
#include "JniOcResource.h"
#include "JniOcRepresentation.h"
#include "JniUtils.h"

JniOnPutListener::JniOnPutListener(JNIEnv *env, jobject jListener, JniOcResource* owner)
    : m_ownerResource(owner)
{
    m_jwListener = env->NewWeakGlobalRef(jListener);
}

JniOnPutListener::~JniOnPutListener()
{
    if (m_jwListener)
    {
        jint ret;
        JNIEnv *env = GetJNIEnv(ret);
        if (NULL == env) return;

        env->DeleteWeakGlobalRef(m_jwListener);

        if (JNI_EDETACHED == ret) g_jvm->DetachCurrentThread();
    }
}

void JniOnPutListener::onPutCallback(const HeaderOptions& headerOptions,
    const OCRepresentation& ocRepresentation, const int eCode)
{
    jint envRet;
    JNIEnv *env = GetJNIEnv(envRet);
    if (NULL == env) return;

    jobject jListener = env->NewLocalRef(m_jwListener);
    if (!jListener)
    {
        checkExAndRemoveListener(env);
        if (JNI_EDETACHED == envRet) g_jvm->DetachCurrentThread();
        return;
    }
    jclass clsL = env->GetObjectClass(jListener);

    if (OC_STACK_OK != eCode)
    {
        jobject ex = GetOcException(eCode, "stack error in onPutCallback");
        jmethodID midL = env->GetMethodID(clsL, "onPutFailed", "(Ljava/lang/Throwable;)V");
        env->CallVoidMethod(jListener, midL, ex);
    }
    else
    {
        jobject jHeaderOptionList = JniUtils::convertHeaderOptionsVectorToJavaList(env, headerOptions);
        if (!jHeaderOptionList)
        {
            checkExAndRemoveListener(env);
            if (JNI_EDETACHED == envRet) g_jvm->DetachCurrentThread();
            return;
        }

        OCRepresentation * rep = new OCRepresentation(ocRepresentation);
        jlong handle = reinterpret_cast<jlong>(rep);
        jobject jRepresentation = env->NewObject(g_cls_OcRepresentation, g_mid_OcRepresentation_N_ctor_bool,
            handle, true);
        if (!jRepresentation)
        {
            delete rep;
            checkExAndRemoveListener(env);
            if (JNI_EDETACHED == envRet) g_jvm->DetachCurrentThread();
            return;
        }

        jmethodID midL = env->GetMethodID(clsL, "onPutCompleted",
            "(Ljava/util/List;Lorg/iotivity/base/OcRepresentation;)V");

        env->CallVoidMethod(jListener, midL, jHeaderOptionList, jRepresentation);
        if (env->ExceptionCheck())
        {
            LOGE("Java exception is thrown");
            delete rep;
        }
    }

    checkExAndRemoveListener(env);
    if (JNI_EDETACHED == envRet) g_jvm->DetachCurrentThread();
}

void JniOnPutListener::checkExAndRemoveListener(JNIEnv* env)
{
    if (env->ExceptionCheck())
    {
        jthrowable ex = env->ExceptionOccurred();
        env->ExceptionClear();
        m_ownerResource->removeOnPutListener(env, m_jwListener);
        env->Throw((jthrowable)ex);
    }
    else
    {
        m_ownerResource->removeOnPutListener(env, m_jwListener);
    }
}