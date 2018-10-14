all: \
    $(SHARED_INTERMEDIATE_DIR)/proto_out/data_manager/packed/system_dictionary_data.pb.h

$(SHARED_INTERMEDIATE_DIR)/proto_out/data_manager/packed/system_dictionary_data.pb.h \
    $(SHARED_INTERMEDIATE_DIR)/proto_out/data_manager/packed/system_dictionary_data.pb.cc \
    : \
    system_dictionary_data.proto \
    ../../build_tools/protoc_wrapper.py \
    $(BUILT_PRODUCTS_DIR)/protoc
	@mkdir -p "$(SHARED_INTERMEDIATE_DIR)/proto_out/data_manager/packed"
	@echo note: "Generating C++ code from system_dictionary_data.proto"
	python ../../build_tools/protoc_wrapper.py "--project_root=../.." "--protoc_command=protoc" "--proto=system_dictionary_data.proto" "--cpp_out=$(SHARED_INTERMEDIATE_DIR)/proto_out" "--protoc_dir=$(BUILT_PRODUCTS_DIR)"
