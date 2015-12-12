/*
����         ��Ӧ��ǩ��
boolean        Z
byte           B
char           C
short          S
int            I
long           L
float          F
double         D
void           V
object         L��/�ָ���������������   Ljava/lang/String;
Array          [ǩ��          [I      [Ljava/lang/Object;
Method         (����1����ǩ�� ����2����ǩ��������)����ֵ����ǩ��
*/

/*
Java����      ��������        �������͡���                �ֽ�(bit)
boolean     jboolean      unsigned char����          8, unsigned
byte        jbyte         signed char��������        8
char        jchar         unsigned short����         16, unsigned
short       jshort        short������                16
int         jint          long��������                32
long        jlong         __int64��������           64
float       jfloat        float������                   32
double      jdouble       double������             64
void        void        ��������                        n/a����
Object      _jobject      *jobject
*/
/*
* Class:     com_ashqal_test_LearnJNI
* Method:    displayHelloWorld
* Signature: ()V
*/
#include "TopwoPlatform.h"
#include "Topwo.h"
//��׿ƽ̨
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "platform/android/jni/JniHelper.h"
#endif

#define CLASS_PATH "com/topwo/platform/TopwoAndroid"

//��C�ķ�ʽ���룬��׿���ط��������ҵõ�
extern "C"
{
	// jint 
	//      ��ʾJAVA�ı��ط�����������Ϊint
	// 
	// Java_com_youmi_android_cocos2dx_demo_MainActivity_pointsBalanceChange
	//      Java_��ͷ�Ǳ����
	//      com_youmi_android_cocos2dx_demo_MainActivity ��Ӧ����:com.youmi.android.cocos2dx.demo�µ���MainActivity
	//      pointsBalanceChange ����MainActivity�¶���ķ�����
	//
	// JNIEnv *env, jobject thiz 
	//      ����������Ҫ�в���
	//
	// jint points
	//      ��ӦJAVA���ط����Ĳ���private native int pointsBalanceChang��int points��
	//
	// �翪���ߵ�һ����Test�ڰ�com.a.b�У��������еĶ���һ�����غ���public native void doSomething(int p);
	// ��ô����Ӧ��дvoid Java_com_a_b_Test_doSomething( JNIEnv *env, jobject thiz, jint p ) { //�ڲ��߼�}
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	void Java_com_topwo_platform_TopwoAndroid_nativeGameOut(JNIEnv *env, jobject thiz)
	{
	}
	void Java_com_topwo_platform_TopwoAndroid_nativePayCallback(JNIEnv *env, jobject thiz, int status)
	{
		Topwo::getInstance()->getTopwoPlatform()->payCallback(status);
	}
#endif

}

TopwoPlatform::TopwoPlatform(){}
TopwoPlatform::~TopwoPlatform(){}
bool TopwoPlatform::init()
{
	return true;
}

void TopwoPlatform::callShowExitDialog()
{
	//��׿ƽ̨
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	//����������jnihelper��������Android Static  
	JniMethodInfo methodInfo;  //jni������Ϣ�ṹ��  
	/*getStaticMethodInfo��ȡ��MethodId��ClassId,ClassIDͨ������ȥ��Activity��������ȡ��MethodIdͨ����������ȡ*/
	bool isHave = JniHelper::getStaticMethodInfo(methodInfo, CLASS_PATH, "callShowExitDialog", "()V");
	if (isHave)
	{
		/*�����������*/
		methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID);
	}
#endif

}

//����ַ
void TopwoPlatform::callOpenURL(const char* pszUrl)
{
	//��׿ƽ̨
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	//����������jnihelper��������Android Static  
	JniMethodInfo methodInfo;  //jni������Ϣ�ṹ��  
	/*getStaticMethodInfo��ȡ��MethodId��ClassId,ClassIDͨ������ȥ��Activity��������ȡ��MethodIdͨ����������ȡ*/
	bool isHave = JniHelper::getStaticMethodInfo(methodInfo, CLASS_PATH, "callOpenURL", "(Ljava/lang/String;)V");
	if (isHave)
	{
		jstring StringArg1 = methodInfo.env->NewStringUTF(pszUrl);
		/*�����������*/
		methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, StringArg1);
		methodInfo.env->DeleteLocalRef(StringArg1);
	}
