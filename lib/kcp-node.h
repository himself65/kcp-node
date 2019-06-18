#ifndef KCP_NODE
#define KCP_NODE
#define NAPI_VERSION 4
#include <v8.h>
#include <node_api.h>
#include "./kcp/ikcp.h"

namespace kcp_node {
	class KCPObject {
		//napi_value Init(napi_env, napi_callback_info);
	private:
		/*~KCPObject();
		napi_status Release(napi_env, napi_callback_info);
		napi_status SetOutput(napi_env, napi_callback_info);
		napi_status Output(napi_env, napi_callback_info);
		napi_status Recv(napi_env, napi_callback_info);
		napi_status Send(napi_env, napi_callback_info);
		napi_status Update(napi_env, napi_callback_info);
		napi_status Check(napi_env, napi_callback_info);
		napi_status Input(napi_env, napi_callback_info);
		napi_status Flush(napi_env, napi_callback_info);
		napi_status Peeksize(napi_env, napi_callback_info);
		napi_status Setmtu(napi_env, napi_callback_info);
		napi_status Wndsize(napi_env, napi_callback_info);
		napi_status Waitsnd(napi_env, napi_callback_info);
		napi_status Nodelay(napi_env, napi_callback_info);
		napi_status Log(napi_env, napi_callback_info);*/

		ikcpcb* _ikcpcb;
		napi_value obj;
	};

	napi_value KCPCreate(napi_env, napi_callback_info);

	napi_value Init(napi_env, napi_callback_info);
}

#endif // !KCP_NODE
