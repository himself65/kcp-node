#define NAPI_VERSION 4
#include <v8.h>
#include <node_api.h>

#define NAPI_OK(command, code, message) if ((command) != napi_ok) napi_throw_error(env, code, message);

#define ADD_PROPERTY(env, object, name, value) NAPI_OK(napi_set_named_property((env), (object), (name), value), nullptr, "Set property error"); 

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