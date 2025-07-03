#include "gmock/gmock.h"
#include "device_driver.h"

#include "Mock_FlashMemoryDevice.cpp"

using namespace testing;

class DeviceDriverFixture : public Test
{
protected:
	void SetUp() override
	{
		mock_hardware = new MockFlashMemoryDevice();
		driver = mock_hardware;
	}

public:
	MockFlashMemoryDevice* mock_hardware{ nullptr };
	DeviceDriver driver{ nullptr };
};

TEST_F(DeviceDriverFixture, ReadFromHW_HaveToReadFiveTimesInValidCase) {
	// act, assert
	EXPECT_CALL(*mock_hardware, read)
		.Times(5)
		.WillRepeatedly(Return(0xA));

	int data = driver.read(0xFF);
}

TEST_F(DeviceDriverFixture, ReadFromHW_DifferentData) {
	// act
	EXPECT_CALL(*mock_hardware, read)
		.Times(4)
		.WillOnce(Return(0xAA))
		.WillOnce(Return(0xAA))
		.WillOnce(Return(0xAA))
		.WillOnce(Return(0xFF))
		.WillOnce(Return(0xAA));

	EXPECT_THROW(driver.read(0xFF), std::exception);
}

int main() {
	::testing::InitGoogleMock();
	return RUN_ALL_TESTS();
}