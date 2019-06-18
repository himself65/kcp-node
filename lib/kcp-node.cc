#include "kcp-node.h"

#define ADD_FUNCITON(env, exports, name, function) \
{ \
	napi_status status; \
	napi_value fn; \
	status = napi_create_function((env), nullptr, 0, (function), nullptr, &fn); \
	if (status != napi_ok) return NULL; \
	status = napi_set_named_property((env), (exports), (name), fn); \
	if (status != napi_ok) return NULL; \
	return (exports); \
}

namespace kcp_node {
//	KCPObject::~KCPObject()
//	{
//	}
//	napi_value KCPObject::Init(napi_env, napi_callback_info)
//	{
//	}
//
//	void KCPObject::Release(napi_env, napi_callback_info)
//	{
//	}
//
//	napi_status KCPObject::SetOutput(napi_env, napi_callback_info)
//	{
//	}
//
//	napi_status KCPObject::Output(napi_env, napi_callback_info)
//	{
//	}
//
//	napi_status KCPObject::Recv(napi_env, napi_callback_info)
//	{
//	}
//
//	napi_status KCPObject::Send(napi_env, napi_callback_info)
//	{
//	}
//
//	napi_status KCPObject::Update(napi_env, napi_callback_info)
//	{
//	}
//
//	napi_status KCPObject::Check(napi_env, napi_callback_info)
//	{
//	}
//
//	napi_status KCPObject::Input(napi_env, napi_callback_info)
//	{
//	}
//
//	napi_status KCPObject::Flush(napi_env, napi_callback_info)
//	{
//	}
//
//	napi_status KCPObject::Peeksize(napi_env, napi_callback_info)
//	{
//	}
//
//	napi_status KCPObject::Setmtu(napi_env, napi_callback_info)
//	{
//	}
//
//	napi_status KCPObject::Wndsize(napi_env, napi_callback_info)
//	{
//	}
//
//	napi_status KCPObject::Waitsnd(napi_env, napi_callback_info)
//	{
//	}
//
//	napi_status KCPObject::Nodelay(napi_env, napi_callback_info)
//	{
//	}
//
//	napi_status KCPObject::Log(napi_env, napi_callback_info)
//	{
//	}

	napi_value KCPCreate(napi_env env, napi_callback_info info) {
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
		IUINT32 conv;
		napi_get_value_uint32(env, args[0], &conv);
		ikcpcb* ikcp = ikcp_create(conv, NULL);		// fixme: save value ikcp
		napi_value obj;
		napi_status status =napi_create_object(env, &obj);
		if (status != napi_ok) {
			napi_throw_error(env, NULL, "Unexpected error.");
		}
		// todo
		return obj;
	}

	napi_value Init(napi_env env, napi_value exports) {
		ADD_FUNCITON(env, exports, "create", KCPCreate);
		return exports;
	}

	NAPI_MODULE(NODE_GYP_MODULE_NAME, Init)
}
