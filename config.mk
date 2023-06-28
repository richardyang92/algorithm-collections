export BUILD_ROOT := $(shell pwd)

export SOURCE_DIR := $(BUILD_ROOT)/merge_sort/ \
					 $(BUILD_ROOT)/zero_one_packet/ \
					 $(BUILD_ROOT)/huffman/ \
					 $(BUILD_ROOT)/quick_sort

export TARGET_DIR := $(BUILD_ROOT)/target/