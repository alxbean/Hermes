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
package org.msgpack.unpacker;

import java.io.EOFException;
import java.io.IOException;
import java.io.InputStream;
import java.math.BigInteger;

import org.msgpack.io.BufferReferer;
import org.msgpack.io.Input;
import org.msgpack.io.StreamInput;
import org.msgpack.packer.msgpackType;

public class MessagePackUnpacker {
	protected int rawSizeLimit = 134217728;

	protected int arraySizeLimit = 4194304;

	protected int mapSizeLimit = 2097152;

	private static final byte REQUIRE_TO_READ_HEAD = (byte) 0xc1;

	protected final Input in;
	private final UnpackerStack stack = new UnpackerStack();

	private byte headByte = REQUIRE_TO_READ_HEAD;
	private byte type = 0;

	private byte[] raw;
	private int rawFilled;

	private final IntAccept intAccept = new IntAccept();
	private final LongAccept longAccept = new LongAccept();
	private final BigIntegerAccept bigIntegerAccept = new BigIntegerAccept();
	private final DoubleAccept doubleAccept = new DoubleAccept();
	private final ByteArrayAccept byteArrayAccept = new ByteArrayAccept();
	private final StringAccept stringAccept = new StringAccept();
	private final ArrayAccept arrayAccept = new ArrayAccept();
	private final MapAccept mapAccept = new MapAccept();
	private final ExtAccept extAccept = new ExtAccept();
	// private final ValueAccept valueAccept = new ValueAccept();
	private final SkipAccept skipAccept = new SkipAccept();

	public MessagePackUnpacker(InputStream stream) {
		this(new StreamInput(stream));
	}

	public MessagePackUnpacker(Input in) {
		this.in = in;
	}

