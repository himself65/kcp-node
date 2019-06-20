#ifndef KCP_NODE
#define KCP_NODE
#define NAPI_VERSION 4
#include <v8.h>
#include <node_api.h>
#include "./kcp/ikcp.h"

namespace kcp_node {
	class KCPObject {
	public:
		static napi_value Init(napi_env, napi_callback_info);
		static void Release(napi_env, void*, void*);
		static napi_value SetOutput(napi_env, napi_callback_info);
		static napi_value GetOutput(napi_env, napi_callback_info);
		static void kcp_output(const char*, int, ikcpcb*, void*);

		KCPObject(ikcpcb* kcpcb) : kcpcb(kcpcb) { ; };
		~KCPObject();

		napi_value cb;
	private:
		KCPObject() { ; };
		ikcpcb* kcpcb;
	};
	napi_value Init(napi_env, napi_callback_info);
}

#endif // !KCP_NODE
