package org.msgpack.commons;

import java.beans.PropertyDescriptor;
import java.lang.reflect.Array;
import java.lang.reflect.InvocationTargetException;
import java.util.HashMap;
import java.util.Map;

import org.msgpack.unpacker.MessagePackBufferUnpacker;

public class ConvertObject {

	public static void printHexString(byte[] b) {
		for (int i = 0; i < b.length; i++) {
			String hex = Integer.toHexString(b[i] & 0xFF);
			if (hex.length() == 1) {
				hex = '0' + hex;
			}
			System.out.print(hex.toUpperCase() + " ");
		}

		System.out.println();

	}

	public static void printHexString(byte[] b, int len) {
		for (int i = 0; i < len; i++) {
			String hex = Integer.toHexString(b[i] & 0xFF);
			if (hex.length() == 1) {
				hex = '0' + hex;
			}
			System.out.print(hex.toUpperCase() + " ");
		}

		System.out.println();

	}

	public static boolean Set(PropertyDescriptor p, Object obj,
			MessagePackBufferUnpacker unpk) {
		try {
			p.getWriteMethod().invoke(obj, Convert(unpk));
		} catch (IllegalAccessException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
			return false;
		} catch (IllegalArgumentException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
			return false;
		} catch (InvocationTargetException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
			return false;
		}

		return true;
	}

	private static Object Convert(MessagePackBufferUnpacker unpk) {
		switch (unpk.getNextType()) {
		case INTEGER: {
			int a = unpk.readInt();
			System.out.println(a);
			return a;
		}
		case RAW: {
			String a = unpk.readString();
			System.out.println(a);
			return a;
		}
		case ARRAY: {
			int len = unpk.readArrayBegin();
			Object[] a = new Object[len];

			for (int i = 0; i < len; i++) {
				a[i] = Convert(unpk);
			}
			
			try {
				unpk.readArrayEnd(false);
			} catch (Exception e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			Class<?> type = a[0].getClass();
			Object array = Array.newInstance(type, len);
			for (int i = 0; i < len; i++) {
				Array.set(array, i, a[i]);
			}
			return array;
		}
		case MAP: {
			int len = unpk.readMapBegin();
			Map<Object, Object> a = new HashMap<Object, Object>();
			for (int i = 0; i < len; i++) {
				a.put(Convert(unpk), Convert(unpk));
			}

			try {
				unpk.readMapEnd(false);
			} catch (Exception e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			return a;
		}
		case NIL: {
			System.out.println("NIL");
			return null;
		}
		case BOOLEAN: {
			try {
				boolean a = unpk.readBoolean();
				System.out.println(unpk.readBoolean());
				return a;
			} catch (Exception e) {
				e.printStackTrace();
			}
			return null;
		}
		case FLOAT: {
			Float a = unpk.readFloat();
			System.out.println(a);
			return a;
		}
		case DOUBLE: {
			Double a = unpk.readDouble();
			System.out.println(a);
			return a;
		}
		case EXT: {
			byte[] a = unpk.readExt();
			return a;
		}
		default: {
			return null;
		}
		}
	}
}
