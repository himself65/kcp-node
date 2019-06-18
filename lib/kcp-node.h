#ifndef KCP_NODE
#define KCP_NODE
#define NAPI_VERSION 4
#include <v8.h>
#include <node_api.h>
#include "./kcp/ikcp.h"

namespace kcp_node {
	class KCPObject {
	public:
		static napi_value KCPObject::Init(napi_env env, napi_callback_info info);
		KCPObject(ikcpcb* cb) : ikcpcb(cb) { ; };
		~KCPObject();
	private:
		KCPObject() { ; };
		ikcpcb* ikcpcb;
	};
	napi_value Init(napi_env, napi_callback_info);
}

#endif // !KCP_NODE
