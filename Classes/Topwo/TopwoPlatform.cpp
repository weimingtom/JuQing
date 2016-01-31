/*
类型         相应的签名
boolean        Z
byte           B
char           C
short          S
int            I
long           L
float          F
double         D
void           V
object         L用/分隔包的完整类名：   Ljava/lang/String;
Array          [签名          [I      [Ljava/lang/Object;
Method         (参数1类型签名 参数2类型签名···)返回值类型签名
*/

/*
Java类型      别名　　        本地类型　　                字节(bit)
boolean     jboolean      unsigned char　　          8, unsigned
byte        jbyte         signed char　　　　        8
char        jchar         unsigned short　　         16, unsigned
short       jshort        short　　　                16
int         jint          long　　　　                32
long        jlong         __int64　　　　           64
float       jfloat        float　　　                   32
double      jdouble       double　　　             64
void        void        　　　　                        n/a　　
Object      _jobject      *jobject
*/
/*
* Class:     com_ashqal_test_LearnJNI
* Method:    displayHelloWorld
* Signature: ()V
*/
#include "TopwoPlatform.h"
#include "Topwo.h"
//安卓平台
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "platform/android/jni/JniHelper.h"
#endif

#define CLASS_PATH "com/topwo/platform/TopwoAndroid"

//以C的方式编译，安卓本地方法才能找得到
extern "C"
{
	// jint 
	//      表示JAVA的本地方法返回类型为int
	// 
	// Java_com_youmi_android_cocos2dx_demo_MainActivity_pointsBalanceChange
	//      Java_开头是必须的
	//      com_youmi_android_cocos2dx_demo_MainActivity 对应包名:com.youmi.android.cocos2dx.demo下的类MainActivity
	//      pointsBalanceChange 是类MainActivity下定义的方法名
	//
	// JNIEnv *env, jobject thiz 
	//      是两个必须要有参数
	//
	// jint points
	//      对应JAVA本地方法的参数private native int pointsBalanceChang（int points）
	//
	// 如开发者的一个类Test在包com.a.b中，而且类中的定义一个本地函数public native void doSomething(int p);
	// 那么这里应该写void Java_com_a_b_Test_doSomething( JNIEnv *env, jobject thiz, jint p ) { //内部逻辑}
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	void Java_com_topwo_platform_TopwoAndroid_nativeGameOut(JNIEnv *env, jobject thiz)
	{
		Topwo::getInstance()->getTopwoPlatform()->exitCallback();
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
	//安卓平台
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	//下面是利用jnihelper类来调用Android Static  
	JniMethodInfo methodInfo;  //jni函数信息结构体  
	/*getStaticMethodInfo获取到MethodId和ClassId,ClassID通过穿进去的Activity即类名获取，MethodId通过函数名获取*/
	bool isHave = JniHelper::getStaticMethodInfo(methodInfo, CLASS_PATH, "callShowExitDialog", "()V");
	if (isHave)
	{
		/*调用这个函数*/
		methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID);
	}
#endif

}

//打开网址
void TopwoPlatform::callOpenURL(const char* pszUrl)
{
	//安卓平台
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	//下面是利用jnihelper类来调用Android Static  
	JniMethodInfo methodInfo;  //jni函数信息结构体  
	/*getStaticMethodInfo获取到MethodId和ClassId,ClassID通过穿进去的Activity即类名获取，MethodId通过函数名获取*/
	bool isHave = JniHelper::getStaticMethodInfo(methodInfo, CLASS_PATH, "callOpenURL", "(Ljava/lang/String;)V");
	if (isHave)
	{
		jstring StringArg1 = methodInfo.env->NewStringUTF(pszUrl);
		/*调用这个函数*/
		methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, StringArg1);
		methodInfo.env->DeleteLocalRef(StringArg1);
	}
