#include "kcp-node.h"

#define ASSERT_RUN_SUCCESS(command, code, message) \
{ \
	if ((command) != napi_ok) napi_throw_error(env, code, message); \
}

#define ADD_PROPERTY(env, object, name, value) \
{ \
	ASSERT_RUN_SUCCESS(napi_set_named_property((env), (object), (name), value), nullptr, "Set property error"); \
}

#define ADD_FUNCITON(env, object, name, function) \
{ \
	napi_status status; \
	napi_value fn; \
	status = napi_create_function((env), nullptr, NAPI_AUTO_LENGTH, (function), nullptr, &fn); \
	if (status != napi_ok) return nullptr; \
	ADD_PROPERTY(env, object, name, fn); \
	return (object); \
}

namespace kcp_node {
	KCPObject::~KCPObject()
	{
		if (cb) {
			ikcp_release(cb);
			cb = nullptr;
		}
	}

	napi_value KCPObject::Init(napi_env env, napi_callback_info info)
	{
		size_t argc = 1;
		napi_value args[2];
		napi_value thiz;
		napi_get_cb_info(env, info, &argc, args, &thiz, nullptr);
		if (argc < 1) {
			napi_throw_error(env, nullptr, "must have one parameter at least.");
		}
		napi_valuetype valuetype;
		napi_typeof(env, args[0], &valuetype);
		if (valuetype != napi_number) {
			napi_throw_type_error(env, nullptr, "Wrong argument type on args[0]. number expected.");
		}
		IUINT32 conv;
		napi_get_value_uint32(env, args[0], &conv);
		KCPObject kcp_obj = KCPObject(ikcp_create(conv, thiz));
		ASSERT_RUN_SUCCESS(napi_wrap(env, thiz, &kcp_obj, nullptr, nullptr, nullptr), nullptr, "Wrap C++ instance failed.");
		return nullptr;
	}

	napi_value Init(napi_env env, napi_value exports) {
		napi_value obj;
		napi_define_class(env, "kcp", NAPI_AUTO_LENGTH, KCPObject::Init, nullptr, 0, nullptr, &obj);
		ASSERT_RUN_SUCCESS(napi_set_named_property(env, exports, "KCP", obj), nullptr, nullptr);
		return exports;
	}

	NAPI_MODULE(NODE_GYP_MODULE_NAME, Init)
}
