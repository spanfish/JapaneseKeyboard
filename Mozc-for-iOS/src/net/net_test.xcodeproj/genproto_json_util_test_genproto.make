all: \
    $(SHARED_INTERMEDIATE_DIR)/proto_out/net/json_util_test.pb.h

$(SHARED_INTERMEDIATE_DIR)/proto_out/net/json_util_test.pb.h \
    $(SHARED_INTERMEDIATE_DIR)/proto_out/net/json_util_test.pb.cc \
    : \
    json_util_test.proto \
    ../build_tools/protoc_wrapper.py \
    $(BUILT_PRODUCTS_DIR)/protoc
	@mkdir -p "$(SHARED_INTERMEDIATE_DIR)/proto_out/net"
	@echo note: "Generating C++ code from json_util_test.proto"
	python ../build_tools/protoc_wrapper.py "--project_root=.." "--protoc_command=protoc" "--proto=json_util_test.proto" "--cpp_out=$(SHARED_INTERMEDIATE_DIR)/proto_out" "--protoc_dir=$(BUILT_PRODUCTS_DIR)"
