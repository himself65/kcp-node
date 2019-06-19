#include "kcp-node.h"

#define ASSERT_RUN_SUCCESS(command, code, message) \
{ \
	if ((command) != napi_ok) napi_throw_error(env, code, message); \
}

#define ADD_PROPERTY(env, object, name, value) \
{ \
	ASSERT_RUN_SUCCESS(napi_set_named_property((env), (object), (name), value), NULL, "Set property error"); \
}

#define ADD_FUNCITON(env, object, name, function) \
{ \
	napi_status status; \
	napi_value fn; \
	status = napi_create_function((env), NULL, NAPI_AUTO_LENGTH, (function), NULL, &fn); \
	if (status != napi_ok) return NULL; \
	ADD_PROPERTY(env, object, name, fn); \
	return (object); \
}

namespace kcp_node {
	KCPObject::~KCPObject()
	{
		if (this->cb) {
			ikcp_release(this->cb);
			this->cb = NULL;
		}
	}

	napi_value KCPObject::Init(napi_env env, napi_callback_info info)
	{
		size_t argc = 1;
		napi_value args[2];
		napi_value thiz;
		napi_get_cb_info(env, info, &argc, args, &thiz, NULL);
		if (argc < 1) {
			napi_throw_error(env, NULL, "must have one parameter at least.");
		}
		napi_valuetype valuetype;
		napi_typeof(env, args[0], &valuetype);
		if (valuetype != napi_number) {
			napi_throw_type_error(env, NULL, "Wrong argument type on args[0]. number expected.");
		}
		IUINT32 conv;
		napi_get_value_uint32(env, args[0], &conv);
		KCPObject kcp_obj = KCPObject(ikcp_create(conv, thiz));
		napi_status status = napi_wrap(env, thiz, &kcp_obj, NULL, NULL, NULL);
		if (status != napi_ok) {
			napi_throw_error(env, NULL, NULL);
		}

		return NULL;
	}

	napi_value Init(napi_env env, napi_value exports) {
		napi_value obj;
		napi_define_class(env, "kcp", NAPI_AUTO_LENGTH, KCPObject::Init, NULL, 0, NULL, &obj);
		ASSERT_RUN_SUCCESS(napi_set_named_property(env, exports, "KCP", obj), NULL, NULL);
		return exports;
	}

	NAPI_MODULE(NODE_GYP_MODULE_NAME, Init)
}
