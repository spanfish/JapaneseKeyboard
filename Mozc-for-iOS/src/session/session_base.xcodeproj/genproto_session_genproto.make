all: \
    $(SHARED_INTERMEDIATE_DIR)/proto_out/session/candidates.pb.h \
    $(SHARED_INTERMEDIATE_DIR)/proto_out/session/commands.pb.h \
    $(SHARED_INTERMEDIATE_DIR)/proto_out/session/state.pb.h

$(SHARED_INTERMEDIATE_DIR)/proto_out/session/candidates.pb.h \
    $(SHARED_INTERMEDIATE_DIR)/proto_out/session/candidates.pb.cc \
    : \
    candidates.proto \
    ../build_tools/protoc_wrapper.py \
    $(BUILT_PRODUCTS_DIR)/protoc
	@mkdir -p "$(SHARED_INTERMEDIATE_DIR)/proto_out/session"
	@echo note: "Generating C++ code from candidates.proto"
	python ../build_tools/protoc_wrapper.py "--project_root=.." "--protoc_command=protoc" "--proto=candidates.proto" "--cpp_out=$(SHARED_INTERMEDIATE_DIR)/proto_out" "--protoc_dir=$(BUILT_PRODUCTS_DIR)"

$(SHARED_INTERMEDIATE_DIR)/proto_out/session/commands.pb.h \
    $(SHARED_INTERMEDIATE_DIR)/proto_out/session/commands.pb.cc \
    : \
    commands.proto \
    ../build_tools/protoc_wrapper.py \
    $(BUILT_PRODUCTS_DIR)/protoc
	@mkdir -p "$(SHARED_INTERMEDIATE_DIR)/proto_out/session"
	@echo note: "Generating C++ code from commands.proto"
	python ../build_tools/protoc_wrapper.py "--project_root=.." "--protoc_command=protoc" "--proto=commands.proto" "--cpp_out=$(SHARED_INTERMEDIATE_DIR)/proto_out" "--protoc_dir=$(BUILT_PRODUCTS_DIR)"

$(SHARED_INTERMEDIATE_DIR)/proto_out/session/state.pb.h \
    $(SHARED_INTERMEDIATE_DIR)/proto_out/session/state.pb.cc \
    : \
    state.proto \
    ../build_tools/protoc_wrapper.py \
    $(BUILT_PRODUCTS_DIR)/protoc
	@mkdir -p "$(SHARED_INTERMEDIATE_DIR)/proto_out/session"
	@echo note: "Generating C++ code from state.proto"
	python ../build_tools/protoc_wrapper.py "--project_root=.." "--protoc_command=protoc" "--proto=state.proto" "--cpp_out=$(SHARED_INTERMEDIATE_DIR)/proto_out" "--protoc_dir=$(BUILT_PRODUCTS_DIR)"
