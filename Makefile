include config.mk

all:
	@echo "compile"
	@if [ ! -d $(TARGET_DIR) ]; then mkdir $(TARGET_DIR); fi
	@for dir in $(SOURCE_DIR); do make -C $$dir; done

clean:
	rm -rf $(TARGET_DIR)