all: \
    $(SHARED_INTERMEDIATE_DIR)/proto_out/config/config.pb.h

$(SHARED_INTERMEDIATE_DIR)/proto_out/config/config.pb.h \
    $(SHARED_INTERMEDIATE_DIR)/proto_out/config/config.pb.cc \
    : \
    config.proto \
    ../build_tools/protoc_wrapper.py \
    $(BUILT_PRODUCTS_DIR)/protoc
	@mkdir -p "$(SHARED_INTERMEDIATE_DIR)/proto_out/config"
	@echo note: "Generating C++ code from config.proto"
	python ../build_tools/protoc_wrapper.py "--project_root=.." "--protoc_command=protoc" "--proto=config.proto" "--cpp_out=$(SHARED_INTERMEDIATE_DIR)/proto_out" "--protoc_dir=$(BUILT_PRODUCTS_DIR)"
