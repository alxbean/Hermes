//
// MessagePack for Java
//
// Copyright (C) 2009 - 2013 FURUHASHI Sadayuki
//
//    Licensed under the Apache License, Version 2.0 (the "License");
//    you may not use this file except in compliance with the License.
//    You may obtain a copy of the License at
//
//        http://www.apache.org/licenses/LICENSE-2.0
//
//    Unless required by applicable law or agreed to in writing, software
//    distributed under the License is distributed on an "AS IS" BASIS,
//    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//    See the License for the specific language governing permissions and
//    limitations under the License.
//
package org.msgpack.packer;

import java.io.IOException;
import java.io.OutputStream;
import java.io.UnsupportedEncodingException;
import java.math.BigInteger;
import java.nio.ByteBuffer;

import org.msgpack.io.Output;
import org.msgpack.io.StreamOutput;

public class MessagePackPacker {
	protected final Output out;

	private PackerStack stack = new PackerStack();

	public MessagePackPacker(OutputStream stream) {
		this(new StreamOutput(stream));
	}

	public MessagePackPacker(Output out) {
		this.out = out;
	}

	public void packByte(byte d) throws IOException {
		if (d < -(1 << 5)) {
			out.writeByteAndByte((byte) 0xd0, d);
		} else {
			out.writeByte(d);
		}
		stack.reduceCount();
	}

	public void packShort(short d) throws IOException {
		if (d < -(1 << 5)) {
			if (d < -(1 << 7)) {
				// signed 16
				out.writeByteAndShort((byte) 0xd1, d);
			} else {
				// signed 8
				out.writeByteAndByte((byte) 0xd0, (byte) d);
			}
		} else if (d < (1 << 7)) {
			// fixnum
			out.writeByte((byte) d);
		} else {
			if (d < (1 << 8)) {
				// unsigned 8
				out.writeByteAndByte((byte) 0xcc, (byte) d);
			} else {
				// unsigned 16
				out.writeByteAndShort((byte) 0xcd, d);
			}
		}
		stack.reduceCount();
	}

	public void packInt(int d) throws IOException {
		if (d < -(1 << 5)) {
			if (d < -(1 << 15)) {
				// signed 32
				out.writeByteAndInt((byte) 0xd2, d);
			} else if (d < -(1 << 7)) {
				// signed 16
				out.writeByteAndShort((byte) 0xd1, (short) d);
			} else {
				// signed 8
				out.writeByteAndByte((byte) 0xd0, (byte) d);
			}
		} else if (d < (1 << 7)) {
			// fixnum
			out.writeByte((byte) d);
		} else {
			if (d < (1 << 8)) {
				// unsigned 8
				out.writeByteAndByte((byte) 0xcc, (byte) d);
			} else if (d < (1 << 16)) {
				// unsigned 16
				out.writeByteAndShort((byte) 0xcd, (short) d);
			} else {
				// unsigned 32
				out.writeByteAndInt((byte) 0xce, d);
			}
		}
		stack.reduceCount();
	}

	public void packLong(long d) throws IOException {
		if (d < -(1L << 5)) {
			if (d < -(1L << 15)) {
				if (d < -(1L << 31)) {
					// signed 64
					out.writeByteAndLong((byte) 0xd3, d);
				} else {
					// signed 32
					out.writeByteAndInt((byte) 0xd2, (int) d);
				}
			} else {
				if (d < -(1 << 7)) {
					// signed 16
					out.writeByteAndShort((byte) 0xd1, (short) d);
				} else {
					// signed 8
					out.writeByteAndByte((byte) 0xd0, (byte) d);
				}
			}
		} else if (d < (1 << 7)) {
			// fixnum
			out.writeByte((byte) d);
		} else {
			if (d < (1L << 16)) {
				if (d < (1 << 8)) {
					// unsigned 8
					out.writeByteAndByte((byte) 0xcc, (byte) d);
				} else {
					// unsigned 16
					out.writeByteAndShort((byte) 0xcd, (short) d);
				}
			} else {
				if (d < (1L << 32)) {
					// unsigned 32
					out.writeByteAndInt((byte) 0xce, (int) d);
				} else {
					// unsigned 64
					out.writeByteAndLong((byte) 0xcf, d);
				}
			}
		}
		stack.reduceCount();
	}

	public void packBigInteger(BigInteger d) throws Exception {
		if (d.bitLength() <= 63) {
			packLong(d.longValue());
			stack.reduceCount();
		} else if (d.bitLength() == 64 && d.signum() == 1) {
			// unsigned 64
			out.writeByteAndLong((byte) 0xcf, d.longValue());
			stack.reduceCount();
		} else {
			throw new Exception(
					"MessagePack can't serialize BigInteger larger than (2^64)-1");
		}
	}

	public void packFloat(float d) throws IOException {
		out.writeByteAndFloat((byte) 0xca, d);
		stack.reduceCount();
	}

