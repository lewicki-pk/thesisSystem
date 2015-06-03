#include <gmock/gmock.h>
#include <ISensorDB.hpp>


class MockSensorDB : public ISensorDB
{
public:
    MOCK_METHOD0(begin, std::map<uint8_t, ISensorNode*>::iterator(void));
    MOCK_METHOD0(end, std::map<uint8_t, ISensorNode*>::iterator(void));
    MOCK_METHOD0(getSize, size_t());
    MOCK_METHOD1(isNodeInDB, bool(uint8_t id));
    MOCK_METHOD0(getAvailableNodeId, uint8_t());
    MOCK_METHOD1(addSensorNode, bool(ISensorNode* newNode));
    MOCK_METHOD0(clearDatabase, void());
    MOCK_METHOD1(updateReadings, void(Message msg));
};
