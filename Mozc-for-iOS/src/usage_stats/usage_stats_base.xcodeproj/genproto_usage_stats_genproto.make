all: \
    $(SHARED_INTERMEDIATE_DIR)/proto_out/usage_stats/usage_stats.pb.h

$(SHARED_INTERMEDIATE_DIR)/proto_out/usage_stats/usage_stats.pb.h \
    $(SHARED_INTERMEDIATE_DIR)/proto_out/usage_stats/usage_stats.pb.cc \
    : \
    usage_stats.proto \
    ../build_tools/protoc_wrapper.py \
    $(BUILT_PRODUCTS_DIR)/protoc
	@mkdir -p "$(SHARED_INTERMEDIATE_DIR)/proto_out/usage_stats"
	@echo note: "Generating C++ code from usage_stats.proto"
	python ../build_tools/protoc_wrapper.py "--project_root=.." "--protoc_command=protoc" "--proto=usage_stats.proto" "--cpp_out=$(SHARED_INTERMEDIATE_DIR)/proto_out" "--protoc_dir=$(BUILT_PRODUCTS_DIR)"
