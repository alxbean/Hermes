package org.msgpack.commons;

import java.util.HashMap;
import java.util.Map;

public class MsgpackObjectMap {
	private static Map<String, Object> cached = new HashMap<String, Object>();

	// no synchronized
	public static Object get(String key) throws IllegalArgumentException {
		return cached.get(key);
	}

	public synchronized static void insert(String key, Object value)
			throws IllegalArgumentException {
		cached.put(key, value);
	}

	public synchronized static void remove(String key)
			throws IllegalArgumentException {
		cached.remove(key);
	}

	public synchronized static void clear() {
		cached.clear();
	}
}
