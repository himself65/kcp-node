#include "kcp-node.h"

#define ASSERT_RUN_SUCCESS(command, code, message) if ((command) != napi_ok) napi_throw_error(env, code, message);

#define ADD_PROPERTY(env, object, name, value) ASSERT_RUN_SUCCESS(napi_set_named_property((env), (object), (name), value), nullptr, "Set property error"); 

#define ADD_FUNCITON(env, object, name, function) \
{ \
	napi_status status; \
	napi_value fn; \
	status = napi_create_function((env), nullptr, NAPI_AUTO_LENGTH, (function), nullptr, &fn); \
	if (status != napi_ok) return nullptr; \
	ADD_PROPERTY(env, object, name, fn); \
	return (object); \
}

#define DECLARE_NAPI_PROPERTY(name, func) \
{ (name), nullptr, (func), nullptr, nullptr, nullptr, napi_default, nullptr }

#define DECLARE_NAPI_GETTER_SETTER(name, getter, setter)				 \
{ (name), nullptr, nullptr, (getter), (setter), nullptr, napi_default, nullptr }

namespace kcp_node {
	KCPObject::~KCPObject()
	{
		if (kcpcb) {
			ikcp_release(kcpcb);
			kcpcb = nullptr;
		}
	}

	void KCPObject::kcp_output(const char* buf, int len, ikcpcb* kcp, void* user) {
		// todo
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
		ASSERT_RUN_SUCCESS(napi_get_cb_info(env, info, &argc, args, &thiz, nullptr), nullptr, "Get_cb_info failed.");
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
		KCPObject* kcp_obj = new KCPObject(ikcp_create(conv, nullptr));
		// bind function
		ASSERT_RUN_SUCCESS(napi_wrap(env, thiz, kcp_obj, KCPObject::Release, nullptr, nullptr), nullptr, "Wrap C++ instance failed.");
		napi_value func;
		ASSERT_RUN_SUCCESS(napi_create_function(env, "empty", NAPI_AUTO_LENGTH, Empty, nullptr, &func), nullptr, "Wrap C++ instance failed.");
		ASSERT_RUN_SUCCESS(napi_create_reference(env, func, 1, &kcp_obj->cb), nullptr, "Create_reference error.");
		return nullptr;
	}

	napi_value KCPObject::GetOutput(napi_env env, napi_callback_info info) {
		napi_value thiz;
		ASSERT_RUN_SUCCESS(napi_get_cb_info(env, info, nullptr, nullptr, &thiz, nullptr), nullptr, "Get_cb_info failed.");
		KCPObject* target;
		ASSERT_RUN_SUCCESS(napi_unwrap(env, thiz, reinterpret_cast<void**>(&target)), nullptr, "Unwrap failed.");
		napi_value value;
		ASSERT_RUN_SUCCESS(napi_get_reference_value(env, target->cb, &value), nullptr, "Get_reference_value error.");
		return value;
	}

	napi_value KCPObject::SetOutput(napi_env env, napi_callback_info info)
	{
		size_t argc = 1;
		napi_value args[1];
		napi_value thiz;
		ASSERT_RUN_SUCCESS(napi_get_cb_info(env, info, &argc, args, &thiz, nullptr), nullptr, "Get_cb_info failed.");
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
		ASSERT_RUN_SUCCESS(napi_unwrap(env, thiz, reinterpret_cast<void**>(&target)), nullptr, "Unwrap failed.");
		ASSERT_RUN_SUCCESS(napi_create_reference(env, args[0], 1, &target->cb), nullptr, "Create_reference error.");
		return args[0];
	}

	napi_value Init(napi_env env, napi_value exports) {
		napi_value obj;
		napi_property_descriptor desc[] = {
			DECLARE_NAPI_GETTER_SETTER("output", KCPObject::GetOutput, KCPObject::SetOutput),
		};
		napi_define_class(env, "kcp", NAPI_AUTO_LENGTH, KCPObject::Init, nullptr, 1, desc, &obj);
		ASSERT_RUN_SUCCESS(napi_set_named_property(env, exports, "KCP", obj), nullptr, nullptr);
		return exports;
	}

	NAPI_MODULE(NODE_GYP_MODULE_NAME, Init)
}
