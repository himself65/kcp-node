#include "kcp-node.h"

namespace kcp_node {
	KCPObject::~KCPObject()
	{
		if (kcpcb) {
			ikcp_release(kcpcb);
			kcpcb = nullptr;
		}
	}

	int KCPObject::kcp_output(const char* buf, int len, ikcpcb* kcp, void* user) {
		KCPObject* target = reinterpret_cast<KCPObject*>(&user);
		// todo
		return 0;
	}

	void KCPObject::Release(napi_env env, void* finalize_data, void* finalize_hint) {
		delete reinterpret_cast<KCPObject*>(finalize_data);
	}

	napi_value Empty(napi_env env, napi_callback_info info) {
		return nullptr;
	}

	napi_value KCPObject::Init(napi_env env, napi_callback_info info)
	{
		size_t argc = 1;
		napi_value args[2];
		napi_value thiz;
		NAPI_OK(napi_get_cb_info(env, info, &argc, args, &thiz, nullptr), nullptr, "Get_cb_info error.");
		if (argc < 1) {
			napi_throw_error(env, nullptr, "Must have one parameter at least.");
			return nullptr;
		}
		napi_valuetype valuetype;
		napi_typeof(env, args[0], &valuetype);
		if (valuetype != napi_number) {
			napi_throw_type_error(env, nullptr, "Wrong argument type on args[0]. number expected.");
			// return to avoid crash
			return nullptr;
		}
		IUINT32 conv;
		napi_get_value_uint32(env, args[0], &conv);
		KCPObject* kcp_obj;
		kcp_obj = new KCPObject(ikcp_create(conv, &kcp_obj));
		kcp_obj->kcpcb->output = KCPObject::kcp_output;
		kcp_obj->env = env;
		// bind function
		NAPI_OK(napi_wrap(env, thiz, kcp_obj, KCPObject::Release, nullptr, nullptr), nullptr, "Wrap C++ instance error.");
		napi_value func;
		NAPI_OK(napi_create_function(env, "empty", NAPI_AUTO_LENGTH, Empty, nullptr, &func), nullptr, "Wrap C++ instance error.");
		NAPI_OK(napi_create_reference(env, func, 1, &kcp_obj->cb), nullptr, "Create_reference error.");
		return nullptr;
	}

	napi_value KCPObject::GetOutput(napi_env env, napi_callback_info info) {
		napi_value thiz;
		NAPI_OK(napi_get_cb_info(env, info, nullptr, nullptr, &thiz, nullptr), nullptr, "Get_cb_info error.");
		KCPObject* target;
		NAPI_OK(napi_unwrap(env, thiz, reinterpret_cast<void**>(&target)), nullptr, "Unwrap error.");
		napi_value value;
		NAPI_OK(napi_get_reference_value(env, target->cb, &value), nullptr, "Get_reference_value error.");
		return value;
	}

	napi_value KCPObject::SetOutput(napi_env env, napi_callback_info info)
	{
		size_t argc = 1;
		napi_value args[1];
		napi_value thiz;
		NAPI_OK(napi_get_cb_info(env, info, &argc, args, &thiz, nullptr), nullptr, "Get_cb_info error.");
		if (argc < 1) {
			napi_throw_error(env, nullptr, "Must have one parameter at least.");
			return nullptr;
		}
		napi_valuetype valuetype;
		napi_typeof(env, args[0], &valuetype);
		if (valuetype != napi_function) {
			napi_throw_error(env, nullptr, "Wrong argument type on args[0], function expected.");
			return nullptr;
		}
		KCPObject* target;
		NAPI_OK(napi_unwrap(env, thiz, reinterpret_cast<void**>(&target)), nullptr, "Unwrap error.");
		NAPI_OK(napi_create_reference(env, args[0], 1, &target->cb), nullptr, "Create_reference error.");
		return args[0];
	}

	napi_value KCPObject::SetTimestamp(napi_env env, napi_callback_info info) {
		size_t argc = 4;
		napi_value args[4];
		napi_value thiz;
		NAPI_OK(napi_get_cb_info(env, info, &argc, args, &thiz, nullptr), nullptr, "Get_cb_info error.");
		if (argc < 4) {
			napi_throw_error(env, nullptr, "Must have one parameter at least.");
			return nullptr;
		}
		int arguments[4];
		for (int i = 0; i < 4; ++i) {
			napi_valuetype valuetype;
			napi_typeof(env, args[i], &valuetype);
			if (valuetype != napi_number) {

				napi_throw_error(
					env,
					nullptr,
					"Wrong argument type on args, number expected."
				);
				return nullptr;
			}
			napi_get_value_int32(env, args[i], arguments + i);
		}
		KCPObject* target;
		NAPI_OK(napi_unwrap(env, thiz, reinterpret_cast<void**>(&target)), nullptr, "Unwrap error.");
		if (target == nullptr) {
			napi_throw_error(env, nullptr, "Unexpected error, target is nullptr.");
			return nullptr;
		}
		napi_value res;
		NAPI_OK(
			napi_get_boolean(
				env,
				ikcp_nodelay(target->kcpcb, arguments[0], arguments[1], arguments[2], arguments[3]),
				&res
			),
			nullptr,
			"Get_boolean error."
		);
		return res;
	}

	napi_value Init(napi_env env, napi_value exports) {
		napi_value obj;
		napi_property_descriptor desc[] = {
			DECLARE_NAPI_GETTER_SETTER("output", KCPObject::GetOutput, KCPObject::SetOutput),
		};
		napi_define_class(env, "kcp", NAPI_AUTO_LENGTH, KCPObject::Init, nullptr, 1, desc, &obj);
		NAPI_OK(napi_set_named_property(env, exports, "KCP", obj), nullptr, nullptr);
		return exports;
	}

	NAPI_MODULE(NODE_GYP_MODULE_NAME, Init)
}
