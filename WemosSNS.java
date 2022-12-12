package com.amazonaws.lambda.demo;

import com.amazonaws.auth.AWSStaticCredentialsProvider;
import com.amazonaws.auth.BasicAWSCredentials;
import com.amazonaws.regions.Regions;
import com.amazonaws.services.lambda.runtime.Context;
import com.amazonaws.services.lambda.runtime.RequestHandler;
import com.amazonaws.services.sns.AmazonSNS;
import com.amazonaws.services.sns.AmazonSNSClientBuilder;
import com.amazonaws.services.sns.model.PublishRequest;
import com.amazonaws.services.sns.model.PublishResult;
import com.google.gson.JsonElement;
import com.google.gson.JsonParser;

public class  WemosSNS implements RequestHandler<Object, String> {

    @Override
    public String handleRequest(Object input, Context context) {
    	  context.getLogger().log("Input: " + input);
          String json = ""+input;
          JsonParser parser = new JsonParser();
          JsonElement element = parser.parse(json);
         
          String state = element.getAsJsonObject().get("state").getAsString();
		final	String	AccessKey=" ";
		final	String	SecretKey=" ";
		final	String	topicArn=" "; //	이전 단계에서 생성한	SNS	주제에 대한	Arn을 지정
		BasicAWSCredentials	awsCreds	= new BasicAWSCredentials(AccessKey,	SecretKey);		
		AmazonSNS	sns	=	AmazonSNSClientBuilder.standard()
														.withRegion(Regions.AP_NORTHEAST_2)
														.withCredentials( new AWSStaticCredentialsProvider(awsCreds) )
														.build();
		 final String subject = "Alarm";  
		 final String msg0 = state + " taged RFID";       
	     final String msg1 = "Shocked";
	       
	     if (state.equals("0") ) { //0번이 들어오면 충격을 받았다는 메세지를 보낸다.
	           PublishRequest publishRequest = new PublishRequest(topicArn, msg1, subject);
	           PublishResult publishResponse = sns.publish(publishRequest);
	           System.out.println("0");
	       }
	     else if (state.equals("DaHyun")) { //해당학생이 태그를 찍었다는 메세지를 보낸다.
	           PublishRequest publishRequest = new PublishRequest(topicArn, msg0, subject);
	           PublishResult publishResponse = sns.publish(publishRequest);
	       }
	     else if (state.equals("MinJi")) {
	           PublishRequest publishRequest = new PublishRequest(topicArn, msg0, subject);
	           PublishResult publishResponse = sns.publish(publishRequest);
	       }
	     else if (state.equals("GunWo")) {
	           PublishRequest publishRequest = new PublishRequest(topicArn, msg0, subject);
	           PublishResult publishResponse = sns.publish(publishRequest);
	       }
	     else if (state.equals("DongHyun")) {
	           PublishRequest publishRequest = new PublishRequest(topicArn, msg0, subject);
	           PublishResult publishResponse = sns.publish(publishRequest);
	       }

	     return subject + state;
	   }

	}
    

