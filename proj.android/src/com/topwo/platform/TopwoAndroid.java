package com.topwo.platform;

import org.json.JSONException;
import org.json.JSONObject;

import com.topwo.juqing.JuQing;
import com.topwo.juqing.R;

import android.app.Activity;
import android.app.AlertDialog;
import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.net.Uri;
import android.os.Handler;
import android.os.Message;
import android.util.JsonReader;
import android.widget.TextView;
import android.widget.Toast;

public class TopwoAndroid{
	public static Context main_context;
	public static TopwoAndroid ta;
	
	
	/**
	 * 显示积分余额的控件
	 */
	TextView mTextViewPoints;
	public TopwoAndroid(Activity main) {
		// TODO Auto-generated constructor stub
		ta=this;
		main_context=main;
	}

    /*****消息类型****/  
    private static final int SHOW_EXIT_DIALOG = 0;
    private static final int PAY = 1;
    private static final int PAY_CALLBACK = 2;
    private static final int SHOW_OFFERS_WALL_DIALOG = 3;
    private static final int SHOW_SHARE_WALL_DIALOG = 4;
	public static Handler handler = new Handler(){
        @Override
        public void handleMessage(Message msg){
            switch(msg.what){
            case SHOW_EXIT_DIALOG:
            	showExit();
				break;
            case PAY:
            	break;
            case PAY_CALLBACK:
				ta.payCallback((Integer)msg.obj);
            	break;
            default:
            	break;
            }
            super.handleMessage(msg);
        }
    };
    
    public static void showExit() {
   		new AlertDialog.Builder(main_context)
        .setIcon(R.drawable.icon)
        .setTitle(R.string.app_name)
        .setMessage("确定退出游戏？")
        .setNegativeButton("取消",
                new DialogInterface.OnClickListener() {
                    @Override
                    public void onClick(DialogInterface dialog,int which) {  
                    }
                })
        .setPositiveButton("确定",
                new DialogInterface.OnClickListener() {  
                    public void onClick(DialogInterface dialog,int whichButton) {
                    	nativeGameOut();
                    }
                }).show();
   	}
    //发送消息封装
	private synchronized static void sendMsgToHandler(int type, Object obj) {
		Message msg = handler.obtainMessage(type);
		msg.obj = obj;
		msg.sendToTarget();
	}
    //显示退出对话框
    public static void callShowExitDialog()
    {
    	sendMsgToHandler(SHOW_EXIT_DIALOG, null);
    }
    
    public static void callOpenURL(String url)
    {
	    Intent i = new Intent(Intent.ACTION_VIEW);
	    i.setData(Uri.parse(url));
	    main_context.startActivity(i);
    }
    
    //调用sdk支付
    static String pay_title = "商品标题";
    static String price = "0";
    public static void callPay(int id)
    {
    	if(id == 1)
    	{
    		pay_title = "强行解锁下一关";
    		price = "1";
    	}
    	else if(id == 2)
    	{
    		pay_title = "满血复活";
    		price = "1";
    	}
    	sendMsgToHandler(PAY, null);
    }
    
    

    //设置当前玩家的等级
    public static void setLevel(int level)
    {
    }
    //游戏关卡开始
    public static void levelBegin(String levelId)
    {
    }
    
    //游戏关卡通过
    public static void levelComplete(String levelId)
    {
    }
    
    //游戏关卡通关失败
    public static void levelIdFail(String levelId)
    {
    }
    
    //记录玩家虚拟币留存总量
    public static void setCoinNum(int coinNum,String coinType)
    {
    }
    
    //自定义事件
    public static void onEvent(String eventId)
    {
    }
    
    void payCallback(final int status)
    {
    	((JuQing)main_context).runOnGLThread(new Runnable() {
			
			@Override
			public void run() {
				// TODO Auto-generated method stub
				nativePayCallback(status);
			}
		});
    }
    
    /**积分墙**/
    //展示对话框积分墙
    public static void showOffersWallDialog()
    {
        Message msg=new Message();
        msg.what=SHOW_OFFERS_WALL_DIALOG;
        msg.obj="showmessage demos";//可以传递参数  
        handler.sendMessage(msg);
    }
    //展示对话框分享
    public static void showShareWallDialog()
    {
        Message msg=new Message();
        msg.what=SHOW_SHARE_WALL_DIALOG;
        msg.obj="showmessage demos";//可以传递参数  
        handler.sendMessage(msg);
    }
    //奖励
    public static void awardPoints(float f)
    {
    }
    //消费
    public static void spendPoints(float f)
    {
    	System.out.println("DDDDDDDD" + f);
    }
    
    //查询积分
    public static float queryPoints()
    {
    	float pointsBalance = 0.f;
    	return pointsBalance;
    }
    public native static void nativeGameOut();
    public native static void nativePayCallback(int status);
}