#endif
}
void TopwoPlatform::callPay(int id, CCObject* target, SEL_CallFuncI callfun)
{
	__callbackListener = target;
	__callbackfunc = callfun;
	//��׿ƽ̨
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	//����������jnihelper��������Android Static  
	JniMethodInfo methodInfo;  //jni������Ϣ�ṹ��  
	/*getStaticMethodInfo��ȡ��MethodId��ClassId,ClassIDͨ������ȥ��Activity��������ȡ��MethodIdͨ����������ȡ*/
	bool isHave = JniHelper::getStaticMethodInfo(methodInfo, CLASS_PATH, "callPay", "(I)V");
	if (isHave)
	{
		/*�����������*/
		methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, id);
	}
#endif
}

//֧���ص�
void TopwoPlatform::payCallback(int status)
{
	if (__callbackListener&&__callbackfunc)
		(__callbackListener->*__callbackfunc)(status);
}

//���õ�ǰ��ҵĵȼ�
void TopwoPlatform::setLevel(int level)
{
	//��׿ƽ̨
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	//����������jnihelper��������Android Static  
	JniMethodInfo methodInfo;  //jni������Ϣ�ṹ��  
	/*getStaticMethodInfo��ȡ��MethodId��ClassId,ClassIDͨ������ȥ��Activity��������ȡ��MethodIdͨ����������ȡ*/
	bool isHave = JniHelper::getStaticMethodInfo(methodInfo, CLASS_PATH, "setLevel", "(I)V");
	if (isHave)
	{
		/*�����������*/
		methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID,level);
	}
#endif
}
//��Ϸ�ؿ���ʼ
void TopwoPlatform::levelBegin(const char* levelId)
{
	//��׿ƽ̨
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	//����������jnihelper��������Android Static  
	JniMethodInfo methodInfo;  //jni������Ϣ�ṹ��  
	/*getStaticMethodInfo��ȡ��MethodId��ClassId,ClassIDͨ������ȥ��Activity��������ȡ��MethodIdͨ����������ȡ*/
	bool isHave = JniHelper::getStaticMethodInfo(methodInfo, CLASS_PATH, "levelBegin", "(Ljava/lang/String;)V");
	if (isHave)
	{
		jstring jstr = methodInfo.env->NewStringUTF(levelId);
		/*�����������*/
		methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID,jstr);
	}
#endif
}

//��Ϸ�ؿ�ͨ��
void TopwoPlatform::levelComplete(const char* levelId)
{
	//��׿ƽ̨
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	//����������jnihelper��������Android Static  
	JniMethodInfo methodInfo;  //jni������Ϣ�ṹ��  
	/*getStaticMethodInfo��ȡ��MethodId��ClassId,ClassIDͨ������ȥ��Activity��������ȡ��MethodIdͨ����������ȡ*/
	bool isHave = JniHelper::getStaticMethodInfo(methodInfo, CLASS_PATH, "levelComplete", "(Ljava/lang/String;)V");
	if (isHave)
	{
		jstring jstr = methodInfo.env->NewStringUTF(levelId);
		/*�����������*/
		methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID,jstr);
	}
#endif
}

//��Ϸ�ؿ�ͨ��ʧ��
void TopwoPlatform::levelIdFail(const char* levelId)
{
	//��׿ƽ̨
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	//����������jnihelper��������Android Static  
	JniMethodInfo methodInfo;  //jni������Ϣ�ṹ��  
	/*getStaticMethodInfo��ȡ��MethodId��ClassId,ClassIDͨ������ȥ��Activity��������ȡ��MethodIdͨ����������ȡ*/
	bool isHave = JniHelper::getStaticMethodInfo(methodInfo, CLASS_PATH, "levelIdFail", "(Ljava/lang/String;)V");
	if (isHave)
	{
		jstring jstr = methodInfo.env->NewStringUTF(levelId);
		/*�����������*/
		methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID,jstr);
	}
#endif
}

//��¼����������������
void TopwoPlatform::setCoinNum(int coinNum, const char* coinType)
{
	//��׿ƽ̨
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	//����������jnihelper��������Android Static  
	JniMethodInfo methodInfo;  //jni������Ϣ�ṹ��  
	/*getStaticMethodInfo��ȡ��MethodId��ClassId,ClassIDͨ������ȥ��Activity��������ȡ��MethodIdͨ����������ȡ*/
	bool isHave = JniHelper::getStaticMethodInfo(methodInfo, CLASS_PATH, "setCoinNum", "(ILjava/lang/String;)V");
	if (isHave)
	{
		jstring jstr = methodInfo.env->NewStringUTF(coinType);
		/*�����������*/
		methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID,coinNum,jstr);
	}