#endif
}
void TopwoPlatform::callPay(int id, CCObject* target, SEL_CallFuncI callfun)
{
	__callbackListener = target;
	__callbackfunc = callfun;
	//安卓平台
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	//下面是利用jnihelper类来调用Android Static  
	JniMethodInfo methodInfo;  //jni函数信息结构体  
	/*getStaticMethodInfo获取到MethodId和ClassId,ClassID通过穿进去的Activity即类名获取，MethodId通过函数名获取*/
	bool isHave = JniHelper::getStaticMethodInfo(methodInfo, CLASS_PATH, "callPay", "(I)V");
	if (isHave)
	{
		/*调用这个函数*/
		methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, id);
	}
#endif
}

//支付回调
void TopwoPlatform::payCallback(int status)
{
	if (__callbackListener&&__callbackfunc)
		(__callbackListener->*__callbackfunc)(status);
}
//退出回调
void TopwoPlatform::exitCallback()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.", "Alert");
#else
	Topwo::getInstance()->getTopwoData()->writeData();
	CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
#endif
}

//设置当前玩家的等级
void TopwoPlatform::setLevel(int level)
{
	//安卓平台
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	//下面是利用jnihelper类来调用Android Static  
	JniMethodInfo methodInfo;  //jni函数信息结构体  
	/*getStaticMethodInfo获取到MethodId和ClassId,ClassID通过穿进去的Activity即类名获取，MethodId通过函数名获取*/
	bool isHave = JniHelper::getStaticMethodInfo(methodInfo, CLASS_PATH, "setLevel", "(I)V");
	if (isHave)
	{
		/*调用这个函数*/
		methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID,level);
	}
#endif
}
//游戏关卡开始
void TopwoPlatform::levelBegin(const char* levelId)
{
	//安卓平台
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	//下面是利用jnihelper类来调用Android Static  
	JniMethodInfo methodInfo;  //jni函数信息结构体  
	/*getStaticMethodInfo获取到MethodId和ClassId,ClassID通过穿进去的Activity即类名获取，MethodId通过函数名获取*/
	bool isHave = JniHelper::getStaticMethodInfo(methodInfo, CLASS_PATH, "levelBegin", "(Ljava/lang/String;)V");
	if (isHave)
	{
		jstring jstr = methodInfo.env->NewStringUTF(levelId);
		/*调用这个函数*/
		methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID,jstr);
	}
#endif
}

//游戏关卡通过
void TopwoPlatform::levelComplete(const char* levelId)
{
	//安卓平台
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	//下面是利用jnihelper类来调用Android Static  
	JniMethodInfo methodInfo;  //jni函数信息结构体  
	/*getStaticMethodInfo获取到MethodId和ClassId,ClassID通过穿进去的Activity即类名获取，MethodId通过函数名获取*/
	bool isHave = JniHelper::getStaticMethodInfo(methodInfo, CLASS_PATH, "levelComplete", "(Ljava/lang/String;)V");
	if (isHave)
	{
		jstring jstr = methodInfo.env->NewStringUTF(levelId);
		/*调用这个函数*/
		methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID,jstr);
	}
#endif
}

//游戏关卡通关失败
void TopwoPlatform::levelIdFail(const char* levelId)
{
	//安卓平台
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	//下面是利用jnihelper类来调用Android Static  
	JniMethodInfo methodInfo;  //jni函数信息结构体  
	/*getStaticMethodInfo获取到MethodId和ClassId,ClassID通过穿进去的Activity即类名获取，MethodId通过函数名获取*/
	bool isHave = JniHelper::getStaticMethodInfo(methodInfo, CLASS_PATH, "levelIdFail", "(Ljava/lang/String;)V");
	if (isHave)
	{
		jstring jstr = methodInfo.env->NewStringUTF(levelId);
		/*调用这个函数*/
		methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID,jstr);
	}
#endif
}

//记录玩家虚拟币留存总量
void TopwoPlatform::setCoinNum(int coinNum, const char* coinType)
{
	//安卓平台
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	//下面是利用jnihelper类来调用Android Static  
	JniMethodInfo methodInfo;  //jni函数信息结构体  
	/*getStaticMethodInfo获取到MethodId和ClassId,ClassID通过穿进去的Activity即类名获取，MethodId通过函数名获取*/
	bool isHave = JniHelper::getStaticMethodInfo(methodInfo, CLASS_PATH, "setCoinNum", "(ILjava/lang/String;)V");
	if (isHave)
	{
		jstring jstr = methodInfo.env->NewStringUTF(coinType);
		/*调用这个函数*/
		methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID,coinNum,jstr);
	}
