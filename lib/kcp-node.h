#ifndef KCP_NODE
#define KCP_NODE
#include "./common.h"
#include "./kcp/ikcp.h"
#include <string>

namespace kcp_node {
	class KCPObject {
	public:
		static napi_value Init(napi_env, napi_callback_info);
		static void Release(napi_env, void*, void*);
		static napi_value SetOutput(napi_env, napi_callback_info);
		static napi_value GetOutput(napi_env, napi_callback_info);
		static napi_value SetTimestamp(napi_env, napi_callback_info);
		static int kcp_output(const char*, int, ikcpcb*, void*);

		KCPObject(ikcpcb* kcpcb) : kcpcb(kcpcb) { ; };
		~KCPObject();

		napi_ref cb;
		napi_env env;
	private:
		KCPObject() { ; };
		ikcpcb* kcpcb;
	};
	napi_value Init(napi_env, napi_callback_info);
}

#endif // !KCP_NODE
