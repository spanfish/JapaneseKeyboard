all: \
    $(SHARED_INTERMEDIATE_DIR)/proto_out/ipc/ipc.pb.h

$(SHARED_INTERMEDIATE_DIR)/proto_out/ipc/ipc.pb.h \
    $(SHARED_INTERMEDIATE_DIR)/proto_out/ipc/ipc.pb.cc \
    : \
    ipc.proto \
    ../build_tools/protoc_wrapper.py \
    $(BUILT_PRODUCTS_DIR)/protoc
	@mkdir -p "$(SHARED_INTERMEDIATE_DIR)/proto_out/ipc"
	@echo note: "Generating C++ code from ipc.proto"
	python ../build_tools/protoc_wrapper.py "--project_root=.." "--protoc_command=protoc" "--proto=ipc.proto" "--cpp_out=$(SHARED_INTERMEDIATE_DIR)/proto_out" "--protoc_dir=$(BUILT_PRODUCTS_DIR)"
