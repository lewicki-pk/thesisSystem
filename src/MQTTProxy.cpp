#include "MQTTProxy.hpp"
#include <stdio.h>
#include <cstring>

bool MQTTProxy::publish(std::string topic, std::string payload)
{
//	MQTTPacket_connectData data = MQTTPacket_connectData_initializer;
//	int rc = 0;
//	char buf[200];
//	int buflen = sizeof(buf);
//	int mysock = 0;
//	MQTTString topicString = MQTTString_initializer;
//	int len = 0;
//	char *host = "localhost";
//	int port = 1883;
//
//	mysock = transport_open(host,port);
//	if(mysock < 0)
//		return mysock;
//
//	//printf("Sending to hostname %s port %d\n", host, port);
//
//	data.clientID.cstring = "me";
//	data.keepAliveInterval = 20;
//	data.cleansession = 1;
//	data.username.cstring = "testuser";
//	data.password.cstring = "testpassword";
//	data.MQTTVersion = 4;
//
//	len = MQTTSerialize_connect((unsigned char *)buf, buflen, &data);
//
//	strcpy(topicString.cstring, topic.c_str());
//
//      unsigned char * payloadBuf = (unsigned char *)payload.c_str();
//      //std::strcpy (payloadBuf, payload.c_str());
//
//
//	len += MQTTSerialize_publish((unsigned char *)(buf + len), buflen - len, 0, 0, 0, 0, topicString, payloadBuf, payload.length());
//
//	len += MQTTSerialize_disconnect((unsigned char *)(buf + len), buflen - len);
//
//	rc = transport_sendPacketBuffer(mysock,(unsigned char *)buf, len);
//	if (rc == len)
//		printf("Successfully published\n");
//	else
//		printf("Publish failed\n");
//
//	transport_close(mysock);
//
//	return 0;
}
