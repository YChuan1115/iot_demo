# NOTE: This file is generated by yotta: changes will be overwritten!

cmake_minimum_required(VERSION 2.8.11)

include_directories("/root/iot_demo/mbed-client-pi/mbed-linux/source")


set(YOTTA_AUTO_MBED-CLIENT-LINUX-EXAMPLE_CPP_FILES
    "/root/iot_demo/mbed-client-pi/mbed-linux/source/oled_i2c/src/I2C_SSD1306Z.c"
    "/root/iot_demo/mbed-client-pi/mbed-linux/source/bme280_i2c/src/lib_i2c.c"
    "/root/iot_demo/mbed-client-pi/mbed-linux/source/bme280_i2c/src/bcm2835.c"
    "/root/iot_demo/mbed-client-pi/mbed-linux/source/bme280_i2c/src/bme280.c"
    "/root/iot_demo/mbed-client-pi/mbed-linux/source/main.cpp"
)
# force dependency on the config header for cpp files, which CMake otherwise wouldn't track:
set_property(SOURCE ${YOTTA_AUTO_MBED-CLIENT-LINUX-EXAMPLE_CPP_FILES} PROPERTY OBJECT_DEPENDS "/root/iot_demo/mbed-client-pi/mbed-linux/build/arm-linux-native/yotta_config.h")
set(YOTTA_AUTO_MBED-CLIENT-LINUX-EXAMPLE_HEADER_FILES
    "/root/iot_demo/mbed-client-pi/mbed-linux/source/oled_i2c/include/I2C_SSD1306Z.h"
    "/root/iot_demo/mbed-client-pi/mbed-linux/source/bme280_i2c/include/prin_bme280.h"
    "/root/iot_demo/mbed-client-pi/mbed-linux/source/oled_i2c/include/Draw2D.h"
    "/root/iot_demo/mbed-client-pi/mbed-linux/source/oled_i2c/include/my_debug.h"
    "/root/iot_demo/mbed-client-pi/mbed-linux/source/security_hank.h"
    "/root/iot_demo/mbed-client-pi/mbed-linux/source/security_joseph1.h"
    "/root/iot_demo/mbed-client-pi/mbed-linux/source/security_joseph.h"
    "/root/iot_demo/mbed-client-pi/mbed-linux/source/bme280.h"
    "/root/iot_demo/mbed-client-pi/mbed-linux/source/bme280_i2c/include/bme280.h"
    "/root/iot_demo/mbed-client-pi/mbed-linux/source/lib_i2c.h"
    "/root/iot_demo/mbed-client-pi/mbed-linux/source/bme280_i2c/include/lib_i2c.h"
    "/root/iot_demo/mbed-client-pi/mbed-linux/source/oled_i2c/include/I2Cdev.h"
    "/root/iot_demo/mbed-client-pi/mbed-linux/source/bme280_i2c/include/bcm2835.h"
    "/root/iot_demo/mbed-client-pi/mbed-linux/source/security_joseph2.h"
    "/root/iot_demo/mbed-client-pi/mbed-linux/source/oled_i2c/include/Font8x16.h"
    "/root/iot_demo/mbed-client-pi/mbed-linux/source/oled_i2c/include/lib_i2c.h"
    "/root/iot_demo/mbed-client-pi/mbed-linux/source/bme280_i2c/include/my_debug.h"
    "/root/iot_demo/mbed-client-pi/mbed-linux/source/oled_i2c/include/Font5x7.h"
    "/root/iot_demo/mbed-client-pi/mbed-linux/source/bcm2835.h"
    "/root/iot_demo/mbed-client-pi/mbed-linux/source/security.h"
)
# force dependency on the config header for header files, which CMake otherwise wouldn't track:
set_property(SOURCE ${YOTTA_AUTO_MBED-CLIENT-LINUX-EXAMPLE_HEADER_FILES} PROPERTY OBJECT_DEPENDS "/root/iot_demo/mbed-client-pi/mbed-linux/build/arm-linux-native/yotta_config.h")
set(YOTTA_AUTO_MBED-CLIENT-LINUX-EXAMPLE_C_FILES
    "/root/iot_demo/mbed-client-pi/mbed-linux/source/oled_i2c/src/I2C_SSD1306Z.c"
    "/root/iot_demo/mbed-client-pi/mbed-linux/source/bme280_i2c/src/lib_i2c.c"
    "/root/iot_demo/mbed-client-pi/mbed-linux/source/bme280_i2c/src/bcm2835.c"
    "/root/iot_demo/mbed-client-pi/mbed-linux/source/bme280_i2c/src/bme280.c"
)
# force dependency on the config header for c files, which CMake otherwise wouldn't track:
set_property(SOURCE ${YOTTA_AUTO_MBED-CLIENT-LINUX-EXAMPLE_C_FILES} PROPERTY OBJECT_DEPENDS "/root/iot_demo/mbed-client-pi/mbed-linux/build/arm-linux-native/yotta_config.h")


add_executable (mbed-client-linux-example
    ${YOTTA_AUTO_MBED-CLIENT-LINUX-EXAMPLE_CPP_FILES}
    ${YOTTA_AUTO_MBED-CLIENT-LINUX-EXAMPLE_HEADER_FILES}
    ${YOTTA_AUTO_MBED-CLIENT-LINUX-EXAMPLE_C_FILES}
)
set_target_properties(mbed-client-linux-example PROPERTIES ENABLE_EXPORTS ON)

yotta_postprocess_target(EXECUTABLE mbed-client-linux-example)



target_link_libraries(mbed-client-linux-example
    mbed-client
)

