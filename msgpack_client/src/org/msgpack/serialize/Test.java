package org.msgpack.serialize;

import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.net.Socket;
import java.util.HashMap;
import java.util.Map;

import org.msgpack.commons.ConvertObject;
import org.msgpack.packer.MessagePackBufferPacker;

public class Test {

	public static byte[] Send2Server(byte[] bt) throws Exception {
		// 连接服务器
		String ip = "192.168.33.10";
		int port = 6666;
		Socket socket = new Socket(ip, port); // 创建一个Socket对象，连接IP地址为192.168.24.177的服务器的5566端口
		DataOutputStream request = new DataOutputStream(
				socket.getOutputStream()); // 获取Socket对象的输出流，并且在外边包一层DataOutputStream管道，方便输出数据
		request.write(bt); // DataOutputStream对象的writeUTF()方法可以输出数据 ，并且支持中文

		DataInputStream response = new DataInputStream(socket.getInputStream()); // 获取Socket对象的输出流，并且在外边包一层DataOutputStream管道，方便输出数据
		byte b[] = new byte[4096];
		int off = 0;
		int len = 0;
		while ((len = response.read(b)) != -1) {
			off += len;
		}

		request.flush(); // 确保所有数据都已经输出
		request.close(); // 关闭输出流
		response.close();
		socket.close(); // 关闭Socket连接

		byte b1[] = new byte[off];
		for (int i = 0; i < off; i++) {
			b1[i] = b[i];
		}

		return b1;
	}

	public static void main(String args[]) {
		String[] addr = { "北京", "上海", "广州" };
		Cake cake = new Cake();
		cake.setName("cheese");
		cake.setPrice(188.8);

		Map<Integer, String> map = new HashMap<Integer, String>();
		map.put(1, "hello");
		cake.setTest(map);

		Person p = new Person();
		p.setAge(20);
		p.setName("呵呵");
		p.setAddr(addr);
		p.setCake(cake);

		msgpackSerializer msgpack = new msgpackSerializer();
		MessagePackBufferPacker packer = new MessagePackBufferPacker();
		msgpack.msgpackSerialize(packer, p);

		// packer.packInt(1);
		// packer.packString("Hello");
		// packer.packInt(0);
		// packer.packString("World");
		// packer.packInt(10);
		// float a = 220;
		// packer.packFloat(a);
		// packer.packArrayHeader(3);
		// packer.packInt(1500);
		// packer.packInt(2);
		// packer.packInt(3);
		// packer.packString("helloworldhelloworldhelloworldhelldhelloworldhelldhelloworldhello");
		// packer.packMapHeader(2);
		// packer.packInt(2);
		// packer.packString("hello");
		// packer.packInt(330);
		// packer.packString("world");

		byte[] bytes = packer.toByteArray();
		try {
			packer.close();
		} catch (IOException e1) {
			// TODO Auto-generated catch block
			e1.printStackTrace();
		}

		try {
			System.out.println("===============Request=============");
			ConvertObject.printHexString(bytes, bytes.length);
			// MessageUnpacker unpacker = MessagePack.newDefaultUnpacker(packer
			// .toByteArray());
			System.out.println("===============Response=============");

			// MessageBufferPacker packer1 =
			// MessagePack.newDefaultBufferPacker();
			// byte[] extData = "custom data type".getBytes(MessagePack.UTF8);
			// packer1.packExtensionTypeHeader((byte)1, 10);
			// packer1.writePayload(extData);
			bytes = Send2Server(bytes);
			ConvertObject.printHexString(bytes, bytes.length);

			Person person = (Person) msgpack.unmsgpackSerialize(bytes,
					Person.class);
			System.out.println("====================================");
			System.out.println(person.getName());
			System.out.println(person.getAge());
			System.out.println(person.getAddr()[1]);
			System.out.println(person.getCake().getName());
			System.out.println(person.getCake().getPrice());
			System.out.println(person.getCake().getTest().get(1));
		} catch (Exception e) {
			// TODO Auto-genlerated catch block
			e.printStackTrace();
		}
	}
}
