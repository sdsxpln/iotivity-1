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
#include "JniOcStack.h"

#ifndef _Included_org_iotivity_base_OcRepresentation
#define _Included_org_iotivity_base_OcRepresentation

using namespace OC;

class JniOcRepresentation
{
public:
    static OCRepresentation* getOCRepresentationPtr(JNIEnv *env, jobject thiz);
};

#ifdef __cplusplus
    extern "C" {
#endif

    /*
    * Class:     org_iotivity_base_OcRepresentation
    * Method:    getValueInt
    * Signature: (Ljava/lang/String;)I
    */
    JNIEXPORT jint JNICALL Java_org_iotivity_base_OcRepresentation_getValueInt
        (JNIEnv *, jobject, jstring);

    /*
    * Class:     org_iotivity_base_OcRepresentation
    * Method:    getValueBool
    * Signature: (Ljava/lang/String;)Z
    */
    JNIEXPORT jboolean JNICALL Java_org_iotivity_base_OcRepresentation_getValueBool
        (JNIEnv *, jobject, jstring);

    /*
    * Class:     org_iotivity_base_OcRepresentation
    * Method:    getValueString
    * Signature: (Ljava/lang/String;)Ljava/lang/String;
    */
    JNIEXPORT jstring JNICALL Java_org_iotivity_base_OcRepresentation_getValueString
        (JNIEnv *, jobject, jstring);

    /*
    * Class:     org_iotivity_base_OcRepresentation
    * Method:    setValueInt
    * Signature: (Ljava/lang/String;I)V
    */
    JNIEXPORT void JNICALL Java_org_iotivity_base_OcRepresentation_setValueInt
        (JNIEnv *, jobject, jstring, jint);

    /*
    * Class:     org_iotivity_base_OcRepresentation
    * Method:    setValueBool
    * Signature: (Ljava/lang/String;Z)V
    */
    JNIEXPORT void JNICALL Java_org_iotivity_base_OcRepresentation_setValueBool
        (JNIEnv *, jobject, jstring, jboolean);

    /*
    * Class:     org_iotivity_base_OcRepresentation
    * Method:    setValueString
    * Signature: (Ljava/lang/String;Ljava/lang/String;)V
    */
    JNIEXPORT void JNICALL Java_org_iotivity_base_OcRepresentation_setValueString
        (JNIEnv *, jobject, jstring, jstring);

    /*
    * Class:     org_iotivity_base_OcRepresentation
    * Method:    getUri
    * Signature: ()Ljava/lang/String;
    */
    JNIEXPORT jstring JNICALL Java_org_iotivity_base_OcRepresentation_getUri
        (JNIEnv *, jobject);

    /*
    * Class:     org_iotivity_base_OcRepresentation
    * Method:    setUri
    * Signature: (Ljava/lang/String;)V
    */
    JNIEXPORT void JNICALL Java_org_iotivity_base_OcRepresentation_setUri
        (JNIEnv *, jobject, jstring);

    /*
    * Class:     org_iotivity_base_OcRepresentation
    * Method:    hasAttribute
    * Signature: (Ljava/lang/String;)Z
    */
    JNIEXPORT jboolean JNICALL Java_org_iotivity_base_OcRepresentation_hasAttribute
        (JNIEnv *, jobject, jstring);

    /*
    * Class:     org_iotivity_base_OcRepresentation
    * Method:    create
    * Signature: ()V
    */
    JNIEXPORT void JNICALL Java_org_iotivity_base_OcRepresentation_create
        (JNIEnv *, jobject);

    /*
    * Class:     org_iotivity_base_OcRepresentation
    * Method:    dispose
    * Signature: ()V
    */
    JNIEXPORT void JNICALL Java_org_iotivity_base_OcRepresentation_dispose
        (JNIEnv *, jobject, jboolean);

#ifdef __cplusplus
}
#endif
#endif