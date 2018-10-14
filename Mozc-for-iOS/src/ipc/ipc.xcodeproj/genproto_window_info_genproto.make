all: \
    $(SHARED_INTERMEDIATE_DIR)/proto_out/ipc/window_info.pb.h

$(SHARED_INTERMEDIATE_DIR)/proto_out/ipc/window_info.pb.h \
    $(SHARED_INTERMEDIATE_DIR)/proto_out/ipc/window_info.pb.cc \
    : \
    window_info.proto \
    ../build_tools/protoc_wrapper.py \
    $(BUILT_PRODUCTS_DIR)/protoc
	@mkdir -p "$(SHARED_INTERMEDIATE_DIR)/proto_out/ipc"
	@echo note: "Generating C++ code from window_info.proto"
	python ../build_tools/protoc_wrapper.py "--project_root=.." "--protoc_command=protoc" "--proto=window_info.proto" "--cpp_out=$(SHARED_INTERMEDIATE_DIR)/proto_out" "--protoc_dir=$(BUILT_PRODUCTS_DIR)"
