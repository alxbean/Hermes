package org.msgpack.service;

import java.beans.IntrospectionException;
import java.beans.PropertyDescriptor;

import org.msgpack.commons.MsgpackMemberMap;
import org.msgpack.commons.MsgpackObjectMap;

public class MsgpackMappingService {
	public static boolean reflectObjectMembers(ClassLoader cl, String className) throws Exception {
		try {
			PropertyDescriptor[] propertyDesc = MsgpackReflect
					.getBeanPropertyDescriptor(cl, className);
			MsgpackMemberMap memberMap = new MsgpackMemberMap();
			for (PropertyDescriptor p : propertyDesc) {
				MsgpackMember member = reflectObjectMember(p);
				if (null == member) {
					throw new Exception(String.format(
							"reflect object:%s is fail.", className));
				}
				
				memberMap.insert(member.getName(), member);
			}
			
			MsgpackObject msgpackObj = new MsgpackObject();
			msgpackObj.setName(className);
			msgpackObj.setMemberMap(memberMap);
			MsgpackObjectMap.insert(className, msgpackObj);
		} catch (ClassNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (IntrospectionException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		return true;
	}
	
	public static MsgpackMember reflectObjectMember(PropertyDescriptor p){
		MsgpackMember member = new MsgpackMember();
		member.setName(p.getName());
		member.setP(p);
		member.setType(p.getPropertyType());
		
		return member;
	}
}
