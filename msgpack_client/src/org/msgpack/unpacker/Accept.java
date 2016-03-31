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

import java.nio.ByteBuffer;

import org.msgpack.io.BufferReferer;

abstract class Accept implements BufferReferer {
    private final String expected;

    Accept(String expected) {
        this.expected = expected;
    }

    void acceptBoolean(boolean v) throws Exception {
        throw new Exception(String.format("Expected %s, but got boolean", expected));
    }

    void acceptInteger(byte v) throws Exception {
        throw new Exception(String.format("Expected %s, but got integer value", expected));
    }

    void acceptInteger(short v) throws Exception {
        throw new Exception(String.format("Expected %s, but got integer value", expected));
    }

    void acceptInteger(int v) throws Exception {
        throw new Exception(String.format("Expected %s, but got integer value", expected));
    }

    void acceptInteger(long v) throws Exception {
        throw new Exception(String.format("Expected %s, but got integer value", expected));
    }

    void acceptUnsignedInteger(byte v) throws Exception {
        throw new Exception(String.format("Expected %s, but got integer value", expected));
    }

    void acceptUnsignedInteger(short v) throws Exception {
        throw new Exception(String.format("Expected %s, but got integer value", expected));
    }

    void acceptUnsignedInteger(int v) throws Exception {
        throw new Exception(String.format("Expected %s, but got integer value", expected));
    }

    void acceptUnsignedInteger(long v) throws Exception {
        throw new Exception(String.format("Expected %s, but got integer value", expected));
    }

    // void checkRawAcceptable() throws Exception {
    // throw new Exception("Unexpected raw value");
    // }

    void acceptRaw(byte[] raw) throws Exception {
        throw new Exception(String.format("Expected %s, but got raw value", expected));
    }

    void acceptEmptyRaw() throws Exception {
        throw new Exception(String.format("Expected %s, but got raw value", expected));
    }
    
    // void checkArrayAcceptable(int size) throws Exception {
    // throw new Exception("Unexpected array value");
    // }

    void acceptArray(int size) throws Exception {
        throw new Exception(String.format("Expected %s, but got array value", expected));
    }

    // void checkMapAcceptable(int size) throws Exception {
    // throw new Exception("Unexpected map value");
    // }

    void acceptMap(int size) throws Exception {
        throw new Exception(String.format("Expected %s, but got map value", expected));
    }

    void acceptNil() throws Exception {
        throw new Exception(String.format("Expected %s, but got nil value", expected));
    }

    void acceptFloat(float v) throws Exception {
        throw new Exception(String.format("Expected %s, but got float value", expected));
    }

    void acceptDouble(double v) throws Exception {
        throw new Exception(String.format("Expected %s, but got float value", expected));
    }

    public void refer(ByteBuffer bb, boolean gift) throws Exception {
        throw new Exception(String.format("Expected %s, but got raw value", expected));
    }
}