#endif
}

//�Զ����¼�
void TopwoPlatform::onEvent(const char* eventId)
{
	//��׿ƽ̨
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	//����������jnihelper��������Android Static  
	JniMethodInfo methodInfo;  //jni������Ϣ�ṹ��  
	/*getStaticMethodInfo��ȡ��MethodId��ClassId,ClassIDͨ������ȥ��Activity��������ȡ��MethodIdͨ����������ȡ*/
	bool isHave = JniHelper::getStaticMethodInfo(methodInfo, CLASS_PATH, "onEvent", "(Ljava/lang/String;)V");
	if (isHave)
	{
		jstring jstr = methodInfo.env->NewStringUTF(eventId);
		/*�����������*/
		methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID,jstr);
	}
#endif
}



//չʾ�Ի������ǽ
void TopwoPlatform::showOffersWallDialog()
{
	//��׿ƽ̨
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	//����������jnihelper��������Android Static  
	JniMethodInfo methodInfo;  //jni������Ϣ�ṹ��  
	/*getStaticMethodInfo��ȡ��MethodId��ClassId,ClassIDͨ������ȥ��Activity��������ȡ��MethodIdͨ����������ȡ*/
	bool isHave = JniHelper::getStaticMethodInfo(methodInfo, CLASS_PATH, "showOffersWallDialog", "()V");
	if (isHave)
	{
		/*�����������*/
		methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID);
	}
#endif
}

//չʾ�Ի������
void TopwoPlatform::showShareWallDialog()
{
	//��׿ƽ̨
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	//����������jnihelper��������Android Static  
	JniMethodInfo methodInfo;  //jni������Ϣ�ṹ��  
	/*getStaticMethodInfo��ȡ��MethodId��ClassId,ClassIDͨ������ȥ��Activity��������ȡ��MethodIdͨ����������ȡ*/
	bool isHave = JniHelper::getStaticMethodInfo(methodInfo, CLASS_PATH, "showShareWallDialog", "()V");
	if (isHave)
	{
		/*�����������*/
		methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID);
	}
#endif
}

//����
void TopwoPlatform::awardPoints(float f)
{
	//��׿ƽ̨
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	//����������jnihelper��������Android Static  
	JniMethodInfo methodInfo;  //jni������Ϣ�ṹ��  
	/*getStaticMethodInfo��ȡ��MethodId��ClassId,ClassIDͨ������ȥ��Activity��������ȡ��MethodIdͨ����������ȡ*/
	bool isHave = false;//JniHelper::getStaticMethodInfo(methodInfo, CLASS_PATH, "awardPoints", "(F)V");
	if (isHave)
	{
		/*�����������*/
		methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID,f);
	}
#endif
}
//����
void TopwoPlatform::spendPoints(float f)
{
	//��׿ƽ̨
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	//����������jnihelper��������Android Static  
	JniMethodInfo methodInfo;  //jni������Ϣ�ṹ��  
	/*getStaticMethodInfo��ȡ��MethodId��ClassId,ClassIDͨ������ȥ��Activity��������ȡ��MethodIdͨ����������ȡ*/
	bool isHave = false;//JniHelper::getStaticMethodInfo(methodInfo, CLASS_PATH, "spendPoints", "(F)V");
	if (isHave)
	{
		/*�����������*/
		methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID,f);
	}
#endif
}
//��ѯ����
float TopwoPlatform::queryPoints()
{
	float ret = 0.0f;
	//��׿ƽ̨
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	//����������jnihelper��������Android Static  
	JniMethodInfo methodInfo;  //jni������Ϣ�ṹ��  
	/*getStaticMethodInfo��ȡ��MethodId��ClassId,ClassIDͨ������ȥ��Activity��������ȡ��MethodIdͨ����������ȡ*/
	bool isHave = false;//JniHelper::getStaticMethodInfo(methodInfo, CLASS_PATH, "queryPoints", "()F");
	if (isHave)
	{
		/*�����������*/
		ret=methodInfo.env->CallStaticFloatMethod(methodInfo.classID, methodInfo.methodID);
	}
#endif
	return ret;
}
