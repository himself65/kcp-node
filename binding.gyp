{
  "targets": [
    {
      "target_name": "kcp",
      "sources": [
        "./deps/kcp/ikcp.c",
        "./lib/kcp-node.cc"
      ],
      'cflags_cc ': ['-std=c++17']
    }
  ]
}
