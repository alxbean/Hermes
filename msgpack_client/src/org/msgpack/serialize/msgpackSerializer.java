package org.msgpack.serialize;

import java.beans.PropertyDescriptor;
import java.io.IOException;
import java.lang.reflect.Field;
import java.util.List;
import java.util.Map;

import org.msgpack.commons.ConvertObject;
import org.msgpack.commons.MsgpackObjectMap;
import org.msgpack.packer.MessagePackBufferPacker;
import org.msgpack.packer.msgpackType;
import org.msgpack.service.MsgpackMappingService;
import org.msgpack.service.MsgpackMember;
import org.msgpack.service.MsgpackObject;
import org.msgpack.unpacker.MessagePackBufferUnpacker;

public class msgpackSerializer {
	private static byte EXTTYPE = 0;

	private boolean BaseTypeSerialize(MessagePackBufferPacker packer, Object obj) {
		if (obj instanceof Integer) {
			int value = ((Integer) obj).intValue();
			try {
				packer.packInt(value);
				return true;
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		} else if (obj instanceof String) {
			String s = (String) obj;
			try {
				packer.packString(s);
			} catch (Exception e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			return true;
		} else if (obj instanceof Double) {
			double d = ((Double) obj).doubleValue();
			try {
				packer.packDouble(d);
				return true;
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		} else if (obj instanceof Float) {
			float f = ((Float) obj).floatValue();
			try {
				packer.packFloat(f);
				return true;
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		} else if (obj instanceof Long) {
			long l = ((Long) obj).longValue();
			try {
				packer.packLong(l);
				return true;
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		} else if (obj instanceof Boolean) {
			boolean b = ((Boolean) obj).booleanValue();
			try {
				packer.packBoolean(b);
				return true;
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		} else if (obj.getClass().isArray()) {
			Object[] objArray = (Object[]) obj;
			try {
				packer.packArrayHeader(objArray.length);
				for (int i = 0; i < objArray.length; i++) {
					if (objArray[i] != null
							&& BaseTypeSerialize(packer, objArray[i]) == false) {
						msgpackSerialize(packer, objArray[i]);
					}
				}
				return true;
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		} else if (obj instanceof Map<?, ?>) {
			Map<?, ?> map = (Map<?, ?>) obj;
			try {
				packer.packMapHeader(map.size());
				for (Map.Entry<?, ?> entry : map.entrySet()) {
					if (BaseTypeSerialize(packer, entry.getKey()) == false) {
						msgpackSerialize(packer, entry.getKey());
					}
					if (BaseTypeSerialize(packer, entry.getValue()) == false) {
						msgpackSerialize(packer, entry.getValue());
					}
				}
				return true;
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		} else if (obj instanceof List<?>) {
			List<?> objList = (List<?>) obj;
			try {
				packer.packArrayHeader(objList.size());
				for (Object o : objList) {
					if (o != null && BaseTypeSerialize(packer, o) == false) {
						msgpackSerialize(packer, o);
					}
				}
				return true;
			} catch (Exception e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}

		return false;
	}

	public boolean msgpackSerialize(MessagePackBufferPacker packer, Object obj) {
		if (BaseTypeSerialize(packer, obj) == true)
			return true;

		MessagePackBufferPacker tmpPacker = new MessagePackBufferPacker();
		Field[] fields = obj.getClass().getDeclaredFields();
		for (Field f : fields) {
			boolean accessFlag = f.isAccessible();
			f.setAccessible(true);
			String attrName = f.getName();
			Object attrValue = null;
			try {
				attrValue = f.get(obj);
			} catch (IllegalArgumentException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
				return false;
			} catch (IllegalAccessException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
				return false;
			}
			System.out.println(attrName + ":" + attrValue);
			try {
				tmpPacker.packString(attrName);
			} catch (Exception e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}

			System.out.println(attrValue.getClass().getTypeName());
			if (BaseTypeSerialize(tmpPacker, attrValue) == false) {
				msgpackSerialize(tmpPacker, attrValue);
			}

			f.setAccessible(accessFlag);
		}

		try {
			packer.packExtensionTypeHeader((byte) EXTTYPE,
					tmpPacker.toByteArray().length);
			packer.addPayload(tmpPacker.toByteArray());
			tmpPacker.close();
		} catch (IOException e1) {
			// TODO Auto-generated catch block
			e1.printStackTrace();
		}

		return true;
	}
	
	
	public static Object unmsgpackSerialize(byte[] bytes, Class<?> clz) {
		MessagePackBufferUnpacker unpacker = new MessagePackBufferUnpacker();
		unpacker.feed(bytes);
		MsgpackObject msgpackObj = (MsgpackObject) MsgpackObjectMap.get(clz.getName());
		if(msgpackObj == null){
			try {
				MsgpackMappingService.reflectObjectMembers(clz.getClassLoader(), clz.getName());
			} catch (Exception e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			msgpackObj = (MsgpackObject) MsgpackObjectMap.get(clz.getName());
			if (msgpackObj == null){
				try {
					throw new Exception("reflectObjectMembers error");
				} catch (Exception e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
			}
		}
		
		Object obj = null;
		try {						
			if (unpacker.getNextType() == msgpackType.EXT) {
				return unmsgpackSerialize(unpacker.readExt(), clz);
			} else {
				obj = clz.newInstance();
				while (unpacker.hasNext()) {
					String attr_name = null;
					if (unpacker.getNextType() == msgpackType.RAW)
						attr_name = unpacker.readString();
					MsgpackMember member = (MsgpackMember)msgpackObj.getMemberMap().get(attr_name);
					PropertyDescriptor p = member.getP();
					if(p == null){
						throw new Exception("PropertyDescriptor of member:" + member.getName() +"is null");
					}
					
					if (unpacker.getNextType() == msgpackType.EXT) {
						p.getWriteMethod().invoke(obj, unmsgpackSerialize(unpacker.readExt(), member.getType()));
					}else{
						ConvertObject.Set(p, obj, unpacker);
					}
				}
			}
		} catch (Exception e1) {
			// TODO Auto-generated catch block
			e1.printStackTrace();
		}

		return obj;
	}
}
