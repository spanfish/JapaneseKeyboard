all: \
    $(SHARED_INTERMEDIATE_DIR)/proto_out/renderer/renderer_command.pb.h \
    $(SHARED_INTERMEDIATE_DIR)/proto_out/renderer/renderer_style.pb.h

$(SHARED_INTERMEDIATE_DIR)/proto_out/renderer/renderer_command.pb.h \
    $(SHARED_INTERMEDIATE_DIR)/proto_out/renderer/renderer_command.pb.cc \
    : \
    renderer_command.proto \
    ../build_tools/protoc_wrapper.py \
    $(BUILT_PRODUCTS_DIR)/protoc
	@mkdir -p "$(SHARED_INTERMEDIATE_DIR)/proto_out/renderer"
	@echo note: "Generating C++ code from renderer_command.proto"
	python ../build_tools/protoc_wrapper.py "--project_root=.." "--protoc_command=protoc" "--proto=renderer_command.proto" "--cpp_out=$(SHARED_INTERMEDIATE_DIR)/proto_out" "--protoc_dir=$(BUILT_PRODUCTS_DIR)"

$(SHARED_INTERMEDIATE_DIR)/proto_out/renderer/renderer_style.pb.h \
    $(SHARED_INTERMEDIATE_DIR)/proto_out/renderer/renderer_style.pb.cc \
    : \
    renderer_style.proto \
    ../build_tools/protoc_wrapper.py \
    $(BUILT_PRODUCTS_DIR)/protoc
	@mkdir -p "$(SHARED_INTERMEDIATE_DIR)/proto_out/renderer"
	@echo note: "Generating C++ code from renderer_style.proto"
	python ../build_tools/protoc_wrapper.py "--project_root=.." "--protoc_command=protoc" "--proto=renderer_style.proto" "--cpp_out=$(SHARED_INTERMEDIATE_DIR)/proto_out" "--protoc_dir=$(BUILT_PRODUCTS_DIR)"