	private byte getHeadByte() {
		byte b = headByte;
		if (b == REQUIRE_TO_READ_HEAD) {
			try {
				b = headByte = in.readByte();
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
		return b;
	}

	final void readOne(Accept a) {
		try {
			stack.checkCount();
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		try {
			if (readOneWithoutStack(a)) {
				stack.reduceCount();
			}
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}

	final boolean readOneWithoutStack(Accept a) throws Exception {
		if (raw != null) {
			readRawBodyCont();
			a.acceptRaw(raw);
			raw = null;
			headByte = REQUIRE_TO_READ_HEAD;
			return true;
		}

		final int b = (int) getHeadByte();

		if ((b & 0x80) == 0) { // Positive Fixnum
			// System.out.println("positive fixnum "+b);
			a.acceptInteger(b);
			headByte = REQUIRE_TO_READ_HEAD;
			return true;
		}

		if ((b & 0xe0) == 0xe0) { // Negative Fixnum
			// System.out.println("negative fixnum "+b);
			a.acceptInteger(b);
			headByte = REQUIRE_TO_READ_HEAD;
			return true;
		}

		if ((b & 0xe0) == 0xa0) { // FixRaw
			int count = b & 0x1f;
			if (count == 0) {
				a.acceptEmptyRaw();
				headByte = REQUIRE_TO_READ_HEAD;
				return true;
			}
			if (!tryReferRawBody(a, count)) {
				readRawBody(count);
				a.acceptRaw(raw);
				raw = null;
			}
			headByte = REQUIRE_TO_READ_HEAD;
			return true;
		}

		if ((b & 0xf0) == 0x90) { // FixArray
			int count = b & 0x0f;
			// System.out.println("fixarray count:"+count);
			a.acceptArray(count);
			stack.reduceCount();
			stack.pushArray(count);
			headByte = REQUIRE_TO_READ_HEAD;
			return false;
		}

		if ((b & 0xf0) == 0x80) { // FixMap
			int count = b & 0x0f;
			// System.out.println("fixmap count:"+count/2);
			a.acceptMap(count);
			stack.reduceCount();
			stack.pushMap(count);
			headByte = REQUIRE_TO_READ_HEAD;
			return false;
		}
		
		if ((b & 0xff) == 0xd4) { // FixExt 1
			type = in.readByte();//read type;
			int count = 1;
			if (!tryReferRawBody(a, count)) {
				readRawBody(count);
				a.acceptRaw(raw);
				raw = null;
			}
			
			headByte = REQUIRE_TO_READ_HEAD;
			return true;
		}
		
		if ((b & 0xff) == 0xd5) { // FixExt 2
			type = in.readByte();//read type;
			int count = 2;
			if (!tryReferRawBody(a, count)) {
				readRawBody(count);
				a.acceptRaw(raw);
				raw = null;
			}
			
			headByte = REQUIRE_TO_READ_HEAD;
			return true;
		}

		if ((b & 0xff) == 0xd6) { // FixExt 4
			type = in.readByte();//read type;
			int count = 4;
			if (!tryReferRawBody(a, count)) {
				readRawBody(count);
				a.acceptRaw(raw);
				raw = null;
			}
			
			headByte = REQUIRE_TO_READ_HEAD;
			return true;
		}
		
		if ((b & 0xff) == 0xd8) { // FixExt 8
			type = in.readByte();//read type;
			int count = 4;
			if (!tryReferRawBody(a, count)) {
				readRawBody(count);
				a.acceptRaw(raw);
				raw = null;
			}
			
			headByte = REQUIRE_TO_READ_HEAD;
			return true;
		}
		
		if ((b & 0xff) == 0xd16) { // FixExt 16
			type = in.readByte();//read type;
			int count = 16;
			if (!tryReferRawBody(a, count)) {
				readRawBody(count);
				a.acceptRaw(raw);
				raw = null;
			}
			
			headByte = REQUIRE_TO_READ_HEAD;
			return true;
		}

		return readOneWithoutStackLarge(a, b);
	}

	private boolean readOneWithoutStackLarge(Accept a, final int b)
			throws Exception {
		switch (b & 0xff) {
		case 0xc0: // nil
			a.acceptNil();
			headByte = REQUIRE_TO_READ_HEAD;
			return true;
		case 0xc2: // false
			a.acceptBoolean(false);
			headByte = REQUIRE_TO_READ_HEAD;
			return true;
		case 0xc3: // true
			a.acceptBoolean(true);
			headByte = REQUIRE_TO_READ_HEAD;
			return true;
			// case 0xc4: // bin 8 -> see 0xd9
			// case 0xc5: // bin 16 -> see 0xda
			// case 0xc6: // bin 32 -> see 0xdb
		case 0xca: // float
			a.acceptFloat(in.getFloat());
			in.advance();
			headByte = REQUIRE_TO_READ_HEAD;
			return true;
		case 0xcb: // double
			a.acceptDouble(in.getDouble());
			in.advance();
			headByte = REQUIRE_TO_READ_HEAD;
			return true;
		case 0xcc: // unsigned int 8
			a.acceptUnsignedInteger(in.getByte());
			in.advance();
			headByte = REQUIRE_TO_READ_HEAD;
			return true;
		case 0xcd: // unsigned int 16
			a.acceptUnsignedInteger(in.getShort());
			in.advance();
			headByte = REQUIRE_TO_READ_HEAD;
			return true;
		case 0xce: // unsigned int 32
			a.acceptUnsignedInteger(in.getInt());
			in.advance();
			headByte = REQUIRE_TO_READ_HEAD;
			return true;
		case 0xcf: // unsigned int 64
			a.acceptUnsignedInteger(in.getLong());
			in.advance();
			headByte = REQUIRE_TO_READ_HEAD;
			return true;
		case 0xd0: // signed int 8
			a.acceptInteger(in.getByte());
			in.advance();
			headByte = REQUIRE_TO_READ_HEAD;
			return true;
		case 0xd1: // signed int 16
			a.acceptInteger(in.getShort());
			in.advance();
			headByte = REQUIRE_TO_READ_HEAD;
			return true;
		case 0xd2: // signed int 32
			a.acceptInteger(in.getInt());
			in.advance();
			headByte = REQUIRE_TO_READ_HEAD;
			return true;
		case 0xd3: // signed int 64
			a.acceptInteger(in.getLong());
			in.advance();
			headByte = REQUIRE_TO_READ_HEAD;
			return true;
		case 0xc4: // bin 8
		case 0xd9: // str 8
		{
			int count = in.getByte() & 0xff;
			if (count == 0) {
				a.acceptEmptyRaw();
				in.advance();
				headByte = REQUIRE_TO_READ_HEAD;
				return true;
			}
			if (count >= rawSizeLimit) {
				String reason = String.format(
						"Size of raw (%d) over limit at %d", new Object[] {
								count, rawSizeLimit });
				throw new SizeLimitException(reason);
			}
			in.advance();
			if (!tryReferRawBody(a, count)) {
				readRawBody(count);
				a.acceptRaw(raw);
				raw = null;
			}
			headByte = REQUIRE_TO_READ_HEAD;
			return true;
		}
		case 0xc5: // bin 16
		case 0xda: // raw 16
		{
			int count = in.getShort() & 0xffff;
			if (count == 0) {
				a.acceptEmptyRaw();
				in.advance();
				headByte = REQUIRE_TO_READ_HEAD;
				return true;
			}
			if (count >= rawSizeLimit) {
				String reason = String.format(
						"Size of raw (%d) over limit at %d", new Object[] {
								count, rawSizeLimit });
				throw new SizeLimitException(reason);
			}
			in.advance();
			if (!tryReferRawBody(a, count)) {
				readRawBody(count);
				a.acceptRaw(raw);
				raw = null;
			}
			headByte = REQUIRE_TO_READ_HEAD;
			return true;
		}
		case 0xc6: // bin 32
		case 0xdb: // raw 32
		{
			int count = in.getInt();
			if (count == 0) {
				a.acceptEmptyRaw();
				in.advance();
				headByte = REQUIRE_TO_READ_HEAD;
				return true;
			}
			if (count < 0 || count >= rawSizeLimit) {
				String reason = String.format(
						"Size of raw (%d) over limit at %d", new Object[] {
								count, rawSizeLimit });
				throw new SizeLimitException(reason);
			}
			in.advance();
			if (!tryReferRawBody(a, count)) {
				readRawBody(count);
				a.acceptRaw(raw);
				raw = null;
			}
			headByte = REQUIRE_TO_READ_HEAD;
			return true;
		}
		case 0xdc: // array 16
		{
			int count = in.getShort() & 0xffff;
			if (count >= arraySizeLimit) {
				String reason = String.format(
						"Size of array (%d) over limit at %d", new Object[] {
								count, arraySizeLimit });
				throw new SizeLimitException(reason);
			}
			a.acceptArray(count);
			stack.reduceCount();
			stack.pushArray(count);
			in.advance();
			headByte = REQUIRE_TO_READ_HEAD;
			return false;
		}
		case 0xdd: // array 32
		{
			int count = in.getInt();
			if (count < 0 || count >= arraySizeLimit) {
				String reason = String.format(
						"Size of array (%d) over limit at %d", new Object[] {
								count, arraySizeLimit });
				throw new SizeLimitException(reason);
			}
			a.acceptArray(count);
			stack.reduceCount();
			stack.pushArray(count);
			in.advance();
			headByte = REQUIRE_TO_READ_HEAD;
			return false;
		}
		case 0xde: // map 16
		{
			int count = in.getShort() & 0xffff;
			if (count >= mapSizeLimit) {
				String reason = String.format(
						"Size of map (%d) over limit at %d", new Object[] {
								count, mapSizeLimit });
				throw new SizeLimitException(reason);
			}
			a.acceptMap(count);
			stack.reduceCount();
			stack.pushMap(count);
			in.advance();
			headByte = REQUIRE_TO_READ_HEAD;
			return false;
		}
		case 0xdf: // map 32
		{
			int count = in.getInt();
			if (count < 0 || count >= mapSizeLimit) {
				String reason = String.format(
						"Size of map (%d) over limit at %d", new Object[] {
								count, mapSizeLimit });
				throw new SizeLimitException(reason);
			}
			a.acceptMap(count);
			stack.reduceCount();
			stack.pushMap(count);
			in.advance();
			headByte = REQUIRE_TO_READ_HEAD;
			return false;
		}
		
		case 0xc7: // ext 8
		{
			int count = in.getByte() & 0xff;
			type = in.readByte();//read type;

			if (count == 0) {
				a.acceptEmptyRaw();
				in.advance();
				headByte = REQUIRE_TO_READ_HEAD;
				return true;
			}
			if (count < 0 || count >= rawSizeLimit) {
				String reason = String.format(
						"Size of ext (%d) over limit at %d", new Object[] {
								count, rawSizeLimit });
				throw new SizeLimitException(reason);
			}
			in.advance();
			if (!tryReferRawBody(a, count)) {
				readRawBody(count);
				a.acceptRaw(raw);
				raw = null;
			}
			headByte = REQUIRE_TO_READ_HEAD;
			return true;
		}
		
		case 0xc8: // ext 16
		{
			int count = in.getShort() & 0xffff;
			type = in.readByte();//read type;

			if (count == 0) {
				a.acceptEmptyRaw();
				in.advance();
				headByte = REQUIRE_TO_READ_HEAD;
				return true;
			}
			if (count < 0 || count >= rawSizeLimit) {
				String reason = String.format(
						"Size of ext (%d) over limit at %d", new Object[] {
								count, rawSizeLimit });
				throw new SizeLimitException(reason);
			}
			in.advance();
			if (!tryReferRawBody(a, count)) {
				readRawBody(count);
				a.acceptRaw(raw);
				raw = null;
			}
			headByte = REQUIRE_TO_READ_HEAD;
			return true;
		}
		
		case 0xc9: // ext 32
		{
			int count = in.getInt();
			type = in.readByte();//read type;

			if (count == 0) {
				a.acceptEmptyRaw();
				in.advance();
				headByte = REQUIRE_TO_READ_HEAD;
				return true;
			}
			if (count < 0 || count >= rawSizeLimit) {
				String reason = String.format(
						"Size of ext (%d) over limit at %d", new Object[] {
								count, rawSizeLimit });
				throw new SizeLimitException(reason);
			}
			in.advance();
			if (!tryReferRawBody(a, count)) {
				readRawBody(count);
				a.acceptRaw(raw);
				raw = null;
			}
			headByte = REQUIRE_TO_READ_HEAD;
			return true;
		}
		
		default:
			// System.out.println("unknown b "+(b&0xff));
			// headByte = CS_INVALID
			headByte = REQUIRE_TO_READ_HEAD;
			throw new IOException("Invalid byte: " + b); // TODO error
															// FormatException
		}
	}

	private boolean tryReferRawBody(BufferReferer referer, int size) {
		try {
			return in.tryRefer(referer, size);
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		return false;
	}

	private void readRawBody(int size) throws Exception {
		raw = new byte[size];
		rawFilled = 0;
		readRawBodyCont();
	}

	private void readRawBodyCont() throws Exception {
		int len = in.read(raw, rawFilled, raw.length - rawFilled);
		rawFilled += len;
		if (rawFilled < raw.length) {
			try {
				throw new EOFException();
			} catch (EOFException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
	}

	public boolean tryReadNil() throws Exception {
		stack.checkCount();
		int b = getHeadByte() & 0xff;
		if (b == 0xc0) {
			// nil is read
			stack.reduceCount();
			headByte = REQUIRE_TO_READ_HEAD;
			return true;
		}
		// not nil
		return false;
	}

	public boolean trySkipNil() throws IOException {
		if (stack.getDepth() > 0 && stack.getTopCount() <= 0) {
			// end of array or map
			return true;
		}

		int b = getHeadByte() & 0xff;
		if (b == 0xc0) {
			// nil is skipped
			stack.reduceCount();
			headByte = REQUIRE_TO_READ_HEAD;
			return true;
		}
		// not nil
		return false;
	}

	public void readNil() throws Exception {
		// optimized not to allocate nilAccept
		stack.checkCount();
		int b = getHeadByte() & 0xff;
		if (b == 0xc0) {
			stack.reduceCount();
			headByte = REQUIRE_TO_READ_HEAD;
			return;
		}
		throw new Exception("Expected nil but got not nil value");
	}

	public boolean readBoolean() throws Exception {
		// optimized not to allocate booleanAccept
		stack.checkCount();
		int b = getHeadByte() & 0xff;
		if (b == 0xc2) {
			stack.reduceCount();
			headByte = REQUIRE_TO_READ_HEAD;
			return false;
		} else if (b == 0xc3) {
			stack.reduceCount();
			headByte = REQUIRE_TO_READ_HEAD;
			return true;
		}
		throw new Exception("Expected Boolean but got not boolean value");
	}

	public byte readByte() throws Exception {
		// optimized not to allocate byteAccept
		stack.checkCount();
		readOneWithoutStack(intAccept);
		int value = intAccept.value;
		if (value < (int) Byte.MIN_VALUE || value > (int) Byte.MAX_VALUE) {
			throw new Exception(); // TODO message
		}
		stack.reduceCount();
		return (byte) value;
	}

	public short readShort() throws Exception {
		// optimized not to allocate shortAccept
		stack.checkCount();
		readOneWithoutStack(intAccept);
		int value = intAccept.value;
		if (value < (int) Short.MIN_VALUE || value > (int) Short.MAX_VALUE) {
			throw new Exception(); // TODO message
		}
		stack.reduceCount();
		return (short) value;
	}

	public int readInt() {
		readOne(intAccept);
		return intAccept.value;
	}

	public long readLong() throws Exception {
		readOne(longAccept);
		return longAccept.value;
	}

	public BigInteger readBigInteger(){
		readOne(bigIntegerAccept);
		return bigIntegerAccept.value;
	}

	public float readFloat() {
		readOne(doubleAccept);
		return (float) doubleAccept.value;
	}

	public double readDouble(){
		readOne(doubleAccept);
		return doubleAccept.value;
	}

	public byte[] readByteArray(){
		readOne(byteArrayAccept);
		return byteArrayAccept.value;
	}

	public String readString() {
		readOne(stringAccept);
		return stringAccept.value;
	}

	public byte[] readExt() {
		readOne(extAccept);
		return extAccept.value;
	}
	
	public int readArrayBegin() {
		readOne(arrayAccept);
		return arrayAccept.size;
	}

	public void readArrayEnd(boolean check) throws Exception {
		if (!stack.topIsArray()) {
			throw new Exception(
					"readArrayEnd() is called but readArrayBegin() is not called");
		}

		int remain = stack.getTopCount();
		if (remain > 0) {
			if (check) {
				throw new Exception(
						"readArrayEnd(check=true) is called but the array is not end");
			}
			for (int i = 0; i < remain; i++) {
				skip();
			}
		}
		stack.pop();
	}

	public int readMapBegin(){
		readOne(mapAccept);
		return mapAccept.size;
	}

	public void readMapEnd(boolean check) throws Exception {
		if (!stack.topIsMap()) {
			throw new Exception(
					"readMapEnd() is called but readMapBegin() is not called");
		}

		int remain = stack.getTopCount();
		if (remain > 0) {
			if (check) {
				throw new Exception(
						"readMapEnd(check=true) is called but the map is not end");
			}
			for (int i = 0; i < remain; i++) {
				skip();
			}
		}
		stack.pop();
	}

	public boolean hasNext() {
		if (in.getSize() > 0)
			return true;
		else
			return false;
	}

	// public void readValue(Unconverter uc) throws IOException {
	// if (uc.getResult() != null) {
	// uc.resetResult();
	// }
	// valueAccept.setUnconverter(uc);
	//
	// stack.checkCount();
	// if (readOneWithoutStack(valueAccept)) {
	// stack.reduceCount();
	// if (uc.getResult() != null) {
	// return;
	// }
	// }
	// while (true) {
	// while (stack.getTopCount() == 0) {
	// if (stack.topIsArray()) {
	// uc.writeArrayEnd(true);
	// stack.pop();
	// // stack.reduceCount();
	// } else if (stack.topIsMap()) {
	// uc.writeMapEnd(true);
	// stack.pop();
	// // stack.reduceCount();
	// } else {
	// throw new RuntimeException("invalid stack"); // FIXME error?
	// }
	// if (uc.getResult() != null) {
	// return;
	// }
	// }
	// readOne(valueAccept);
	// }
	// }

	public void skip() throws Exception {
		stack.checkCount();
		if (readOneWithoutStack(skipAccept)) {
			stack.reduceCount();
			return;
		}
		int targetDepth = stack.getDepth() - 1;
		while (true) {
			while (stack.getTopCount() == 0) {
				stack.pop();
				if (stack.getDepth() <= targetDepth) {
					return;
				}
			}
			readOne(skipAccept);
		}
	}

	public msgpackType getNextType() {
		headByte =  getHeadByte();
		final int b = (int) headByte;
		
		if ((b & 0x80) == 0) { // Positive Fixnum
			return msgpackType.INTEGER;
		}
		if ((b & 0xe0) == 0xe0) { // Negative Fixnum
			return msgpackType.INTEGER;
		}
		if ((b & 0xe0) == 0xa0) { // FixRaw
			return msgpackType.RAW;
		}
		if ((b & 0xf0) == 0x90) { // FixArray
			return msgpackType.ARRAY;
		}
		if ((b & 0xf0) == 0x80) { // FixMap
			return msgpackType.MAP;
		}
		switch (b & 0xff) {
		case 0xc0: // nil
			return msgpackType.NIL;
		case 0xc2: // false
		case 0xc3: // true
			return msgpackType.BOOLEAN;
		case 0xca: // float
			return msgpackType.FLOAT;
		case 0xcb: // double
			return msgpackType.DOUBLE;
		case 0xcc: // unsigned int 8
		case 0xcd: // unsigned int 16
		case 0xce: // unsigned int 32
		case 0xcf: // unsigned int 64
		case 0xd0: // signed int 8
		case 0xd1: // signed int 16
		case 0xd2: // signed int 32
		case 0xd3: // signed int 64
			return msgpackType.INTEGER;
			// The definition based on a minor upgrade guide.
			// https://github.com/msgpack/msgpack/blob/master/spec.md#impl-upgrade
		case 0xc4: // bin 8
		case 0xc5: // bin 16
		case 0xc6: // bin 32
		case 0xd9: // str8
		case 0xda: // raw 16
		case 0xdb: // raw 32
			return msgpackType.RAW;
		case 0xdc: // array 16
		case 0xdd: // array 32
			return msgpackType.ARRAY;
		case 0xde: // map 16
		case 0xdf: // map 32
			return msgpackType.MAP;
		case 0xd4:
		case 0xd5:
		case 0xd6:
		case 0xd7:
		case 0xd8:
		case 0xc7:
		case 0xc8:
		case 0xc9:
			return msgpackType.EXT;
		default:
			return null; // TODO error FormatException
		}
	}

	public void reset() {
		raw = null;
		stack.clear();
	}

	public void close() throws IOException {
		in.close();
	}

	public int getReadByteCount() {
		return in.getReadByteCount();
	}

	public void resetReadByteCount() {
		in.resetReadByteCount();
	}
}
