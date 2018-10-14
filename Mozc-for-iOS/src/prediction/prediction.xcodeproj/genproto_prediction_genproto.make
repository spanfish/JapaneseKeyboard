all: \
    $(SHARED_INTERMEDIATE_DIR)/proto_out/prediction/user_history_predictor.pb.h

$(SHARED_INTERMEDIATE_DIR)/proto_out/prediction/user_history_predictor.pb.h \
    $(SHARED_INTERMEDIATE_DIR)/proto_out/prediction/user_history_predictor.pb.cc \
    : \
    user_history_predictor.proto \
    ../build_tools/protoc_wrapper.py \
    $(BUILT_PRODUCTS_DIR)/protoc
	@mkdir -p "$(SHARED_INTERMEDIATE_DIR)/proto_out/prediction"
	@echo note: "Generating C++ code from user_history_predictor.proto"
	python ../build_tools/protoc_wrapper.py "--project_root=.." "--protoc_command=protoc" "--proto=user_history_predictor.proto" "--cpp_out=$(SHARED_INTERMEDIATE_DIR)/proto_out" "--protoc_dir=$(BUILT_PRODUCTS_DIR)"
