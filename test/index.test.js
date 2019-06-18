const kcp_node = require('../build/Release/kcp')

describe('kcp-node base unit test', () => {
	it('should have exports', () => {
		expect(typeof kcp_node.create).toBe('function')
	})
})
