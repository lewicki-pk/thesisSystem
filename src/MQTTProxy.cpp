#include "MQTTProxy.hpp"

#define ADDRESS     "tcp://localhost:1883"
#define CLIENTID    "ExampleClientPub"
#define TIMEOUT     10000L

MQTTProxy::MQTTProxy() { }

MQTTProxy::~MQTTProxy()
{
    if (NULL != _instance)
        delete _instance;
}

MQTTProxy* MQTTProxy::_instance = NULL;

MQTTProxy* MQTTProxy::getInstance()
{
    if (NULL == _instance) {
        _instance = new MQTTProxy;
    }
    return _instance;
}

bool MQTTProxy::publish(std::string topic, std::string payload)
{
#ifndef UNIT_TEST
    MQTTClient client;
    MQTTClient_connectOptions conn_opts = MQTTClient_connectOptions_initializer;
    MQTTClient_message pubmsg = MQTTClient_message_initializer;
    MQTTClient_deliveryToken token;
    int rc;

    MQTTClient_create(&client, ADDRESS, CLIENTID,
        MQTTCLIENT_PERSISTENCE_NONE, NULL);
    conn_opts.keepAliveInterval = 20;
    conn_opts.cleansession = 1;

    if ((rc = MQTTClient_connect(client, &conn_opts)) != MQTTCLIENT_SUCCESS)
    {

    }
    pubmsg.payload = (void*)payload.c_str();
    pubmsg.payloadlen = payload.length();
    pubmsg.qos = 1;
    pubmsg.retained = 0;
    MQTTClient_publishMessage(client, topic.c_str(), &pubmsg, &token);

    rc = MQTTClient_waitForCompletion(client, token, TIMEOUT);

    MQTTClient_disconnect(client, 10000);
    MQTTClient_destroy(&client);
    return rc;
#endif
}

