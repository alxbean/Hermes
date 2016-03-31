package org.msgpack.commons;

import java.util.HashMap;
import java.util.Map;

public class MsgpackMemberMap {
	private Map<String, Object> cached = new HashMap<String, Object>();

	// no synchronized
	public  Object get(String key) throws IllegalArgumentException {
		return cached.get(key);
	}

	public synchronized  void insert(String key, Object value)
			throws IllegalArgumentException {
		cached.put(key, value);
	}

	public synchronized void remove(String key)
			throws IllegalArgumentException {
		cached.remove(key);
	}

	public synchronized void clear() {
		cached.clear();
	}
}
