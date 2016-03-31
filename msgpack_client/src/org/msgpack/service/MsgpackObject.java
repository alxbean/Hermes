package org.msgpack.service;

import org.msgpack.commons.MsgpackMemberMap;

public class MsgpackObject {
	private String name = null;
	private MsgpackMemberMap memberMap = null;

	public String getName() {
		return name;
	}

	public void setName(String name) {
		this.name = name;
	}

	public MsgpackMemberMap getMemberMap() {
		return memberMap;
	}

	public void setMemberMap(MsgpackMemberMap memberMap) {
		this.memberMap = memberMap;
	}
	
	
}
