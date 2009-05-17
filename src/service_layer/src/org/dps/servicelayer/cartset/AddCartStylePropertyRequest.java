package org.dps.servicelayer.cartset;

import javax.xml.bind.annotation.XmlAccessType;
import javax.xml.bind.annotation.XmlAccessorType;
import javax.xml.bind.annotation.XmlElement;

@XmlAccessorType(XmlAccessType.NONE)
public class AddCartStylePropertyRequest {
	
	private Long cartStyleID;
	private String name;
	private String property;
	private String value;
	
	@XmlElement(required = false)
	public Long getCartStyleID() {
		return cartStyleID;
	}
	public void setCartStyleID(Long cartStyleID_) {
		cartStyleID = cartStyleID_;
	}
	
	@XmlElement(required = false)
	public String getName() {
		return name;
	}
	public void setName(String name_) {
		name = name_;
	}
	
	@XmlElement(required = true)
	public String getProperty() {
		return property;
	}
	public void setProperty(String property_) {
		property = property_;
	}
	
	@XmlElement(required = true)
	public String getValue() {
		return value;
	}
	public void setValue(String value_) {
		value = value_;
	}
	
}
