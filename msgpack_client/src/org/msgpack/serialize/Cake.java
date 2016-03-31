package org.msgpack.serialize;

import java.util.Map;

public class Cake {
	private String name;
	private double price;
	private Map<Integer, String> test;

	public String getName() {
		return name;
	}

	public void setName(String name) {
		this.name = name;
	}

	public double getPrice() {
		return price;
	}

	public void setPrice(double price) {
		this.price = price;
	}

	public Map<Integer, String> getTest() {
		return test;
	}

	public void setTest(Map<Integer, String> test) {
		this.test = test;
	}

}
