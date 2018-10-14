all: \
    $(SHARED_INTERMEDIATE_DIR)/proto_out/dictionary/user_dictionary_storage.pb.h

$(SHARED_INTERMEDIATE_DIR)/proto_out/dictionary/user_dictionary_storage.pb.h \
    $(SHARED_INTERMEDIATE_DIR)/proto_out/dictionary/user_dictionary_storage.pb.cc \
    : \
    user_dictionary_storage.proto \
    ../build_tools/protoc_wrapper.py \
    $(BUILT_PRODUCTS_DIR)/protoc
	@mkdir -p "$(SHARED_INTERMEDIATE_DIR)/proto_out/dictionary"
	@echo note: "Generating C++ code from user_dictionary_storage.proto"
	python ../build_tools/protoc_wrapper.py "--project_root=.." "--protoc_command=protoc" "--proto=user_dictionary_storage.proto" "--cpp_out=$(SHARED_INTERMEDIATE_DIR)/proto_out" "--protoc_dir=$(BUILT_PRODUCTS_DIR)"
