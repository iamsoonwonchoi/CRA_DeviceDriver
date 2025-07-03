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
	void ReadFiveTimesInValidCase(int data)
	{
		EXPECT_CALL(*mock_hardware, read)
			.Times(5)
			.WillRepeatedly(Return(data));
	}

	static const int EMPTY = 0xFF;
	static const int DATA_A = 0xA;
	static const int DATA_B = 0xB;
	static const int TARGET_ADDRESS = 0xFF;

	MockFlashMemoryDevice* mock_hardware{ nullptr };
	DeviceDriver driver{ nullptr };
};

TEST_F(DeviceDriverFixture, ReadFromHW_HaveToReadFiveTimesInValidCase) {
	ReadFiveTimesInValidCase(DATA_A);

	int data = driver.read(TARGET_ADDRESS);
	
	EXPECT_EQ(data, DATA_A);
}

TEST_F(DeviceDriverFixture, ReadFromHW_DifferentData) {
	EXPECT_CALL(*mock_hardware, read)
		.Times(4)
		.WillOnce(Return(DATA_A))
		.WillOnce(Return(DATA_A))
		.WillOnce(Return(DATA_A))
		.WillOnce(Return(EMPTY))
		.WillOnce(Return(DATA_A));

	EXPECT_THROW(driver.read(TARGET_ADDRESS), std::exception);
}

TEST_F(DeviceDriverFixture, WriteFromHW_NotEmptyCase) {
	ReadFiveTimesInValidCase(DATA_A);

	EXPECT_CALL(*mock_hardware, write).Times(1);

	EXPECT_THROW(driver.write(TARGET_ADDRESS, DATA_A), std::exception);
}

TEST_F(DeviceDriverFixture, WriteFromHW_EmptyCase) {
	ReadFiveTimesInValidCase(EMPTY);

	EXPECT_CALL(*mock_hardware, write).Times(1);

	driver.write(TARGET_ADDRESS, DATA_B);
}

int main() {
	::testing::InitGoogleMock();
	return RUN_ALL_TESTS();
}