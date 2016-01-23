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
	 * ��ʾ�������Ŀؼ�
	 */
	TextView mTextViewPoints;
	public TopwoAndroid(Activity main) {
		// TODO Auto-generated constructor stub
		ta=this;
		main_context=main;
	}

    /*****��Ϣ����****/  
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
        .setMessage("ȷ���˳���Ϸ��")
        .setNegativeButton("ȡ��",
                new DialogInterface.OnClickListener() {
                    @Override
                    public void onClick(DialogInterface dialog,int which) {  
                    }
                })
        .setPositiveButton("ȷ��",
                new DialogInterface.OnClickListener() {  
                    public void onClick(DialogInterface dialog,int whichButton) {
                    	nativeGameOut();
                    }
                }).show();
   	}
    //������Ϣ��װ
	private synchronized static void sendMsgToHandler(int type, Object obj) {
		Message msg = handler.obtainMessage(type);
		msg.obj = obj;
		msg.sendToTarget();
	}
    //��ʾ�˳��Ի���
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
    
    //����sdk֧��
    static String pay_title = "��Ʒ����";
    static String price = "0";
    public static void callPay(int id)
    {
    	if(id == 1)
    	{
    		pay_title = "ǿ�н�����һ��";
    		price = "1";
    	}
    	else if(id == 2)
    	{
    		pay_title = "��Ѫ����";
    		price = "1";
    	}
    	sendMsgToHandler(PAY, null);
    }
    
    

    //���õ�ǰ��ҵĵȼ�
    public static void setLevel(int level)
    {
    }
    //��Ϸ�ؿ���ʼ
    public static void levelBegin(String levelId)
    {
    }
    
    //��Ϸ�ؿ�ͨ��
    public static void levelComplete(String levelId)
    {
    }
    
    //��Ϸ�ؿ�ͨ��ʧ��
    public static void levelIdFail(String levelId)
    {
    }
    
    //��¼����������������
    public static void setCoinNum(int coinNum,String coinType)
    {
    }
    
    //�Զ����¼�
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
    
    /**����ǽ**/
    //չʾ�Ի������ǽ
    public static void showOffersWallDialog()
    {
        Message msg=new Message();
        msg.what=SHOW_OFFERS_WALL_DIALOG;
        msg.obj="showmessage demos";//���Դ��ݲ���  
        handler.sendMessage(msg);
    }
    //չʾ�Ի������
    public static void showShareWallDialog()
    {
        Message msg=new Message();
        msg.what=SHOW_SHARE_WALL_DIALOG;
        msg.obj="showmessage demos";//���Դ��ݲ���  
        handler.sendMessage(msg);
    }
    //����
    public static void awardPoints(float f)
    {
    }
    //����
    public static void spendPoints(float f)
    {
    	System.out.println("DDDDDDDD" + f);
    }
    
    //��ѯ����
    public static float queryPoints()
    {
    	float pointsBalance = 0.f;
    	return pointsBalance;
    }
    public native static void nativeGameOut();
    public native static void nativePayCallback(int status);
}
