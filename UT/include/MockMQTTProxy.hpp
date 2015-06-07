#include <gmock/gmock.h>
#include <IMQTTProxy.hpp>


class MockMQTTProxy : public IMQTTProxy
{
public:
    MOCK_METHOD0(publish, bool(std::string topic, std::string payload));
};
