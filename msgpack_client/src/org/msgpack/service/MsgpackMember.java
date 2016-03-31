package org.msgpack.service;

import java.beans.PropertyDescriptor;

public class MsgpackMember {
	private String name;
	private PropertyDescriptor p;
	private Class<?> type;

	public String getName() {
		return name;
	}

	public void setName(String name) {
		this.name = name;
	}

	public PropertyDescriptor getP() {
		return p;
	}

	public void setP(PropertyDescriptor p) {
		this.p = p;
	}

	public Class<?> getType() {
		return type;
	}

	public void setType(Class<?> type) {
		this.type = type;
	}
}
