#define NAPI_VERSION 4
#include <functional>
#include <v8.h>
#include <node_api.h>
#include "kcp-node.h"
#include "../deps/kcp/ikcp.h"

#define ADD_FUNCITON(env, exports, name, function) \
{ \
	napi_status status; \
	napi_value fn; \
	status = napi_create_function((env), nullptr, 0, (function), nullptr, &fn); \
	if (status != napi_ok) return nullptr; \
	status = napi_set_named_property((env), (exports), (name), fn); \
	if (status != napi_ok) return nullptr; \
}

namespace kcp_node {
	napi_value kcp_create(napi_env env, napi_callback_info info) {
		size_t argc = 1;
		napi_value args[2];
		napi_get_cb_info(env, info, &argc, args, NULL, NULL);
		if (argc < 1) {
			napi_throw_error(env, NULL, "must have one parameter at least.");
		}
		napi_valuetype valuetype;
		napi_typeof(env, args[0], &valuetype);
		if (valuetype != napi_number) {
			napi_throw_type_error(env, NULL, "Wrong argument type on args[0]. number expected.");
		}
		std::function<void()> func;
		napi_typeof(env, args[1], &valuetype);
		if (valuetype == napi_function) {
			func = [&]() {
				napi_value global;
				napi_value& cb = args[1];
				napi_get_global(env, &global);
				napi_call_function(env, global, cb, 0, NULL, NULL);
			};
		}
		IUINT32 conv;
		napi_get_value_uint32(env, args[0], &conv);
		ikcpcb* val = ikcp_create(conv, func.target<void*>());
	}

	napi_value init(napi_env env, napi_value exports) {
		ADD_FUNCITON(env, exports, "create", kcp_create);
		return exports;
	}
}