	public void packDouble(double d) throws IOException {
		out.writeByteAndDouble((byte) 0xcb, d);
		stack.reduceCount();
	}

	public void packBoolean(boolean d) throws IOException {
		if (d) {
			// true
			out.writeByte((byte) 0xc3);
		} else {
			// false
			out.writeByte((byte) 0xc2);
		}
		stack.reduceCount();
	}

	public void packByteArray(byte[] b, int off, int len) throws IOException {
		if (len < 32) {
			out.writeByte((byte) (0xa0 | len));
		} else if (len < 65536) {
			out.writeByteAndShort((byte) 0xda, (short) len);
		} else {
			out.writeByteAndInt((byte) 0xdb, len);
		}
		out.write(b, off, len);
		stack.reduceCount();
	}

	public void packByteBuffer(ByteBuffer bb) throws IOException {
		int len = bb.remaining();
		if (len < 32) {
			out.writeByte((byte) (0xa0 | len));
		} else if (len < 65536) {
			out.writeByteAndShort((byte) 0xda, (short) len);
		} else {
			out.writeByteAndInt((byte) 0xdb, len);
		}
		int pos = bb.position();
		try {
			out.write(bb);
		} finally {
			bb.position(pos);
		}
		stack.reduceCount();
	}

	public void packString(String s) throws Exception {
		byte[] b;
		try {
			// TODO encoding error?
			b = s.getBytes("UTF-8");
		} catch (UnsupportedEncodingException ex) {
			throw new Exception(ex);
		}
		packByteArray(b, 0, b.length);
		stack.reduceCount();
	}

	public void packNil() throws IOException {
		out.writeByte((byte) 0xc0);
		stack.reduceCount();
		// return this;
	}

	public void packArrayHeader(int size) throws IOException {
		// TODO check size < 0?
		if (size < 16) {
			// FixArray
			out.writeByte((byte) (0x90 | size));
		} else if (size < 65536) {
			out.writeByteAndShort((byte) 0xdc, (short) size);
		} else {
			out.writeByteAndInt((byte) 0xdd, size);
		}
		stack.reduceCount();
		stack.pushArray(size);
		// return this;
	}

	public void packArrayEnd(boolean check) throws Exception {
		if (!stack.topIsArray()) {
			throw new Exception(
					"writeArrayEnd() is called but writeArrayBegin() is not called");
		}

		int remain = stack.getTopCount();
		if (remain > 0) {
			if (check) {
				throw new Exception(
						"writeArrayEnd(check=true) is called but the array is not end: "
								+ remain);
			}
			for (int i = 0; i < remain; i++) {
				packNil();
			}
		}
		stack.pop();
		// return this;
	}

	public void packMapHeader(int size) throws IOException {
		// TODO check size < 0?
		if (size < 16) {
			// FixMap
			out.writeByte((byte) (0x80 | size));
		} else if (size < 65536) {
			out.writeByteAndShort((byte) 0xde, (short) size);
		} else {
			out.writeByteAndInt((byte) 0xdf, size);
		}
		stack.reduceCount();
		stack.pushMap(size);
		// return this;
	}

	public void writeMapEnd(boolean check) throws Exception {
		if (!stack.topIsMap()) {
			throw new Exception(
					"writeMapEnd() is called but writeMapBegin() is not called");
		}

		int remain = stack.getTopCount();
		if (remain > 0) {
			if (check) {
				throw new Exception(
						"writeMapEnd(check=true) is called but the map is not end: "
								+ remain);
			}
			for (int i = 0; i < remain; i++) {
				packNil();
			}
		}
		stack.pop();
		// return this;
	}

	public void packExtensionTypeHeader(byte type, int size) throws IOException {
		// TODO check size < 0?
		if(size == 1){
			out.writeByteAndByte((byte)0xd4, type);
		} else if(size == 2){
			out.writeByteAndByte((byte)0xd5, type);
		} else if(size == 4){
			out.writeByteAndByte((byte)0xd6, type);
		} else if(size == 8){
			out.writeByteAndByte((byte)0xd7, type);
		} else if(size == 16){
			out.writeByteAndByte((byte)0xd8, type);
		} else if (size < 256) {
			out.writeByteAndByte((byte)0xc7, (byte)size);
			out.writeByte(type);
		} else if (size < 65536) {
			out.writeByteAndShort((byte) 0xc8, (short) size);
			out.writeByte(type);
		} else {
			out.writeByteAndInt((byte) 0xc9, size);
			out.writeByte(type);
		}
		
		stack.reduceCount();
	}

	
	public void addPayload(byte[] body){
		ByteBuffer bb = ByteBuffer.wrap(body);
		try {
			out.write(bb);
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		stack.reduceCount();
	}

	public void reset() {
		stack.clear();
	}

	public void flush() throws IOException {
		out.flush();
	}

	public void close() throws IOException {
		out.close();
	}
}
