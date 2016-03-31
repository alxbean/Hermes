package org.msgpack.unpacker;

import java.io.IOException;
import java.nio.ByteBuffer;

final class ExtAccept extends Accept {
	byte[] value;

	ExtAccept() {
		super("ext");
	}

	@Override
	void acceptRaw(byte[] raw) {
		this.value = raw;
	}

	@Override
	void acceptEmptyRaw() {
		this.value = new byte[0];
	}

	@Override
	public void refer(ByteBuffer bb, boolean gift) throws IOException {
		// TODO gift
		this.value = new byte[bb.remaining()];
		bb.get(value);
	}
}