#endif
}

//自定义事件
void TopwoPlatform::onEvent(const char* eventId)
{
	//安卓平台
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	//下面是利用jnihelper类来调用Android Static  
	JniMethodInfo methodInfo;  //jni函数信息结构体  
	/*getStaticMethodInfo获取到MethodId和ClassId,ClassID通过穿进去的Activity即类名获取，MethodId通过函数名获取*/
	bool isHave = JniHelper::getStaticMethodInfo(methodInfo, CLASS_PATH, "onEvent", "(Ljava/lang/String;)V");
	if (isHave)
	{
		jstring jstr = methodInfo.env->NewStringUTF(eventId);
		/*调用这个函数*/
		methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID,jstr);
	}
#endif
}



//展示对话框积分墙
void TopwoPlatform::showOffersWallDialog()
{
	//安卓平台
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	//下面是利用jnihelper类来调用Android Static  
	JniMethodInfo methodInfo;  //jni函数信息结构体  
	/*getStaticMethodInfo获取到MethodId和ClassId,ClassID通过穿进去的Activity即类名获取，MethodId通过函数名获取*/
	bool isHave = JniHelper::getStaticMethodInfo(methodInfo, CLASS_PATH, "showOffersWallDialog", "()V");
	if (isHave)
	{
		/*调用这个函数*/
		methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID);
	}
#endif
}

//展示对话框分享
void TopwoPlatform::showShareWallDialog()
{
	//安卓平台
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	//下面是利用jnihelper类来调用Android Static  
	JniMethodInfo methodInfo;  //jni函数信息结构体  
	/*getStaticMethodInfo获取到MethodId和ClassId,ClassID通过穿进去的Activity即类名获取，MethodId通过函数名获取*/
	bool isHave = JniHelper::getStaticMethodInfo(methodInfo, CLASS_PATH, "showShareWallDialog", "()V");
	if (isHave)
	{
		/*调用这个函数*/
		methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID);
	}
#endif
}

//奖励
void TopwoPlatform::awardPoints(float f)
{
	//安卓平台
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	//下面是利用jnihelper类来调用Android Static  
	JniMethodInfo methodInfo;  //jni函数信息结构体  
	/*getStaticMethodInfo获取到MethodId和ClassId,ClassID通过穿进去的Activity即类名获取，MethodId通过函数名获取*/
	bool isHave = false;//JniHelper::getStaticMethodInfo(methodInfo, CLASS_PATH, "awardPoints", "(F)V");
	if (isHave)
	{
		/*调用这个函数*/
		methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID,f);
	}
#endif
}
//消费
void TopwoPlatform::spendPoints(float f)
{
	//安卓平台
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	//下面是利用jnihelper类来调用Android Static  
	JniMethodInfo methodInfo;  //jni函数信息结构体  
	/*getStaticMethodInfo获取到MethodId和ClassId,ClassID通过穿进去的Activity即类名获取，MethodId通过函数名获取*/
	bool isHave = JniHelper::getStaticMethodInfo(methodInfo, CLASS_PATH, "spendPoints", "(F)V");//false;//
	if (isHave)
	{
		/*调用这个函数*/
		methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID,f);
	}
#endif
}
//查询积分
float TopwoPlatform::queryPoints()
{
	float ret = 0.0f;
	//安卓平台
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	//下面是利用jnihelper类来调用Android Static  
	JniMethodInfo methodInfo;  //jni函数信息结构体  
	/*getStaticMethodInfo获取到MethodId和ClassId,ClassID通过穿进去的Activity即类名获取，MethodId通过函数名获取*/
	bool isHave = false;//JniHelper::getStaticMethodInfo(methodInfo, CLASS_PATH, "queryPoints", "()F");
	if (isHave)
	{
		/*调用这个函数*/
		ret=methodInfo.env->CallStaticFloatMethod(methodInfo.classID, methodInfo.methodID);
	}
#endif
	return ret;
}
